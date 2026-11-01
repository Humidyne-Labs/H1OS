<#
.SYNOPSIS
    ESP32-S3 Zero-Dependency Native USB SLIP Flasher & Partition Inspector
    Target Silicon: Espressif ESP32-S3 (Mask ROM USB CDC, VID_303A&PID_1001)

.DESCRIPTION
    Pure, project-agnostic PowerShell + embedded C# SLIP engine that communicates
    directly with the ESP32-S3 Mask ROM bootloader over Windows inbox USB CDC (usbser.sys).
    Requires ZERO external dependencies (no Python, no esptool, no external drivers).

    Accepts generic physical flash primitives:
      -Write "0x0=boot.bin", "0x8000=pt.bin" : Flashes one or more offset=file segments
      -EraseAll                              : Scrubs entire SPI NOR flash die to 0xFF
      -EraseRegion -Offset 0x9000 -Length 0x14000 : Erases specific physical sector range
      -EraseRegions "0x9000=0x14000", ...    : Erases multiple physical regions
      -Inspect [-PartitionTable pt.bin]      : Audits on-chip hardware MD5s and chip info
#>

[CmdletBinding()]
param(
    # Flash segments in form "0xOFFSET=file.bin" or "OFFSET=file.bin"
    [Alias("Segments")]
    [string[]]$Write = @(),

    # Full flash die scrub to 0xFF (entire flash capacity)
    [switch]$EraseAll,

    # Single or multiple region erases in form "0xOFFSET=0xLENGTH"
    [Alias("EraseRegion")]
    [string[]]$EraseRegions = @(),

    # Specific flash region erase offset/length (alternative to -EraseRegions)
    [uint32]$Offset = [uint32]::MaxValue,
    [uint32]$Length = 0,

    # Connect to device and inspect on-chip partition MD5s and hardware telemetry
    [switch]$Inspect,

    # Path to binary partition-table.bin for structural validation and on-chip MD5 auditing
    [string]$PartitionTable = "",

    # Target COM port (auto-detects ESP32-S3 VID_303A:PID_1001 if omitted)
    [string]$Port = "",

    # Serial baud rate for SPI flashing (default: 460800)
    [int]$Baud = 460800,

    # Physical flash size in MB (default: 8)
    [int]$FlashSizeMB = 8,

    # Skip on-chip MD5 verification
    [switch]$NoVerify,

    # Suppress automatic post-flash reboot
    [switch]$NoReset,

    # Require connected board to be ESP32-S3-PICO-1-N8R8 (Waveshare 1.54" V2 panel)
    [switch]$RequireN8R8
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# ---------------------------------------------------------------------------
# 1. Embedded C# ESP32-S3 Mask ROM SLIP Engine & Partition Table Parser
# ---------------------------------------------------------------------------
$CSharpSource = @"
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.IO.Ports;
using System.Security.Cryptography;
using System.Text;
using System.Threading;

namespace Esp32Slip.Flasher
{
    public class PartitionEntry
    {
        public string Name { get; set; }
        public string TypeStr { get; set; }
        public string SubTypeStr { get; set; }
        public byte TypeCode { get; set; }
        public byte SubTypeCode { get; set; }
        public uint Offset { get; set; }
        public uint Size { get; set; }
        public bool IsSystemRegion { get; set; }

        public uint EndOffset { get { return Offset + Size - 1; } }
        public double SizeKB { get { return Size / 1024.0; } }
    }

    public class FlashSegment
    {
        public uint Offset { get; set; }
        public uint MaxAllowedSize { get; set; }
        public string FilePath { get; set; }
        public byte[] RawPayload { get; set; }
        public string Label { get; set; }
    }

    public static class PartitionTableParser
    {
        public const int FLASH_SECTOR_SIZE = 4096;

        public static List<PartitionEntry> ParseBinaryPartitionTable(byte[] data)
        {
            List<PartitionEntry> list = new List<PartitionEntry>();
            if (data == null || data.Length < 32) return list;

            int md5RowOffset = -1;

            for (int off = 0; off + 32 <= data.Length; off += 32)
            {
                ushort magic = BitConverter.ToUInt16(data, off);
                if (magic == 0xEBEB)
                {
                    md5RowOffset = off;
                    break;
                }
                if (magic == 0xFFFF) break;
                if (magic != 0x50AA) break;

                byte pType = data[off + 2];
                byte pSubType = data[off + 3];
                uint pOffset = BitConverter.ToUInt32(data, off + 4);
                uint pSize = BitConverter.ToUInt32(data, off + 8);

                int nameLen = 0;
                while (nameLen < 16 && data[off + 12 + nameLen] != 0) nameLen++;
                string name = Encoding.ASCII.GetString(data, off + 12, nameLen).Trim();

                list.Add(new PartitionEntry {
                    Name = name,
                    TypeCode = pType,
                    SubTypeCode = pSubType,
                    TypeStr = DecodeType(pType),
                    SubTypeStr = DecodeSubType(pType, pSubType),
                    Offset = pOffset,
                    Size = pSize,
                    IsSystemRegion = false
                });
            }

            // Verify embedded MD5 checksum if present
            if (md5RowOffset > 0)
            {
                byte[] expectedMd5 = new byte[16];
                Array.Copy(data, md5RowOffset + 16, expectedMd5, 0, 16);
                using (MD5 md5 = MD5.Create())
                {
                    byte[] actualMd5 = md5.ComputeHash(data, 0, md5RowOffset);
                    for (int i = 0; i < 16; i++)
                    {
                        if (expectedMd5[i] != actualMd5[i])
                        {
                            throw new InvalidDataException("Partition table MD5 checksum verification failed! Binary may be corrupt.");
                        }
                    }
                }
            }

            return list;
        }

        public static uint ParseSizeOrHex(string val)
        {
            string s = val.Trim();
            if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            {
                return uint.Parse(s.Substring(2), NumberStyles.HexNumber, CultureInfo.InvariantCulture);
            }
            if (s.EndsWith("MB", StringComparison.OrdinalIgnoreCase))
            {
                return (uint)(double.Parse(s.Substring(0, s.Length - 2), CultureInfo.InvariantCulture) * 1024 * 1024);
            }
            if (s.EndsWith("KB", StringComparison.OrdinalIgnoreCase))
            {
                return (uint)(double.Parse(s.Substring(0, s.Length - 2), CultureInfo.InvariantCulture) * 1024);
            }
            return uint.Parse(s, CultureInfo.InvariantCulture);
        }

        private static string DecodeType(byte t)
        {
            switch (t) {
                case 0x00: return "app";
                case 0x01: return "data";
                default:   return string.Format("0x{0:X2}", t);
            }
        }

        private static string DecodeSubType(byte t, byte st)
        {
            if (t == 0x00) {
                if (st == 0x00) return "factory";
                if (st >= 0x10 && st <= 0x1F) return string.Format("ota_{0}", st - 0x10);
                if (st == 0x20) return "test";
            } else if (t == 0x01) {
                if (st == 0x00) return "ota";
                if (st == 0x01) return "phy";
                if (st == 0x02) return "nvs";
                if (st == 0x03) return "coredump";
                if (st == 0x04) return "nvs_keys";
                if (st == 0x81) return "fat";
                if (st == 0x82) return "spiffs";
            }
            return string.Format("0x{0:X2}", st);
        }
    }

    public class Esp32ChipInfo
    {
        public uint ChipId;            // 9 = ESP32-S3
        public string ChipName;        // "ESP32-S3-PICO-1 (LGA56)" or "ESP32-S3 (QFN56)"
        public uint PackageCode;       // 1 = PICO-1, 0 = QFN56
        public uint MajorRevision;
        public uint MinorRevision;
        public string RevisionStr;     // "v0.2"
        public string MacAddress;      // "7C:DF:A1:XX:XX:XX"
        public uint FlashCapCode;      // 1 = 8MB, 2 = 4MB, 0 = External
        public string FlashCapStr;     // "8 MB Embedded Flash (GD)"
        public uint PsramCapCode;      // 1 = 8MB, 2 = 2MB, 0 = None
        public string PsramCapStr;     // "8 MB Embedded PSRAM"
        public bool IsN8R8;            // PackageCode == 1 && FlashCapCode == 1 && PsramCapCode == 1
    }

    public class Esp32S3RomFlasher : IDisposable
    {
        public const byte SLIP_END  = 0xC0;
        public const byte SLIP_ESC  = 0xDB;
        public const byte SLIP_ESC_END = 0xDC;
        public const byte SLIP_ESC_ESC = 0xDD;

        public const byte ESP_FLASH_BEGIN = 0x02;
        public const byte ESP_FLASH_DATA  = 0x03;
        public const byte ESP_FLASH_END   = 0x04;
        public const byte ESP_MEM_BEGIN   = 0x05;
        public const byte ESP_MEM_END     = 0x06;
        public const byte ESP_MEM_DATA    = 0x07;
        public const byte ESP_SYNC        = 0x08;
        public const byte ESP_WRITE_REG   = 0x09;
        public const byte ESP_READ_REG    = 0x0A;
        public const byte ESP_SPI_SET_PARAMS = 0x0B;
        public const byte ESP_SPI_ATTACH  = 0x0D;
        public const byte ESP_CHANGE_BAUDRATE = 0x0F;
        public const byte ESP_SPI_FLASH_MD5   = 0x13;
        public const byte ESP_GET_SECURITY_INFO = 0x14;

        public const int FLASH_BLOCK_SIZE = 1024;
        public const int FLASH_SECTOR_SIZE = 4096;

        private SerialPort _port;
        private string _portName;
        private int _baud;
        private bool _isNativeUsb;

        public Esp32S3RomFlasher(string portName, int baud, bool isNativeUsb)
        {
            _portName = portName;
            _baud = baud;
            _isNativeUsb = isNativeUsb;
        }

        public void WriteReg(uint addr, uint value, uint mask)
        {
            byte[] payload = new byte[16];
            Buffer.BlockCopy(BitConverter.GetBytes(addr),  0, payload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(value), 0, payload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(mask),  0, payload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(0u),    0, payload, 12, 4);

            uint val;
            ExecuteCommand(ESP_WRITE_REG, payload, 0, 1000, out val);
        }

        public uint ReadReg(uint addr)
        {
            byte[] payload = BitConverter.GetBytes(addr);
            uint val;
            ExecuteCommand(ESP_READ_REG, payload, 0, 1000, out val);
            return val;
        }

        public bool TryGetSecurityInfo(out uint chipId, out uint secFlags, out byte flashCryptCnt)
        {
            chipId = 0;
            secFlags = 0;
            flashCryptCnt = 0;
            try
            {
                byte[] resp = ExecuteCommandRaw(ESP_GET_SECURITY_INFO, new byte[0], 0, 1000);
                if (resp != null && resp.Length >= 8 + 20)
                {
                    secFlags = BitConverter.ToUInt32(resp, 8);
                    flashCryptCnt = resp[12];
                    chipId = BitConverter.ToUInt32(resp, 8 + 12);
                    return true;
                }
            }
            catch { }
            return false;
        }

        public Esp32ChipInfo ReadChipInfo()
        {
            Esp32ChipInfo info = new Esp32ChipInfo();

            uint chipId;
            uint secFlags;
            byte cryptCnt;
            if (TryGetSecurityInfo(out chipId, out secFlags, out cryptCnt))
            {
                info.ChipId = chipId;
            }
            else
            {
                info.ChipId = 9; // Fallback for standard S3 ROM
            }

            uint reg50 = ReadReg(0x60007050);
            uint reg54 = ReadReg(0x60007054);
            uint reg58 = ReadReg(0x60007058);
            uint mac0  = ReadReg(0x60007044);
            uint mac1  = ReadReg(0x60007048);

            // MAC Address
            byte b0 = (byte)((mac1 >> 8) & 0xFF);
            byte b1 = (byte)(mac1 & 0xFF);
            byte b2 = (byte)((mac0 >> 24) & 0xFF);
            byte b3 = (byte)((mac0 >> 16) & 0xFF);
            byte b4 = (byte)((mac0 >> 8) & 0xFF);
            byte b5 = (byte)(mac0 & 0xFF);
            info.MacAddress = string.Format("{0:X2}:{1:X2}:{2:X2}:{3:X2}:{4:X2}:{5:X2}", b0, b1, b2, b3, b4, b5);

            // Package Variant: 1 = PICO-1 (LGA56), 0 = Standard QFN56
            info.PackageCode = (reg50 >> 21) & 0x07;
            if (info.PackageCode == 1) info.ChipName = "ESP32-S3-PICO-1 (LGA56)";
            else if (info.PackageCode == 0) info.ChipName = "ESP32-S3 (QFN56)";
            else info.ChipName = string.Format("ESP32-S3 (pkg {0})", info.PackageCode);

            // Silicon Revisions
            uint rawMinorLow = (reg50 >> 18) & 0x07;
            uint rawMinorHi  = (reg58 >> 23) & 0x01;
            uint rawMinor    = (rawMinorHi << 3) | rawMinorLow;
            uint rawMajor    = (reg58 >> 24) & 0x03;

            // ECO0 check
            bool isEco0 = (rawMinor & 0x07) == 0 && (((reg54 >> 20) & 0x07) == 1);
            if (isEco0) { info.MajorRevision = 0; info.MinorRevision = 0; }
            else { info.MajorRevision = rawMajor; info.MinorRevision = rawMinor; }
            info.RevisionStr = string.Format("v{0}.{1}", info.MajorRevision, info.MinorRevision);

            // Embedded Flash Capacity & Vendor
            info.FlashCapCode = (reg50 >> 27) & 0x07;
            uint flashVendorId = reg54 & 0x07;
            string vendorStr = "";
            switch (flashVendorId) {
                case 1: vendorStr = "XMC"; break;
                case 2: vendorStr = "GD"; break;
                case 3: vendorStr = "FM"; break;
                case 4: vendorStr = "TT"; break;
                case 5: vendorStr = "BY"; break;
            }
            string vendorSuffix = string.IsNullOrEmpty(vendorStr) ? "" : (" (" + vendorStr + ")");

            switch (info.FlashCapCode) {
                case 1: info.FlashCapStr = "8 MB Embedded Flash" + vendorSuffix; break;
                case 2: info.FlashCapStr = "4 MB Embedded Flash" + vendorSuffix; break;
                case 0: info.FlashCapStr = "External Flash (on PCB)"; break;
                default: info.FlashCapStr = string.Format("Embedded Flash ({0})", info.FlashCapCode); break;
            }

            // Embedded PSRAM Capacity
            uint psramLow = (reg54 >> 3) & 0x03;
            uint psramHi  = (reg58 >> 19) & 0x01;
            info.PsramCapCode = (psramHi << 2) | psramLow;
            switch (info.PsramCapCode) {
                case 1: info.PsramCapStr = "8 MB Embedded PSRAM"; break;
                case 2: info.PsramCapStr = "2 MB Embedded PSRAM"; break;
                case 3: info.PsramCapStr = "16 MB Embedded PSRAM"; break;
                case 4: info.PsramCapStr = "4 MB Embedded PSRAM"; break;
                case 0: info.PsramCapStr = "None"; break;
                default: info.PsramCapStr = string.Format("Embedded PSRAM ({0})", info.PsramCapCode); break;
            }

            // Strictly true if LGA56 package + 8MB Flash + 8MB PSRAM
            info.IsN8R8 = (info.PackageCode == 1 && info.FlashCapCode == 1 && info.PsramCapCode == 1);
            return info;
        }

        public void DisableWatchdogs()
        {
            try {
                // RTC WDT (RTC_CNTL_WDTCONFIG0_REG: 0x60008048) -> disable stage 0-3
                WriteReg(0x60008048, 0x00000000, 0xFFFFFFFF);
                // Main System WDT (TIMG0_WDTCONFIG0_REG: 0x6001F048) -> disable
                WriteReg(0x6001F048, 0x00000000, 0xFFFFFFFF);
                // Super WDT (RTC_CNTL_SWD_CONF_REG: 0x600080B0) -> bypass
                WriteReg(0x600080B0, 0x40000000, 0x40000000);
            } catch { }
        }

        public void OpenPort(int baud)
        {
            if (_port != null && _port.IsOpen)
            {
                _port.Close();
                _port.Dispose();
            }
            _port = new SerialPort(_portName, baud, Parity.None, 8, StopBits.One);
            _port.ReadTimeout = 2500;
            _port.WriteTimeout = 2500;
            _port.DtrEnable = false;
            _port.RtsEnable = false;
            _port.Open();
            _port.DiscardInBuffer();
            _port.DiscardOutBuffer();
        }

        public void ClosePort()
        {
            if (_port != null && _port.IsOpen)
            {
                try { _port.Close(); } catch { }
                try { _port.Dispose(); } catch { }
                _port = null;
            }
        }

        public void Dispose()
        {
            ClosePort();
        }

        private void SetDtr(bool state)
        {
            try { _port.DtrEnable = state; } catch { }
        }

        private void SetRts(bool state)
        {
            try {
                _port.RtsEnable = state;
                _port.DtrEnable = _port.DtrEnable; // Windows usbser.sys flush workaround
            } catch { }
        }

        public void EnterBootloader()
        {
            Console.WriteLine(string.Format("[*] Engaging ESP32-S3 USB CDC on {0}...", _portName));
            if (_port == null || !_port.IsOpen)
            {
                OpenPort(115200);
            }

            if (_isNativeUsb)
            {
                // Official Espressif USB-Serial-JTAG reset pulse train (PID 0x1001)
                // Windows usbser.sys flushes SET_CONTROL_LINE_STATE only on RTS changes.
                SetRts(false); // Idle
                SetDtr(false);
                Thread.Sleep(100);

                SetDtr(true);  // Assert IO0 LOW (Download mode)
                SetRts(false);
                Thread.Sleep(100);

                SetRts(true);  // Assert CHIP_PU LOW (Reset active)
                SetDtr(false);
                SetRts(true);  // Re-apply RTS to flush DTR to usbser.sys
                Thread.Sleep(100);

                SetDtr(false); // Release IO0
                SetRts(false); // Release CHIP_PU HIGH -> Chip boots into ROM download mode!
                Thread.Sleep(200);
            }
            else
            {
                // Standard external UART bridge (CP2102/CH340/FTDI)
                SetDtr(false);
                SetRts(true);
                Thread.Sleep(100);
                SetDtr(true);
                SetRts(false);
                Thread.Sleep(100);
                SetDtr(false);
                SetRts(false);
                Thread.Sleep(200);
            }

            try {
                _port.DiscardInBuffer();
                _port.DiscardOutBuffer();
            } catch { }
        }

        public void SyncWithRom()
        {
            Console.Write("[*] Synchronizing with ESP32-S3 Mask ROM...");
            byte[] syncFrame = new byte[36];
            syncFrame[0] = 0x07;
            syncFrame[1] = 0x07;
            syncFrame[2] = 0x12;
            syncFrame[3] = 0x20;
            for (int i = 4; i < 36; i++) syncFrame[i] = 0x55;

            bool synced = false;
            for (int attempt = 1; attempt <= 25; attempt++)
            {
                // Every 6 failed sync frames, re-trigger bootloader reset sequence
                if (attempt == 7 || attempt == 14 || attempt == 20)
                {
                    EnterBootloader();
                }

                try
                {
                    uint retVal;
                    ExecuteCommand(ESP_SYNC, syncFrame, 0, 150, out retVal);
                    synced = true;
                    break;
                }
                catch
                {
                    try { _port.DiscardInBuffer(); } catch { }
                    Console.Write(".");
                    Thread.Sleep(40);
                }
            }

            if (!synced)
            {
                Console.WriteLine(" FAILED");
                throw new TimeoutException("Failed to synchronize with ESP32-S3 Mask ROM. Hold BOOT, press RESET, and retry.");
            }
            Console.WriteLine(" OK (Mask ROM Connected)");

            // Drain extra sync replies
            Thread.Sleep(40);
            DrainInput(100);
            DisableWatchdogs();
        }

        public void AttachAndConfigureSpiFlash(int flashSizeMB)
        {
            Console.WriteLine("[*] Attaching SPI Flash (DIO Mode, 80MHz)...");

            // Attach SPI (ESP_SPI_ATTACH 0x0D, payload = 8 zero bytes)
            byte[] attachPayload = new byte[8];
            uint val;
            ExecuteCommand(ESP_SPI_ATTACH, attachPayload, 0, 1500, out val);

            // Configure SPI parameters (0x0B)
            // 8MB = 0x800000, 64KB block, 4KB sector, 256B page, 0xFFFF status mask
            uint flashSizeParam = (uint)flashSizeMB * 1024u * 1024u;
            byte[] spiParams = new byte[24];
            Buffer.BlockCopy(BitConverter.GetBytes(0u),              0, spiParams, 0,  4); // id
            Buffer.BlockCopy(BitConverter.GetBytes(flashSizeParam), 0, spiParams, 4,  4); // total size
            Buffer.BlockCopy(BitConverter.GetBytes(64u * 1024u),    0, spiParams, 8,  4); // block size
            Buffer.BlockCopy(BitConverter.GetBytes(4u * 1024u),     0, spiParams, 12, 4); // sector size
            Buffer.BlockCopy(BitConverter.GetBytes(256u),           0, spiParams, 16, 4); // page size
            Buffer.BlockCopy(BitConverter.GetBytes(0xFFFFu),        0, spiParams, 20, 4); // status mask
            ExecuteCommand(ESP_SPI_SET_PARAMS, spiParams, 0, 1500, out val);

            // Negotiate fast baud rate if requested and != 115200
            if (_baud > 115200)
            {
                Console.WriteLine(string.Format("[*] Accelerating baud rate to {0:N0} baud...", _baud));
                byte[] baudPayload = new byte[8];
                Buffer.BlockCopy(BitConverter.GetBytes((uint)_baud), 0, baudPayload, 0, 4);
                Buffer.BlockCopy(BitConverter.GetBytes(0u),          0, baudPayload, 4, 4);
                ExecuteCommand(ESP_CHANGE_BAUDRATE, baudPayload, 0, 1000, out val);

                ClosePort();
                Thread.Sleep(50);
                OpenPort(_baud);
                Thread.Sleep(50);
                _port.DiscardInBuffer();
            }
        }

        public void EraseFlashRegion(uint startOffset, uint byteLength, string regionLabel)
        {
            if ((startOffset % FLASH_SECTOR_SIZE) != 0)
            {
                throw new Exception(string.Format("Erase start offset 0x{0:X} must be 4KB sector-aligned.", startOffset));
            }
            uint alignedLen = ((byteLength + (uint)FLASH_SECTOR_SIZE - 1u) / (uint)FLASH_SECTOR_SIZE) * (uint)FLASH_SECTOR_SIZE;
            uint maxStep = 256u * 1024u;
            uint totalSteps = (alignedLen + maxStep - 1u) / maxStep;

            Console.WriteLine(string.Format("\n[*] Erasing {0} (0x{1:X6} .. 0x{2:X6}, {3:N1} KB -> 0xFF)...",
                regionLabel, startOffset, startOffset + alignedLen - 1, alignedLen / 1024.0));
            Stopwatch sw = Stopwatch.StartNew();

            uint remaining = alignedLen;
            uint curOffset = startOffset;
            uint stepIdx = 0;

            while (remaining > 0)
            {
                stepIdx++;
                uint chunk = Math.Min(remaining, maxStep);
                int pct = (int)((stepIdx * 100) / totalSteps);
                Console.Write(string.Format("\r    Scrubbing 0x{0:X6} .. 0x{1:X6} [{2,3}%]",
                    curOffset, curOffset + chunk - 1, pct));

                byte[] beginPayload = new byte[20];
                Buffer.BlockCopy(BitConverter.GetBytes(chunk),                  0, beginPayload, 0,  4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                0, beginPayload, 4,  4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)FLASH_BLOCK_SIZE), 0, beginPayload, 8,  4);
                Buffer.BlockCopy(BitConverter.GetBytes(curOffset),              0, beginPayload, 12, 4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                0, beginPayload, 16, 4);

                int timeoutMs = Math.Max(15000, 6000 + (int)((chunk / 65536) * 2500));
                uint val;
                ExecuteCommand(ESP_FLASH_BEGIN, beginPayload, 0, timeoutMs, out val);

                curOffset += chunk;
                remaining -= chunk;
            }

            sw.Stop();
            Console.WriteLine(string.Format("\n    [+] Erased {0} in {1:F1}s.", regionLabel, sw.Elapsed.TotalSeconds));
        }

        public void FlashSegment(FlashSegment segment, bool verifyMd5)
        {
            byte[] rawBytes = segment.RawPayload;
            if (rawBytes == null)
            {
                if (!File.Exists(segment.FilePath))
                {
                    throw new FileNotFoundException("Binary file not found: " + segment.FilePath);
                }
                rawBytes = File.ReadAllBytes(segment.FilePath);
            }

            if (rawBytes.Length == 0)
            {
                throw new Exception("Binary payload is empty for segment: " + segment.Label);
            }

            if (segment.MaxAllowedSize > 0 && rawBytes.Length > segment.MaxAllowedSize)
            {
                throw new Exception(string.Format(
                    "Binary '{0}' ({1:N0} bytes) exceeds capacity ({2:N0} bytes) at 0x{3:X6}!",
                    segment.Label, rawBytes.Length, segment.MaxAllowedSize, segment.Offset));
            }

            if ((segment.Offset % FLASH_SECTOR_SIZE) != 0)
            {
                throw new Exception(string.Format("Flash offset 0x{0:X} is not 4KB sector-aligned.", segment.Offset));
            }

            FlashBlockSequence(segment.Offset, rawBytes, segment.Label);

            if (verifyMd5)
            {
                VerifySegmentMd5(segment.Offset, rawBytes, segment.Label);
            }
        }

        private void FlashBlockSequence(uint offset, byte[] data, string label)
        {
            uint totalSize = (uint)data.Length;
            uint numBlocks = (totalSize + FLASH_BLOCK_SIZE - 1) / FLASH_BLOCK_SIZE;

            Console.WriteLine(string.Format("\n[*] Writing {0} (0x{1:X6}, {2:N1} KB, {3} blocks)...",
                label, offset, totalSize / 1024.0, numBlocks));

            // ESP_FLASH_BEGIN
            byte[] beginPayload = new byte[20];
            Buffer.BlockCopy(BitConverter.GetBytes(totalSize),               0, beginPayload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(numBlocks),                0, beginPayload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)FLASH_BLOCK_SIZE),   0, beginPayload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(offset),                   0, beginPayload, 12, 4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                  0, beginPayload, 16, 4);

            int eraseTimeoutMs = Math.Max(12000, 5000 + (int)((totalSize / 65536) * 1800));
            uint val;
            ExecuteCommand(ESP_FLASH_BEGIN, beginPayload, 0, eraseTimeoutMs, out val);

            Stopwatch sw = Stopwatch.StartNew();

            for (uint seq = 0; seq < numBlocks; seq++)
            {
                uint blockOffset = seq * FLASH_BLOCK_SIZE;
                uint thisBlockSize = Math.Min((uint)FLASH_BLOCK_SIZE, totalSize - blockOffset);

                byte[] blockData = new byte[FLASH_BLOCK_SIZE];
                for (int i = 0; i < FLASH_BLOCK_SIZE; i++) blockData[i] = 0xFF;
                Buffer.BlockCopy(data, (int)blockOffset, blockData, 0, (int)thisBlockSize);

                byte[] dataPayload = new byte[16 + FLASH_BLOCK_SIZE];
                Buffer.BlockCopy(BitConverter.GetBytes(thisBlockSize), 0, dataPayload, 0,  4);
                Buffer.BlockCopy(BitConverter.GetBytes(seq),           0, dataPayload, 4,  4);
                Buffer.BlockCopy(BitConverter.GetBytes(0u),            0, dataPayload, 8,  4);
                Buffer.BlockCopy(BitConverter.GetBytes(0u),            0, dataPayload, 12, 4);
                Buffer.BlockCopy(blockData, 0, dataPayload, 16, FLASH_BLOCK_SIZE);

                ExecuteCommand(ESP_FLASH_DATA, dataPayload, 0, 4000, out val);

                int pct = (int)(((seq + 1) * 100) / numBlocks);
                double elapsedSec = sw.Elapsed.TotalSeconds;
                double speedKBps = (elapsedSec > 0.05) ? ((seq + 1) * FLASH_BLOCK_SIZE / 1024.0) / elapsedSec : 0.0;
                Console.Write(string.Format("\r    Progress: {0,3}% ({1,5:N1} KB / {2,5:N1} KB) @ {3:F1} KB/s    ",
                    pct, (blockOffset + thisBlockSize) / 1024.0, totalSize / 1024.0, speedKBps));
            }

            sw.Stop();
            Console.WriteLine(string.Format("\n    [+] Written in {0:F2}s ({1:F1} KB/s).",
                sw.Elapsed.TotalSeconds, (totalSize / 1024.0) / Math.Max(0.01, sw.Elapsed.TotalSeconds)));
        }

        public string ComputeOnChipMd5(uint offset, uint size)
        {
            byte[] md5Payload = new byte[16];
            Buffer.BlockCopy(BitConverter.GetBytes(offset), 0, md5Payload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(size),   0, md5Payload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(0u),     0, md5Payload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(0u),     0, md5Payload, 12, 4);

            int md5Timeout = Math.Max(5000, 2000 + (int)((size / 65536) * 400));
            byte[] resp = ExecuteCommandRaw(ESP_SPI_FLASH_MD5, md5Payload, 0, md5Timeout);

            // Response payload contains 16-byte binary MD5 or 32-byte hex string
            byte[] valBytes = new byte[resp.Length - 8];
            Buffer.BlockCopy(resp, 8, valBytes, 0, valBytes.Length);

            if (valBytes.Length >= 32)
            {
                return Encoding.ASCII.GetString(valBytes, 0, 32).ToLowerInvariant();
            }
            if (valBytes.Length >= 16)
            {
                StringBuilder sb = new StringBuilder(32);
                for (int i = 0; i < 16; i++) sb.Append(valBytes[i].ToString("x2"));
                return sb.ToString();
            }
            throw new Exception("Unexpected MD5 response size: " + valBytes.Length);
        }

        public void VerifySegmentMd5(uint offset, byte[] expectedData, string label)
        {
            Console.Write(string.Format("[*] Verifying on-chip MD5 for {0}...", label));
            string hostMd5 = ComputeHostMd5Hex(expectedData);
            string chipMd5 = ComputeOnChipMd5(offset, (uint)expectedData.Length);

            if (string.Equals(hostMd5, chipMd5, StringComparison.OrdinalIgnoreCase))
            {
                Console.WriteLine(" VERIFIED (" + chipMd5.Substring(0, 16) + "...)");
            }
            else
            {
                Console.WriteLine(" MISMATCH!");
                throw new Exception(string.Format("MD5 Mismatch for {0} at 0x{1:X6}!\n  Host: {2}\n  Chip: {3}",
                    label, offset, hostMd5, chipMd5));
            }
        }

        public void FinishAndReboot()
        {
            Console.WriteLine("[*] Finalizing flash and rebooting target SoC...");
            try {
                byte[] endPayload = new byte[4]; // reboot flag = 0
                uint val;
                ExecuteCommand(ESP_FLASH_END, endPayload, 0, 1500, out val);
            } catch { }

            // Hardware reset pulse via RTS/DTR
            try {
                if (_port != null && _port.IsOpen)
                {
                    _port.DtrEnable = false;
                    _port.RtsEnable = true;
                    Thread.Sleep(50);
                    _port.RtsEnable = false;
                    Thread.Sleep(50);
                }
            } catch { }
        }

        private void DrainInput(int timeoutMs)
        {
            if (_port == null || !_port.IsOpen) return;
            int oldTimeout = _port.ReadTimeout;
            _port.ReadTimeout = timeoutMs;
            try {
                while (true) { _port.ReadByte(); }
            } catch { }
            finally {
                if (_port != null && _port.IsOpen) _port.ReadTimeout = oldTimeout;
            }
        }

        private void ExecuteCommand(byte op, byte[] data, uint checksum, int timeoutMs, out uint retVal)
        {
            byte[] resp = ExecuteCommandRaw(op, data, checksum, timeoutMs);
            retVal = BitConverter.ToUInt32(resp, 4);
        }

        private byte[] ExecuteCommandRaw(byte op, byte[] data, uint checksum, int timeoutMs)
        {
            if (data == null) data = new byte[0];
            ushort dataLen = (ushort)data.Length;

            byte[] pkt = new byte[8 + dataLen];
            pkt[0] = 0x00; // Direction: host -> ROM
            pkt[1] = op;
            pkt[2] = (byte)(dataLen & 0xFF);
            pkt[3] = (byte)((dataLen >> 8) & 0xFF);
            Buffer.BlockCopy(BitConverter.GetBytes(checksum), 0, pkt, 4, 4);
            Buffer.BlockCopy(data, 0, pkt, 8, dataLen);

            byte[] slipPkt = SlipEncode(pkt);
            _port.Write(slipPkt, 0, slipPkt.Length);

            Stopwatch sw = Stopwatch.StartNew();
            List<byte> replyBuffer = new List<byte>(64);

            int prevTimeout = _port.ReadTimeout;
            _port.ReadTimeout = Math.Max(100, timeoutMs);

            try
            {
                while (sw.ElapsedMilliseconds < timeoutMs)
                {
                    int b = _port.ReadByte();
                    if (b < 0) continue;

                    if ((byte)b == SLIP_END)
                    {
                        if (replyBuffer.Count > 0)
                        {
                            byte[] decoded = SlipDecode(replyBuffer.ToArray());
                            replyBuffer.Clear();

                            if (decoded.Length >= 8 && decoded[0] == 0x01 && decoded[1] == op)
                            {
                                byte status = (decoded.Length >= 10) ? decoded[decoded.Length - 2] : (byte)0;
                                byte err = (decoded.Length >= 10) ? decoded[decoded.Length - 1] : (byte)0;
                                if (status != 0)
                                {
                                    throw new Exception(string.Format("ROM command 0x{0:X2} failed with status 0x{1:X2}, err 0x{2:X2}.", op, status, err));
                                }
                                return decoded;
                            }
                        }
                    }
                    else
                    {
                        replyBuffer.Add((byte)b);
                    }
                }
            }
            finally
            {
                if (_port != null && _port.IsOpen) _port.ReadTimeout = prevTimeout;
            }

            throw new TimeoutException(string.Format("Timeout waiting for ROM reply to command 0x{0:X2} after {1}ms.", op, timeoutMs));
        }

        private static byte[] SlipEncode(byte[] input)
        {
            List<byte> outList = new List<byte>(input.Length + 16);
            outList.Add(SLIP_END);
            for (int i = 0; i < input.Length; i++)
            {
                byte b = input[i];
                if (b == SLIP_END)
                {
                    outList.Add(SLIP_ESC);
                    outList.Add(SLIP_ESC_END);
                }
                else if (b == SLIP_ESC)
                {
                    outList.Add(SLIP_ESC);
                    outList.Add(SLIP_ESC_ESC);
                }
                else
                {
                    outList.Add(b);
                }
            }
            outList.Add(SLIP_END);
            return outList.ToArray();
        }

        private static byte[] SlipDecode(byte[] input)
        {
            List<byte> outList = new List<byte>(input.Length);
            for (int i = 0; i < input.Length; i++)
            {
                byte b = input[i];
                if (b == SLIP_ESC && i + 1 < input.Length)
                {
                    byte next = input[++i];
                    if (next == SLIP_ESC_END) outList.Add(SLIP_END);
                    else if (next == SLIP_ESC_ESC) outList.Add(SLIP_ESC);
                    else outList.Add(next);
                }
                else
                {
                    outList.Add(b);
                }
            }
            return outList.ToArray();
        }

        public static string ComputeHostMd5Hex(byte[] data)
        {
            using (MD5 md5 = MD5.Create())
            {
                byte[] hash = md5.ComputeHash(data);
                StringBuilder sb = new StringBuilder(32);
                for (int i = 0; i < 16; i++) sb.Append(hash[i].ToString("x2"));
                return sb.ToString();
            }
        }

        public static string ComputeBlankRegionMd5Hex(uint size)
        {
            using (MD5 md5 = MD5.Create())
            {
                byte[] chunk = new byte[65536];
                for (int i = 0; i < chunk.Length; i++) chunk[i] = 0xFF;

                uint remaining = size;
                while (remaining > 0)
                {
                    int take = (int)Math.Min((uint)chunk.Length, remaining);
                    if (remaining - (uint)take == 0)
                    {
                        md5.TransformFinalBlock(chunk, 0, take);
                    }
                    else
                    {
                        md5.TransformBlock(chunk, 0, take, null, 0);
                    }
                    remaining -= (uint)take;
                }
                byte[] hash = md5.Hash;
                StringBuilder sb = new StringBuilder(32);
                for (int i = 0; i < 16; i++) sb.Append(hash[i].ToString("x2"));
                return sb.ToString();
            }
        }
    }
}
"@

# Compile embedded C# SLIP engine
if (-not ([System.Management.Automation.PSTypeName]'Esp32Slip.Flasher.Esp32S3RomFlasher').Type) {
    Add-Type -TypeDefinition $CSharpSource -Language CSharp
}

# ---------------------------------------------------------------------------
# 2. Port Auto-Discovery Helper
# ---------------------------------------------------------------------------
function Find-Esp32S3Port {
    param([string]$RequestedPort)

    if (-not [string]::IsNullOrWhiteSpace($RequestedPort)) {
        return [PSCustomObject]@{
            PortName    = $RequestedPort.Trim().ToUpper()
            Description = "User-specified serial port"
            IsNativeUsb = $true
        }
    }

    Write-Host "[*] Scanning Windows PnP tree for ESP32-S3 USB CDC (VID_303A)..." -ForegroundColor Cyan

    try {
        $pnpDevices = @(Get-CimInstance -ClassName Win32_PnPEntity -ErrorAction SilentlyContinue |
            Where-Object { $_.Name -match '\((COM\d+)\)' })

        foreach ($dev in $pnpDevices) {
            if ($dev.PNPDeviceID -match 'VID_303A' -and $dev.Name -match '\((COM\d+)\)') {
                $com = $Matches[1]
                $isNative = ($dev.PNPDeviceID -match 'PID_1001') -or ($dev.PNPDeviceID -match 'VID_303A')
                Write-Host "[+] Auto-discovered ESP32-S3 on $com : $($dev.Name)" -ForegroundColor Green
                return [PSCustomObject]@{
                    PortName    = $com
                    Description = $dev.Name
                    IsNativeUsb = $isNative
                }
            }
        }

        foreach ($dev in $pnpDevices) {
            if (($dev.PNPDeviceID -match '^USB\\') -and ($dev.Name -match '\((COM\d+)\)')) {
                $com = $Matches[1]
                Write-Host "[!] Found USB Serial port $com : $($dev.Name)" -ForegroundColor Yellow
                return [PSCustomObject]@{
                    PortName    = $com
                    Description = $dev.Name
                    IsNativeUsb = $true
                }
            }
        }
    }
    catch { }

    $ports = @([System.IO.Ports.SerialPort]::GetPortNames() | Sort-Object)
    if ($ports.Count -gt 0) {
        $selected = $ports[-1]
        Write-Host "[!] Using active serial port: $selected" -ForegroundColor Yellow
        return [PSCustomObject]@{
            PortName    = $selected
            Description = "Serial Port $selected"
            IsNativeUsb = $true
        }
    }

    throw "No ESP32-S3 serial port detected. Verify the USB-C cable is connected."
}

# ---------------------------------------------------------------------------
# 3. Main Flasher Execution Logic
# ---------------------------------------------------------------------------
Write-Host "=========================================================================" -ForegroundColor Green
Write-Host "    ESP32-S3 Zero-Dependency Native USB SLIP Flasher (Windows CDC)       " -ForegroundColor Green
Write-Host "=========================================================================" -ForegroundColor Green

try {
    $portInfo = Find-Esp32S3Port -RequestedPort $Port

    $eraseRegions  = New-Object System.Collections.Generic.List[PSCustomObject]
    $writeSegments = New-Object System.Collections.Generic.List[Esp32Slip.Flasher.FlashSegment]

    # Handle -EraseAll
    if ($EraseAll.IsPresent) {
        $eraseRegions.Add([PSCustomObject]@{
            Offset = [uint32]0x000000
            Length = [uint32]($FlashSizeMB * 1024 * 1024)
            Label  = "Entire ${FlashSizeMB}MB NOR Flash Die"
        })
    }

    # Handle single region via -Offset and -Length
    if ($Offset -ne [uint32]::MaxValue -or $Length -gt 0) {
        if ($Offset -eq [uint32]::MaxValue -or $Length -eq 0) {
            throw "Specifying an offset erase requires both -Offset <uint32> and -Length <uint32> (or use -EraseRegions '0xOFFSET=0xLENGTH')."
        }
        $eraseRegions.Add([PSCustomObject]@{
            Offset = $Offset
            Length = $Length
            Label  = "Region @ 0x$($Offset.ToString('X6'))"
        })
    }

    # Handle -EraseRegions @("0xOFFSET=0xLENGTH", ...)
    if ($EraseRegions -and $EraseRegions.Count -gt 0) {
        $expandedErase = New-Object System.Collections.Generic.List[string]
        foreach ($item in $EraseRegions) {
            if ([string]::IsNullOrWhiteSpace($item)) { continue }
            $parts = $item -split '[,;]'
            foreach ($p in $parts) {
                $trimmed = $p.Trim().Trim('"', "'")
                if (-not [string]::IsNullOrWhiteSpace($trimmed)) {
                    $expandedErase.Add($trimmed)
                }
            }
        }

        foreach ($entry in $expandedErase) {
            if ($entry -notmatch '^(0x[0-9a-fA-F]+|\d+)=(0x[0-9a-fA-F]+|\d+)$') {
                throw "Invalid erase region format '$entry'. Expected '0xOFFSET=0xLENGTH'."
            }
            $erOff = [Esp32Slip.Flasher.PartitionTableParser]::ParseSizeOrHex($Matches[1])
            $erLen = [Esp32Slip.Flasher.PartitionTableParser]::ParseSizeOrHex($Matches[2])
            $eraseRegions.Add([PSCustomObject]@{
                Offset = $erOff
                Length = $erLen
                Label  = "Region @ 0x$($erOff.ToString('X6'))"
            })
        }
    }

    # Handle -Write @("0xOFFSET=file.bin", ...)
    if ($Write -and $Write.Count -gt 0) {
        $expandedWrite = New-Object System.Collections.Generic.List[string]
        foreach ($item in $Write) {
            if ([string]::IsNullOrWhiteSpace($item)) { continue }
            $parts = $item -split '[,;]'
            foreach ($p in $parts) {
                $trimmed = $p.Trim().Trim('"', "'")
                if (-not [string]::IsNullOrWhiteSpace($trimmed)) {
                    $expandedWrite.Add($trimmed)
                }
            }
        }

        foreach ($entry in $expandedWrite) {
            if ($entry -notmatch '^(0x[0-9a-fA-F]+|\d+)=(.+)$') {
                throw "Invalid segment format '$entry'. Expected '0xOFFSET=file.bin'."
            }
            $segOffset = [Esp32Slip.Flasher.PartitionTableParser]::ParseSizeOrHex($Matches[1])
            $segFile   = $Matches[2].Trim().Trim('"', "'")

            if (-not [System.IO.Path]::IsPathRooted($segFile)) {
                $segFile = Join-Path (Get-Location).Path $segFile
            }
            if (-not (Test-Path $segFile)) {
                throw "Binary file not found for segment: $segFile"
            }

            $s = New-Object Esp32Slip.Flasher.FlashSegment
            $s.Offset = $segOffset
            $s.FilePath = $segFile
            $s.Label = [System.IO.Path]::GetFileName($segFile)
            $writeSegments.Add($s)
        }
    }

    # Print plan
    Write-Host "[*] Target Serial Port        : $($portInfo.PortName) ($($portInfo.Description))"

    if ($eraseRegions.Count -gt 0) {
        Write-Host "[*] Erase Operations Queued   : $($eraseRegions.Count)" -ForegroundColor Yellow
        foreach ($er in $eraseRegions) {
            Write-Host ("    -> ERASE 0x{0:X6} ({1,7:N1} KB) : {2}" -f $er.Offset, ($er.Length / 1024.0), $er.Label) -ForegroundColor Yellow
        }
    }

    if ($writeSegments.Count -gt 0) {
        Write-Host "[*] Write Segments Queued     : $($writeSegments.Count)" -ForegroundColor Cyan
        foreach ($ws in $writeSegments) {
            $szBytes = (Get-Item $ws.FilePath).Length
            Write-Host ("    -> WRITE 0x{0:X6} ({1,7:N1} KB) : {2}" -f $ws.Offset, ($szBytes / 1024.0), $ws.Label) -ForegroundColor Cyan
        }
    }

    # Execute Hardware Connection
    $flasher = New-Object Esp32Slip.Flasher.Esp32S3RomFlasher($portInfo.PortName, $Baud, $portInfo.IsNativeUsb)
    try {
        $flasher.EnterBootloader()
        $flasher.SyncWithRom()

        # Read silicon identity and validate invariant
        $chipInfo = $flasher.ReadChipInfo()
        if ($chipInfo.ChipId -ne 9) {
            throw "Incompatible silicon detected! Target chip ID is $($chipInfo.ChipId), but flasher.ps1 strictly supports ESP32-S3 (Chip ID 9)."
        }

        Write-Host "[*] Detected Silicon          : $($chipInfo.ChipName) (revision $($chipInfo.RevisionStr))"
        Write-Host "[*] Integrated Memory         : $($chipInfo.FlashCapStr) + $($chipInfo.PsramCapStr)"
        Write-Host "[*] Factory Base MAC          : $($chipInfo.MacAddress)"

        if ($RequireN8R8.IsPresent) {
            if (-not $chipInfo.IsN8R8) {
                throw "Hardware mismatch! Connected board is '$($chipInfo.ChipName)' with '$($chipInfo.FlashCapStr)' and '$($chipInfo.PsramCapStr)'. This firmware package strictly requires Waveshare ESP32-S3-PICO-1-N8R8."
            }
            Write-Host "[+] Hardware Invariant Check  : PASS (Waveshare ESP32-S3-PICO-1-N8R8 Confirmed)" -ForegroundColor Green
        }

        $flasher.AttachAndConfigureSpiFlash($FlashSizeMB)

        if ($Inspect.IsPresent) {
            Write-Host ""
            Write-Host "  ESP32-S3 Hardware & Silicon Inspection:" -ForegroundColor Cyan
            Write-Host "  -----------------------------------------------------------------------------------" -ForegroundColor DarkGray
            Write-Host "  Port              : $($portInfo.PortName) ($($portInfo.Description))" -ForegroundColor White
            Write-Host "  Silicon Model     : $($chipInfo.ChipName) (revision $($chipInfo.RevisionStr))" -ForegroundColor White
            Write-Host "  Integrated Memory : $($chipInfo.FlashCapStr) + $($chipInfo.PsramCapStr)" -ForegroundColor White
            Write-Host "  Hardware Match    : $(if ($chipInfo.IsN8R8) { 'Waveshare ESP32-S3-PICO-1-N8R8 (CONFIRMED)' } else { 'Generic / Non-N8R8' })" -ForegroundColor $(if ($chipInfo.IsN8R8) { 'Green' } else { 'Yellow' })
            Write-Host "  Factory Base MAC  : $($chipInfo.MacAddress)" -ForegroundColor White
            Write-Host "  Baud Rate         : $Baud baud" -ForegroundColor White
            Write-Host "  Flash Size        : ${FlashSizeMB} MB" -ForegroundColor White

            if (-not [string]::IsNullOrWhiteSpace($PartitionTable) -and (Test-Path $PartitionTable)) {
                $ptBytes = [System.IO.File]::ReadAllBytes($PartitionTable)
                $partMap = [Esp32Slip.Flasher.PartitionTableParser]::ParseBinaryPartitionTable($ptBytes)

                Write-Host ""
                Write-Host "  Partition Table Inspection ($([System.IO.Path]::GetFileName($PartitionTable))):" -ForegroundColor Cyan
                Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray
                Write-Host ("  {0,-16} {1,-8} {2,-10} {3,-10} {4,10}  {5,-34} {6}" -f "Name", "Type", "SubType", "Offset", "Size (KB)", "On-Chip MD5", "Status") -ForegroundColor White
                Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray

                foreach ($p in $partMap) {
                    $chipMd5 = $flasher.ComputeOnChipMd5($p.Offset, $p.Size)
                    $blankMd5 = [Esp32Slip.Flasher.Esp32S3RomFlasher]::ComputeBlankRegionMd5Hex($p.Size)
                    $statusStr = if ($chipMd5 -eq $blankMd5) { "BLANK (0xFF)" } else { "POPULATED" }
                    $color = if ($chipMd5 -eq $blankMd5) { "DarkGray" } else { "Green" }

                    Write-Host ("  {0,-16} {1,-8} {2,-10} 0x{3:X6}   {4,10:N1}  {5,-34} {6}" -f `
                        $p.Name, $p.TypeStr, $p.SubTypeStr, $p.Offset, $p.SizeKB, $chipMd5, $statusStr) -ForegroundColor $color
                }
                Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray
            }
        }
        else {
            foreach ($er in $eraseRegions) {
                $flasher.EraseFlashRegion($er.Offset, $er.Length, $er.Label)
            }

            $verify = -not $NoVerify.IsPresent
            foreach ($ws in $writeSegments) {
                $flasher.FlashSegment($ws, $verify)
            }
        }

        if (-not $NoReset.IsPresent) {
            $flasher.FinishAndReboot()
        }
    }
    finally {
        $flasher.Dispose()
    }

    Write-Host ""
    Write-Host "=========================================================================" -ForegroundColor Green
    Write-Host " [SUCCESS] All requested flash operations completed successfully!        " -ForegroundColor Green
    Write-Host "=========================================================================" -ForegroundColor Green
    exit 0
}
catch {
    Write-Host ""
    Write-Host "=========================================================================" -ForegroundColor Red
    Write-Host " [FAILED] $($_.Exception.Message)" -ForegroundColor Red
    Write-Host "=========================================================================" -ForegroundColor Red
    exit 1
}
