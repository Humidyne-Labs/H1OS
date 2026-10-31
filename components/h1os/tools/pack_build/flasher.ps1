<#
.SYNOPSIS
    H1OS Unified Zero-Dependency ESP32-S3 Native USB Flasher, Partition & NVS Manager
    Target Hardware: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8, 8MB DIO Flash, VID_303A&PID_1001)

.DESCRIPTION
    Single self-contained PowerShell + embedded C# SLIP engine that communicates directly with the
    ESP32-S3 Mask ROM bootloader over Windows inbox USB CDC (usbser.sys).
    Requires ZERO external dependencies (no Python, no esptool, no Zadig/FTDI drivers).

    Designed to be driven either by:
      1. One-touch Control-Vector Batch Files:
         - flash_update_keep_nvs.bat : Updates Bootloader + PartTable + otadata + ota_0 App; keeps NVS, SPIFFS & epd_frame
         - flash_app_only.bat        : Updates ota_0 App (0x20000) + otadata; keeps Bootloader, PartTable, NVS, SPIFFS & epd_frame
         - flash_factory.bat         : Full 8MB NOR die scrub to 0xFF + complete factory restore
         - flash_nvs_wipe.bat        : Erases only nvs (0x9000) and phy_init (0x1F000); keeps App & SPIFFS intact
      2. Master Interactive Hub (flash_now.bat / -Interactive):
         - Calls the turnkey batch vectors OR opens the built-in Partition Manager, Dual-OTA Slot Manager,
           NVS/SPIFFS/Framebuffer Manager, and Live On-Chip MD5 Inspector.
      3. Direct CLI Invocation for custom hacking/automation.

.PARAMETER Profile
    High-level operation profile:
      - KeepNvs       : (Default) Flashes Bootloader, Partition Table, otadata, and App -> ota_0; preserves nvs, ota_1, storage, epd_frame
      - AppOnly       : Flashes App -> TargetSlot (default ota_0) and updates otadata; preserves Bootloader, Partition Table, nvs, storage, epd_frame
      - Factory       : Scrubs full 8MB flash die to 0xFF, then flashes Bootloader, Partition Table, otadata, and App -> ota_0
      - DualOta       : Flashes App to BOTH ota_0 (0x20000) and ota_1 (0x320000) for redundant fallback
      - WipeNvs       : Erases only nvs (0x9000, 80KB) and phy_init (0x1F000, 4KB)
      - WipeStorage   : Erases only storage SPIFFS partition (0x620000, 1904KB)
      - WipeEpdFrame  : Erases only epd_frame ePaper buffer partition (0x7FC000, 16KB)
      - SetBootSlot   : Updates otadata (0x1D000) to boot either ota_0 or ota_1 without re-flashing app binaries
      - CustomWrite   : Writes -Binary to -TargetPartition (by name) or -Offset (hex)
      - CustomErase   : Erases -TargetPartition (by name) or [-Offset, -EraseLength]
      - Inspect       : Connects to ESP32-S3 and computes live on-chip MD5 across all partitions in the 8MB map
      - Interactive   : Opens the advanced Partition, Dual-OTA & NVS Manager console
#>

[CmdletBinding()]
param(
    [ValidateSet(
        "KeepNvs", "AppOnly", "Factory", "DualOta",
        "WipeNvs", "WipeStorage", "WipeEpdFrame",
        "SetBootSlot", "CustomWrite", "CustomErase",
        "Inspect", "Interactive"
    )]
    [string]$Profile = "KeepNvs",

    [ValidateSet("ota_0", "ota_1", "both")]
    [string]$TargetSlot = "ota_0",

    [switch]$KeepNvs,

    [switch]$KeepPartitionTable,

    [switch]$KeepOtaData,

    [string]$TargetPartition = "",

    [string]$Binary = "",

    [uint32]$Offset = [uint32]::MaxValue,

    [uint32]$EraseLength = 0,

    [string[]]$Segments = @(),

    [string]$Port = "",

    [int]$Baud = 460800,

    [int]$FlashSizeMB = 8,

    [switch]$NoVerify,

    [switch]$Interactive
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

if ($Interactive.IsPresent) {
    $Profile = "Interactive"
}

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

namespace H1OS.Flasher
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

        /// <summary>
        /// Builds the complete 8MB partition map (including system regions bootloader @ 0x0 and partition-table @ 0x8000)
        /// by parsing bins/partition-table.bin (binary 0x50AA format), partitions.csv, or the canonical H1OS 8MB Dual-OTA layout.
        /// </summary>
        public static List<PartitionEntry> LoadPartitionMap(string distRoot)
        {
            List<PartitionEntry> map = new List<PartitionEntry>();

            // System Region 0: Bootloader (0x000000 .. 0x007FFF, 32 KB reserved window)
            map.Add(new PartitionEntry {
                Name = "bootloader", TypeStr = "system", SubTypeStr = "boot",
                TypeCode = 0xFE, SubTypeCode = 0x00, Offset = 0x000000, Size = 0x008000, IsSystemRegion = true
            });

            // System Region 1: Partition Table (0x008000 .. 0x008FFF, 4 KB)
            map.Add(new PartitionEntry {
                Name = "partition-table", TypeStr = "system", SubTypeStr = "part",
                TypeCode = 0xFE, SubTypeCode = 0x01, Offset = 0x008000, Size = 0x001000, IsSystemRegion = true
            });

            string binPath = Path.Combine(distRoot, "bins", "partition-table.bin");
            string csvPath = Path.Combine(distRoot, "partitions.csv");

            List<PartitionEntry> parsed = null;
            if (File.Exists(binPath))
            {
                try { parsed = ParseBinaryPartitionTable(File.ReadAllBytes(binPath)); }
                catch { parsed = null; }
            }

            if ((parsed == null || parsed.Count == 0) && File.Exists(csvPath))
            {
                try { parsed = ParseCsvPartitionTable(File.ReadAllLines(csvPath)); }
                catch { parsed = null; }
            }

            if (parsed == null || parsed.Count == 0)
            {
                parsed = GetCanonicalH1OsPartitions();
            }

            map.AddRange(parsed);
            return map;
        }

        public static List<PartitionEntry> ParseBinaryPartitionTable(byte[] data)
        {
            List<PartitionEntry> list = new List<PartitionEntry>();
            if (data == null || data.Length < 32) return list;

            for (int off = 0; off + 32 <= data.Length; off += 32)
            {
                ushort magic = BitConverter.ToUInt16(data, off);
                if (magic == 0xEBEB || magic == 0xFFFF)
                {
                    // 0xEBEB = MD5 checksum row; 0xFFFF = end of table
                    if (magic == 0xFFFF) break;
                    continue;
                }
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
            return list;
        }

        public static List<PartitionEntry> ParseCsvPartitionTable(string[] lines)
        {
            List<PartitionEntry> list = new List<PartitionEntry>();
            uint runningOffset = 0x9000; // Standard ESP-IDF first partition offset after 0x8000 partition table

            foreach (string rawLine in lines)
            {
                string line = rawLine.Trim();
                if (string.IsNullOrEmpty(line) || line.StartsWith("#")) continue;

                string[] cols = line.Split(',');
                if (cols.Length < 5) continue;

                string name = cols[0].Trim();
                string typeStr = cols[1].Trim().ToLowerInvariant();
                string subTypeStr = cols[2].Trim().ToLowerInvariant();
                string offStr = cols[3].Trim();
                string sizeStr = cols[4].Trim();

                bool isApp = (typeStr == "app" || typeStr == "0" || typeStr == "0x00");
                uint align = isApp ? 0x10000u : 0x1000u; // ESP-IDF aligns app partitions to 64KB, data to 4KB

                uint offset;
                if (!string.IsNullOrEmpty(offStr))
                {
                    offset = ParseSizeOrHex(offStr);
                }
                else
                {
                    offset = ((runningOffset + align - 1) / align) * align;
                }

                uint size = ParseSizeOrHex(sizeStr);
                runningOffset = offset + size;

                list.Add(new PartitionEntry {
                    Name = name,
                    TypeStr = typeStr,
                    SubTypeStr = subTypeStr,
                    TypeCode = isApp ? (byte)0x00 : (byte)0x01,
                    SubTypeCode = 0,
                    Offset = offset,
                    Size = size,
                    IsSystemRegion = false
                });
            }
            return list;
        }

        public static List<PartitionEntry> GetCanonicalH1OsPartitions()
        {
            // Canonical H1OS 8MB Dual-Slot OTA Layout from partitions.csv
            return new List<PartitionEntry> {
                new PartitionEntry { Name = "nvs",       TypeStr = "data", SubTypeStr = "nvs",       TypeCode = 1, SubTypeCode = 0x02, Offset = 0x009000, Size = 0x014000 },
                new PartitionEntry { Name = "otadata",   TypeStr = "data", SubTypeStr = "ota",       TypeCode = 1, SubTypeCode = 0x00, Offset = 0x01D000, Size = 0x002000 },
                new PartitionEntry { Name = "phy_init",  TypeStr = "data", SubTypeStr = "phy",       TypeCode = 1, SubTypeCode = 0x01, Offset = 0x01F000, Size = 0x001000 },
                new PartitionEntry { Name = "ota_0",     TypeStr = "app",  SubTypeStr = "ota_0",     TypeCode = 0, SubTypeCode = 0x10, Offset = 0x020000, Size = 0x300000 },
                new PartitionEntry { Name = "ota_1",     TypeStr = "app",  SubTypeStr = "ota_1",     TypeCode = 0, SubTypeCode = 0x11, Offset = 0x320000, Size = 0x300000 },
                new PartitionEntry { Name = "storage",   TypeStr = "data", SubTypeStr = "spiffs",    TypeCode = 1, SubTypeCode = 0x82, Offset = 0x620000, Size = 0x1DC000 },
                new PartitionEntry { Name = "epd_frame", TypeStr = "data", SubTypeStr = "undefined", TypeCode = 1, SubTypeCode = 0x06, Offset = 0x7FC000, Size = 0x004000 }
            };
        }

        public static uint ParseSizeOrHex(string val)
        {
            string s = val.Trim();
            if (s.StartsWith("0x", StringComparison.OrdinalIgnoreCase))
            {
                return uint.Parse(s.Substring(2), NumberStyles.HexNumber, CultureInfo.InvariantCulture);
            }
            if (s.EndsWith("M", StringComparison.OrdinalIgnoreCase) || s.EndsWith("MB", StringComparison.OrdinalIgnoreCase))
            {
                string num = s.TrimEnd('M', 'm', 'B', 'b');
                return uint.Parse(num, CultureInfo.InvariantCulture) * 1024u * 1024u;
            }
            if (s.EndsWith("K", StringComparison.OrdinalIgnoreCase) || s.EndsWith("KB", StringComparison.OrdinalIgnoreCase))
            {
                string num = s.TrimEnd('K', 'k', 'B', 'b');
                return uint.Parse(num, CultureInfo.InvariantCulture) * 1024u;
            }
            return uint.Parse(s, CultureInfo.InvariantCulture);
        }

        private static string DecodeType(byte t)
        {
            if (t == 0x00) return "app";
            if (t == 0x01) return "data";
            return "0x" + t.ToString("X2");
        }

        private static string DecodeSubType(byte t, byte st)
        {
            if (t == 0x00)
            {
                if (st == 0x00) return "factory";
                if (st >= 0x10 && st <= 0x1F) return "ota_" + (st - 0x10);
                if (st == 0x20) return "test";
            }
            else if (t == 0x01)
            {
                switch (st)
                {
                    case 0x00: return "ota";
                    case 0x01: return "phy";
                    case 0x02: return "nvs";
                    case 0x03: return "coredump";
                    case 0x04: return "nvs_keys";
                    case 0x06: return "undefined";
                    case 0x81: return "fat";
                    case 0x82: return "spiffs";
                    case 0x83: return "littlefs";
                }
            }
            return "0x" + st.ToString("X2");
        }

        /// <summary>
        /// Synthesizes an 8KB (0x2000) ESP-IDF otadata image selecting either ota_0 (seq=1) or ota_1 (seq=2).
        /// Matches ESP-IDF bootloader_common_ota_select_crc(esp_rom_crc32_le(0xFFFFFFFF, &ota_seq, 4)).
        /// </summary>
        public static byte[] BuildOtaDataPayload(string targetSlot)
        {
            byte[] buf = new byte[0x2000];
            for (int i = 0; i < buf.Length; i++) buf[i] = 0xFF;

            uint otaSeq = string.Equals(targetSlot, "ota_1", StringComparison.OrdinalIgnoreCase) ? 2u : 1u;
            uint otaState = 1u; // ESP_OTA_IMG_VALID = 1
            byte[] seqBytes = BitConverter.GetBytes(otaSeq);
            uint crc = ComputeEspRomCrc32Le(0xFFFFFFFF, seqBytes);

            // Write 32-byte esp_ota_select_entry_t into Sector 0 (0x1D000), leaving Sector 1 (0x1E000) as 0xFF
            Buffer.BlockCopy(seqBytes, 0, buf, 0, 4);
            // bytes 4..23 are seq_label (20 x 0xFF)
            Buffer.BlockCopy(BitConverter.GetBytes(otaState), 0, buf, 24, 4);
            Buffer.BlockCopy(BitConverter.GetBytes(crc), 0, buf, 28, 4);

            return buf;
        }

        public static uint ComputeEspRomCrc32Le(uint initCrc, byte[] data)
        {
            // In ESP-ROM, esp_rom_crc32_le(uint32_t crc, const uint8_t *buf, uint32_t len)
            // starts with crc = ~crc and returns ~crc.
            uint crc = ~initCrc;
            foreach (byte b in data)
            {
                crc ^= b;
                for (int k = 0; k < 8; k++)
                {
                    crc = ((crc & 1) != 0) ? ((crc >> 1) ^ 0xEDB88320u) : (crc >> 1);
                }
            }
            return ~crc;
        }
    }

    public class Esp32S3RomFlasher : IDisposable
    {
        private const byte SLIP_END     = 0xC0;
        private const byte SLIP_ESC     = 0xDB;
        private const byte SLIP_ESC_END = 0xDC;
        private const byte SLIP_ESC_ESC = 0xDD;

        // ESP32-S3 Mask ROM Opcodes
        private const byte ESP_FLASH_BEGIN        = 0x02;
        private const byte ESP_FLASH_DATA         = 0x03;
        private const byte ESP_FLASH_END          = 0x04;
        private const byte ESP_SYNC               = 0x08;
        private const byte ESP_WRITE_REG          = 0x09;
        private const byte ESP_READ_REG           = 0x0A;
        private const byte ESP_SPI_SET_PARAMS     = 0x0B;
        private const byte ESP_SPI_ATTACH         = 0x0D;
        private const byte ESP_CHANGE_BAUDRATE    = 0x0F;
        private const byte ESP_SPI_FLASH_MD5      = 0x13;
        private const byte ESP_GET_SECURITY_INFO  = 0x14;

        private const byte ESP_CHECKSUM_MAGIC     = 0xEF;
        private const int  FLASH_SECTOR_SIZE      = 4096;
        private const int  FLASH_BLOCK_SIZE       = 4096;
        private const uint RTC_CNTL_OPTION1_REG      = 0x60008128;
        private const uint RTC_CNTL_WDTWPROTECT_REG  = 0x600080B0;
        private const uint RTC_CNTL_WDTCONFIG0_REG   = 0x60008098;
        private const uint RTC_CNTL_WDT_WKEY         = 0x50D83AA1;
        private const uint RTC_CNTL_SWD_WPROTECT_REG = 0x600080B8;
        private const uint RTC_CNTL_SWD_CONF_REG     = 0x600080B4;
        private const uint RTC_CNTL_SWD_WKEY         = 0x8F1D312A;
        private const uint RTC_CNTL_SWD_AUTO_FEED_EN = 0x80000000;

        public void WriteReg(uint addr, uint value, uint mask)
        {
            byte[] payload = new byte[16];
            Buffer.BlockCopy(BitConverter.GetBytes(addr),  0, payload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(value), 0, payload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(mask),  0, payload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0), 0, payload, 12, 4);
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

        public void DisableWatchdogs()
        {
            try
            {
                WriteReg(RTC_CNTL_WDTWPROTECT_REG, RTC_CNTL_WDT_WKEY, 0xFFFFFFFF);
                WriteReg(RTC_CNTL_WDTCONFIG0_REG, 0, 0xFFFFFFFF);
                WriteReg(RTC_CNTL_WDTWPROTECT_REG, 0, 0xFFFFFFFF);

                WriteReg(RTC_CNTL_SWD_WPROTECT_REG, RTC_CNTL_SWD_WKEY, 0xFFFFFFFF);
                uint swdConf = ReadReg(RTC_CNTL_SWD_CONF_REG);
                WriteReg(RTC_CNTL_SWD_CONF_REG, swdConf | RTC_CNTL_SWD_AUTO_FEED_EN, 0xFFFFFFFF);
                WriteReg(RTC_CNTL_SWD_WPROTECT_REG, 0, 0xFFFFFFFF);
            }
            catch { }
        }

        private SerialPort _port;
        private string _portName;
        private int _baudRate;
        private bool _isNativeUsb;

        public Esp32S3RomFlasher(string portName, int baudRate, bool isNativeUsb)
        {
            _portName = portName;
            _baudRate = baudRate;
            _isNativeUsb = isNativeUsb;
        }

        private void OpenPort(int baud)
        {
            ClosePort();
            _port = new SerialPort(_portName, baud, Parity.None, 8, StopBits.One);
            _port.Handshake = Handshake.None;
            _port.ReadBufferSize = 65536;
            _port.WriteBufferSize = 65536;
            _port.ReadTimeout = 3000;
            _port.WriteTimeout = 5000;
            _port.Open();
        }

        public void ClosePort()
        {
            if (_port != null)
            {
                try { if (_port.IsOpen) _port.Close(); } catch { }
                try { _port.Dispose(); } catch { }
                _port = null;
            }
        }

        public void Dispose()
        {
            ClosePort();
        }

        public void EnterBootloader()
        {
            Console.WriteLine("[*] Triggering ESP32-S3 hardware reset into Mask ROM Download Mode...");

            for (int attempt = 1; attempt <= 3; attempt++)
            {
                try
                {
                    OpenPort(115200);

                    if (_isNativeUsb)
                    {
                        // ESP32-S3 internal USB-Serial/JTAG Reset Sequence (USBJTAGSerialReset)
                        _port.RtsEnable = false;
                        _port.DtrEnable = false;
                        Thread.Sleep(100);

                        _port.DtrEnable = true;
                        _port.RtsEnable = false;
                        Thread.Sleep(100);

                        _port.RtsEnable = true;
                        _port.DtrEnable = false;
                        _port.RtsEnable = true;
                        Thread.Sleep(100);

                        _port.RtsEnable = false;
                        _port.DtrEnable = false;
                    }
                    else
                    {
                        _port.DtrEnable = false;
                        _port.RtsEnable = true;
                        Thread.Sleep(100);
                        _port.DtrEnable = true;
                        _port.RtsEnable = false;
                        Thread.Sleep(50);
                        _port.DtrEnable = false;
                    }

                    ClosePort();
                    Thread.Sleep(_isNativeUsb ? 450 : 120);
                    ReopenPortWithRetry(115200, 4000);
                    return;
                }
                catch (Exception ex)
                {
                    ClosePort();
                    if (attempt == 3)
                    {
                        throw new Exception("Failed to reset ESP32-S3 on " + _portName + ": " + ex.Message);
                    }
                    Thread.Sleep(500);
                }
            }
        }

        private void ReopenPortWithRetry(int baud, int maxWaitMs)
        {
            Stopwatch sw = Stopwatch.StartNew();
            Exception lastErr = null;
            while (sw.ElapsedMilliseconds < maxWaitMs)
            {
                try
                {
                    OpenPort(baud);
                    _port.DiscardInBuffer();
                    _port.DiscardOutBuffer();
                    return;
                }
                catch (Exception ex)
                {
                    lastErr = ex;
                    ClosePort();
                    Thread.Sleep(150);
                }
            }
            throw new Exception("Serial port " + _portName + " did not re-enumerate after reset: " +
                (lastErr != null ? lastErr.Message : "timeout"));
        }

        public void SyncWithRom()
        {
            Console.Write("[*] Synchronizing with ESP32-S3 Mask ROM via SLIP... ");

            byte[] syncPayload = new byte[36];
            syncPayload[0] = 0x07;
            syncPayload[1] = 0x07;
            syncPayload[2] = 0x12;
            syncPayload[3] = 0x20;
            for (int i = 4; i < 36; i++) syncPayload[i] = 0x55;

            byte[] syncPacket = BuildCommandPacket(ESP_SYNC, syncPayload, 0);

            for (int cycle = 0; cycle < 3; cycle++)
            {
                if (cycle > 0)
                {
                    Console.Write("\n[*] Retrying hardware bootloader trap (attempt " + (cycle + 1) + ")... ");
                    EnterBootloader();
                }

                for (int i = 0; i < 10; i++)
                {
                    try
                    {
                        _port.DiscardInBuffer();
                        SendSlipPacket(syncPacket);

                        uint val;
                        byte[] resp = ReadCommandResponse(ESP_SYNC, 250, out val);
                        if (resp != null)
                        {
                            DrainExtraSyncResponses();
                            Console.WriteLine("Connected!");
                            VerifyChipIdentity();

                            if (!_isNativeUsb && _baudRate > 115200)
                            {
                                ChangeBaudRate(_baudRate);
                            }
                            return;
                        }
                    }
                    catch (TimeoutException) { }
                    catch (IOException)
                    {
                        ReopenPortWithRetry(115200, 2000);
                    }
                }
            }

            Console.WriteLine("Failed!");
            throw new Exception("Timed out waiting for ESP32-S3 ROM SYNC handshake on " + _portName +
                ". Hold BOOT (GPIO0), tap RESET, and try again.");
        }

        private void DrainExtraSyncResponses()
        {
            int oldTimeout = _port.ReadTimeout;
            _port.ReadTimeout = 60;
            try
            {
                for (int i = 0; i < 12; i++)
                {
                    byte[] pkt = ReadRawSlipFrame(60);
                    if (pkt == null) break;
                }
            }
            catch { }
            finally
            {
                _port.ReadTimeout = oldTimeout;
                try { _port.DiscardInBuffer(); } catch { }
            }
        }

        private void VerifyChipIdentity()
        {
            try
            {
                uint val;
                byte[] secInfo = ExecuteCommand(ESP_GET_SECURITY_INFO, new byte[0], 0, 1000, out val);
                if (secInfo != null && secInfo.Length >= 16)
                {
                    uint chipId = BitConverter.ToUInt32(secInfo, 12);
                    if (chipId == 9)
                    {
                        Console.WriteLine("[+] Confirmed Target Silicon : ESP32-S3 (Chip ID: 0x0009, Mask ROM Loader)");
                        return;
                    }
                }
            }
            catch { }
        }

        private void ChangeBaudRate(int newBaud)
        {
            Console.Write("[*] Stepping UART baud rate to " + newBaud + " bps... ");
            byte[] payload = new byte[8];
            Buffer.BlockCopy(BitConverter.GetBytes((uint)newBaud), 0, payload, 0, 4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0), 0, payload, 4, 4);

            uint val;
            ExecuteCommand(ESP_CHANGE_BAUDRATE, payload, 0, 1000, out val);
            Thread.Sleep(50);
            _port.BaudRate = newBaud;
            Thread.Sleep(50);
            _port.DiscardInBuffer();
            Console.WriteLine("OK.");
        }

        public void AttachAndConfigureSpiFlash(int flashSizeMB)
        {
            Console.Write("[*] Attaching internal SPI Flash bus (" + flashSizeMB + "MB DIO 80MHz)... ");

            byte[] attachPayload = new byte[8];
            uint val;
            ExecuteCommand(ESP_SPI_ATTACH, attachPayload, 0, 3000, out val);

            uint totalBytes = (uint)(flashSizeMB * 1024 * 1024);
            byte[] spiParams = new byte[24];
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0),          0, spiParams, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(totalBytes),       0, spiParams, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)65536),      0, spiParams, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)4096),       0, spiParams, 12, 4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)256),        0, spiParams, 16, 4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0xFFFF),     0, spiParams, 20, 4);

            ExecuteCommand(ESP_SPI_SET_PARAMS, spiParams, 0, 3000, out val);
            Console.WriteLine("Bound.");
        }

        /// <summary>
        /// Erases an arbitrary sector-aligned flash region (or the full 8MB die) to 0xFF using
        /// the ESP32-S3 Mask ROM's native ESP_FLASH_BEGIN (0x02) erase engine.
        /// </summary>
        public void EraseFlashRegion(uint startOffset, uint byteLength, string regionLabel)
        {
            if ((startOffset % FLASH_SECTOR_SIZE) != 0)
            {
                throw new Exception(string.Format("Erase start offset 0x{0:X} must be 4KB sector-aligned.", startOffset));
            }
            uint alignedLen = ((byteLength + (uint)FLASH_SECTOR_SIZE - 1u) / (uint)FLASH_SECTOR_SIZE) * (uint)FLASH_SECTOR_SIZE;
            uint maxStep = 256u * 1024u; // 256KB chunks for smooth progress & safe ROM timeouts
            uint totalSteps = (alignedLen + maxStep - 1u) / maxStep;

            Console.WriteLine(string.Format("\n[*] Scrubbing {0} (0x{1:X6} .. 0x{2:X6}, {3:N1} KB -> 0xFF)...",
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
                Console.Write(string.Format("\r    Erasing 0x{0:X6} .. 0x{1:X6} [{2,3}%]",
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
            Console.WriteLine(string.Format("\n    [+] Scrubbed {0} to 0xFF in {1:F1}s.", regionLabel, sw.Elapsed.TotalSeconds));
        }

        public void FlashSegment(FlashSegment segment, bool verifyMd5, bool preserveNvsGap)
        {
            byte[] rawBytes = segment.RawPayload;
            if (rawBytes == null)
            {
                if (!File.Exists(segment.FilePath))
                {
                    throw new FileNotFoundException("Firmware binary not found: " + segment.FilePath);
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
                    "Binary '{0}' ({1:N0} bytes) exceeds partition capacity ({2:N0} bytes) at 0x{3:X6}!",
                    segment.Label, rawBytes.Length, segment.MaxAllowedSize, segment.Offset));
            }

            if ((segment.Offset % FLASH_SECTOR_SIZE) != 0)
            {
                throw new Exception(string.Format("Flash offset 0x{0:X} is not aligned to 4096-byte sector boundary.", segment.Offset));
            }

            if (preserveNvsGap && segment.Offset == 0 && rawBytes.Length > 0x20000)
            {
                List<Tuple<uint, byte[], string>> subSegments = SplitMonolithicHeaderGaps(rawBytes, segment.Label);
                if (subSegments.Count > 1)
                {
                    foreach (var sub in subSegments)
                    {
                        FlashByteSlice(sub.Item1, sub.Item2, sub.Item3, verifyMd5);
                    }
                    return;
                }
            }

            FlashByteSlice(segment.Offset, rawBytes, segment.Label, verifyMd5);
        }

        private List<Tuple<uint, byte[], string>> SplitMonolithicHeaderGaps(byte[] rawBytes, string baseLabel)
        {
            List<Tuple<uint, byte[], string>> slices = new List<Tuple<uint, byte[], string>>();
            int headerLimit = Math.Min(rawBytes.Length, 0x20000);
            int totalHeaderSectors = headerLimit / FLASH_SECTOR_SIZE;

            int sec = 0;
            while (sec < totalHeaderSectors)
            {
                if (IsSectorAllFF(rawBytes, sec * FLASH_SECTOR_SIZE))
                {
                    sec++;
                    continue;
                }

                int startSec = sec;
                while (sec < totalHeaderSectors && !IsSectorAllFF(rawBytes, sec * FLASH_SECTOR_SIZE))
                {
                    sec++;
                }

                uint sliceOffset = (uint)(startSec * FLASH_SECTOR_SIZE);
                int sliceLen = (sec - startSec) * FLASH_SECTOR_SIZE;
                while (sliceLen > 16 && rawBytes[(int)sliceOffset + sliceLen - 1] == 0xFF)
                {
                    sliceLen--;
                }

                byte[] buf = new byte[sliceLen];
                Buffer.BlockCopy(rawBytes, (int)sliceOffset, buf, 0, sliceLen);
                string label = string.Format("{0} [0x{1:X5}]", baseLabel, sliceOffset);
                slices.Add(new Tuple<uint, byte[], string>(sliceOffset, buf, label));
            }

            if (rawBytes.Length > 0x20000)
            {
                int appLen = rawBytes.Length - 0x20000;
                byte[] appBuf = new byte[appLen];
                Buffer.BlockCopy(rawBytes, 0x20000, appBuf, 0, appLen);
                slices.Add(new Tuple<uint, byte[], string>(0x20000, appBuf, baseLabel + " [App 0x20000]"));
            }

            return slices;
        }

        private static bool IsSectorAllFF(byte[] data, int sectorOffset)
        {
            int end = Math.Min(data.Length, sectorOffset + FLASH_SECTOR_SIZE);
            for (int i = sectorOffset; i < end; i++)
            {
                if (data[i] != 0xFF) return false;
            }
            return true;
        }

        private void FlashByteSlice(uint offset, byte[] rawBytes, string label, bool verifyMd5)
        {
            int paddedLength = ((rawBytes.Length + FLASH_BLOCK_SIZE - 1) / FLASH_BLOCK_SIZE) * FLASH_BLOCK_SIZE;
            byte[] paddedBytes = new byte[paddedLength];
            Buffer.BlockCopy(rawBytes, 0, paddedBytes, 0, rawBytes.Length);
            for (int i = rawBytes.Length; i < paddedLength; i++)
            {
                paddedBytes[i] = 0xFF;
            }

            uint numBlocks = (uint)(paddedLength / FLASH_BLOCK_SIZE);
            uint eraseSize = (uint)paddedLength;

            Console.WriteLine(string.Format("\n[*] Flashing {0} ({1:N1} KB) -> 0x{2:X6} ({3} blocks)...",
                label, rawBytes.Length / 1024.0, offset, numBlocks));

            byte[] beginPayload = new byte[20];
            Buffer.BlockCopy(BitConverter.GetBytes(eraseSize),               0, beginPayload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(numBlocks),               0, beginPayload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)FLASH_BLOCK_SIZE),  0, beginPayload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(offset),                  0, beginPayload, 12, 4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                 0, beginPayload, 16, 4);

            int beginTimeoutMs = Math.Max(15000, 6000 + (int)((eraseSize / 65536) * 2000));
            uint val;
            ExecuteCommand(ESP_FLASH_BEGIN, beginPayload, 0, beginTimeoutMs, out val);

            Stopwatch sw = Stopwatch.StartNew();
            byte[] blockPayload = new byte[16 + FLASH_BLOCK_SIZE];
            Buffer.BlockCopy(BitConverter.GetBytes((uint)FLASH_BLOCK_SIZE), 0, blockPayload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                0, blockPayload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0),                0, blockPayload, 12, 4);

            for (uint seq = 0; seq < numBlocks; seq++)
            {
                int srcOffset = (int)(seq * FLASH_BLOCK_SIZE);
                Buffer.BlockCopy(BitConverter.GetBytes(seq), 0, blockPayload, 4, 4);
                Buffer.BlockCopy(paddedBytes, srcOffset, blockPayload, 16, FLASH_BLOCK_SIZE);

                uint checksum = ComputeXorChecksum(paddedBytes, srcOffset, FLASH_BLOCK_SIZE);

                bool blockOk = false;
                Exception lastBlockErr = null;
                for (int retry = 0; retry < 3; retry++)
                {
                    try
                    {
                        ExecuteCommand(ESP_FLASH_DATA, blockPayload, checksum, 5000, out val);
                        blockOk = true;
                        break;
                    }
                    catch (Exception ex)
                    {
                        lastBlockErr = ex;
                        Thread.Sleep(50);
                        try { _port.DiscardInBuffer(); } catch { }
                    }
                }

                if (!blockOk)
                {
                    Console.WriteLine();
                    throw new Exception(string.Format("Failed writing block {0}/{1} at 0x{2:X6}: {3}",
                        seq, numBlocks, offset + srcOffset,
                        lastBlockErr != null ? lastBlockErr.Message : "unknown error"));
                }

                if ((seq % 4 == 0) || (seq == numBlocks - 1))
                {
                    RenderProgressBar(seq + 1, numBlocks, sw.Elapsed.TotalSeconds, paddedLength);
                }
            }

            sw.Stop();
            double kbps = (paddedLength / 1024.0) / Math.Max(0.05, sw.Elapsed.TotalSeconds);
            Console.WriteLine(string.Format("\n    [+] Wrote {0:N0} bytes in {1:F1}s ({2:F1} KB/s).",
                rawBytes.Length, sw.Elapsed.TotalSeconds, kbps));

            if (verifyMd5)
            {
                VerifySegmentMd5(offset, rawBytes);
            }
        }

        public string ComputeOnChipMd5(uint offset, uint length)
        {
            byte[] md5Payload = new byte[16];
            Buffer.BlockCopy(BitConverter.GetBytes(offset),  0, md5Payload, 0,  4);
            Buffer.BlockCopy(BitConverter.GetBytes(length),  0, md5Payload, 4,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0), 0, md5Payload, 8,  4);
            Buffer.BlockCopy(BitConverter.GetBytes((uint)0), 0, md5Payload, 12, 4);

            int timeoutMs = Math.Max(5000, 2000 + (int)((length / 65536) * 600));
            uint val;
            byte[] respData = ExecuteCommand(ESP_SPI_FLASH_MD5, md5Payload, 0, timeoutMs, out val);
            return ExtractMd5FromResponse(respData);
        }

        private void VerifySegmentMd5(uint offset, byte[] expectedBytes)
        {
            Console.Write("    [*] Verifying on-chip SPI Flash MD5... ");
            string hostMd5 = ComputeHostMd5Hex(expectedBytes);
            string romMd5 = ComputeOnChipMd5(offset, (uint)expectedBytes.Length);

            if (string.IsNullOrEmpty(romMd5))
            {
                Console.WriteLine("Skipped (unexpected MD5 payload length).");
                return;
            }

            if (!string.Equals(hostMd5, romMd5, StringComparison.OrdinalIgnoreCase))
            {
                Console.WriteLine("MISMATCH!");
                throw new Exception(string.Format("MD5 verification failed at 0x{0:X6}! Host={1}, Chip={2}",
                    offset, hostMd5, romMd5));
            }

            Console.WriteLine("OK (" + romMd5.Substring(0, 12) + "...).");
        }

        public static string ComputeHostMd5Hex(byte[] bytes)
        {
            using (MD5 md5 = MD5.Create())
            {
                byte[] hash = md5.ComputeHash(bytes);
                StringBuilder sb = new StringBuilder(32);
                foreach (byte b in hash) sb.Append(b.ToString("x2"));
                return sb.ToString();
            }
        }

        public static string ComputeBlankRegionMd5Hex(uint length)
        {
            byte[] blank = new byte[length];
            for (int i = 0; i < blank.Length; i++) blank[i] = 0xFF;
            return ComputeHostMd5Hex(blank);
        }

        private string ExtractMd5FromResponse(byte[] respData)
        {
            if (respData == null) return null;
            if (respData.Length >= 36)
            {
                return Encoding.ASCII.GetString(respData, 0, 32).ToLowerInvariant();
            }
            if (respData.Length >= 18)
            {
                StringBuilder sb = new StringBuilder(32);
                for (int i = 0; i < 16; i++) sb.Append(respData[i].ToString("x2"));
                return sb.ToString();
            }
            return null;
        }

        public void FinishAndReboot()
        {
            Console.Write("\n[*] Finalizing flash & rebooting into H1OS firmware... ");

            try
            {
                byte[] writeRegPayload = new byte[16];
                Buffer.BlockCopy(BitConverter.GetBytes(RTC_CNTL_OPTION1_REG), 0, writeRegPayload, 0,  4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)0),              0, writeRegPayload, 4,  4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)0x1),            0, writeRegPayload, 8,  4);
                Buffer.BlockCopy(BitConverter.GetBytes((uint)0),              0, writeRegPayload, 12, 4);
                uint val;
                ExecuteCommand(ESP_WRITE_REG, writeRegPayload, 0, 500, out val);
            }
            catch { }

            try
            {
                byte[] endPayload = BitConverter.GetBytes((uint)0);
                uint val;
                ExecuteCommand(ESP_FLASH_END, endPayload, 0, 1000, out val);
            }
            catch { }

            try
            {
                if (_port != null && _port.IsOpen)
                {
                    _port.DtrEnable = false;
                    _port.RtsEnable = true;
                    Thread.Sleep(100);
                    _port.RtsEnable = false;
                    Thread.Sleep(50);
                }
            }
            catch { }
            finally
            {
                ClosePort();
            }

            Console.WriteLine("Done!");
        }

        private void RenderProgressBar(uint currentBlock, uint totalBlocks, double elapsedSec, int totalBytes)
        {
            int width = 28;
            double ratio = (double)currentBlock / totalBlocks;
            int filled = (int)Math.Round(ratio * width);
            if (filled > width) filled = width;

            string bar = new string('#', filled) + new string('-', width - filled);
            int pct = (int)Math.Round(ratio * 100.0);
            double kbWritten = (currentBlock * FLASH_BLOCK_SIZE) / 1024.0;
            double kbTotal = totalBytes / 1024.0;

            Console.Write(string.Format("\r    [{0}] {1,3}% ({2,6:F1} / {3,6:F1} KB)",
                bar, pct, Math.Min(kbWritten, kbTotal), kbTotal));
        }

        private static uint ComputeXorChecksum(byte[] data, int offset, int count)
        {
            byte chk = ESP_CHECKSUM_MAGIC;
            int end = offset + count;
            for (int i = offset; i < end; i++) chk ^= data[i];
            return chk;
        }

        private static byte[] BuildCommandPacket(byte op, byte[] data, uint checksum)
        {
            ushort len = (ushort)(data != null ? data.Length : 0);
            byte[] pkt = new byte[8 + len];
            pkt[0] = 0x00;
            pkt[1] = op;
            pkt[2] = (byte)(len & 0xFF);
            pkt[3] = (byte)((len >> 8) & 0xFF);
            pkt[4] = (byte)(checksum & 0xFF);
            pkt[5] = (byte)((checksum >> 8) & 0xFF);
            pkt[6] = (byte)((checksum >> 16) & 0xFF);
            pkt[7] = (byte)((checksum >> 24) & 0xFF);
            if (len > 0) Buffer.BlockCopy(data, 0, pkt, 8, len);
            return pkt;
        }

        private void SendSlipPacket(byte[] rawPacket)
        {
            byte[] encoded = new byte[rawPacket.Length * 2 + 2];
            int idx = 0;
            encoded[idx++] = SLIP_END;

            for (int i = 0; i < rawPacket.Length; i++)
            {
                byte b = rawPacket[i];
                if (b == SLIP_END)
                {
                    encoded[idx++] = SLIP_ESC;
                    encoded[idx++] = SLIP_ESC_END;
                }
                else if (b == SLIP_ESC)
                {
                    encoded[idx++] = SLIP_ESC;
                    encoded[idx++] = SLIP_ESC_ESC;
                }
                else
                {
                    encoded[idx++] = b;
                }
            }

            encoded[idx++] = SLIP_END;
            _port.Write(encoded, 0, idx);
        }

        private byte[] ExecuteCommand(byte op, byte[] payload, uint checksum, int timeoutMs, out uint regValue)
        {
            byte[] cmdPkt = BuildCommandPacket(op, payload, checksum);
            SendSlipPacket(cmdPkt);
            return ReadCommandResponse(op, timeoutMs, out regValue);
        }

        private byte[] ReadCommandResponse(byte expectedOp, int timeoutMs, out uint regValue)
        {
            regValue = 0;
            Stopwatch sw = Stopwatch.StartNew();

            while (sw.ElapsedMilliseconds < timeoutMs)
            {
                int remaining = timeoutMs - (int)sw.ElapsedMilliseconds;
                if (remaining <= 0) break;

                byte[] frame = ReadRawSlipFrame(remaining);
                if (frame == null || frame.Length < 8) continue;
                if (frame[0] != 0x01 || frame[1] != expectedOp) continue;

                regValue = BitConverter.ToUInt32(frame, 4);
                int actualPayloadLen = frame.Length - 8;
                byte[] data = new byte[actualPayloadLen];
                if (actualPayloadLen > 0)
                {
                    Buffer.BlockCopy(frame, 8, data, 0, actualPayloadLen);
                }

                if (actualPayloadLen >= 4)
                {
                    byte status = data[actualPayloadLen - 4];
                    byte errCode = data[actualPayloadLen - 3];
                    if (status != 0)
                    {
                        throw new Exception(string.Format("ESP32-S3 ROM command 0x{0:X2} failed with error 0x{1:X2} ({2})",
                            expectedOp, errCode, DescribeRomError(errCode)));
                    }
                }
                else if (actualPayloadLen >= 2)
                {
                    byte status = data[actualPayloadLen - 2];
                    byte errCode = data[actualPayloadLen - 1];
                    if (status != 0)
                    {
                        throw new Exception(string.Format("Bootloader command 0x{0:X2} failed with error 0x{1:X2} ({2})",
                            expectedOp, errCode, DescribeRomError(errCode)));
                    }
                }

                return data;
            }

            throw new TimeoutException(string.Format("Timed out waiting for response to opcode 0x{0:X2} ({1} ms).",
                expectedOp, timeoutMs));
        }

        private byte[] ReadRawSlipFrame(int timeoutMs)
        {
            _port.ReadTimeout = Math.Max(50, timeoutMs);
            Stopwatch sw = Stopwatch.StartNew();

            while (true)
            {
                if (sw.ElapsedMilliseconds >= timeoutMs) throw new TimeoutException("SLIP frame start timeout.");
                int b = _port.ReadByte();
                if (b == SLIP_END) break;
            }

            List<byte> buf = new List<byte>(128);
            bool inEscape = false;

            while (true)
            {
                if (sw.ElapsedMilliseconds >= timeoutMs) throw new TimeoutException("SLIP frame body timeout.");

                int readVal = _port.ReadByte();
                if (readVal < 0) continue;
                byte b = (byte)readVal;

                if (inEscape)
                {
                    if (b == SLIP_ESC_END) buf.Add(SLIP_END);
                    else if (b == SLIP_ESC_ESC) buf.Add(SLIP_ESC);
                    else buf.Add(b);
                    inEscape = false;
                }
                else if (b == SLIP_ESC)
                {
                    inEscape = true;
                }
                else if (b == SLIP_END)
                {
                    if (buf.Count == 0) continue;
                    return buf.ToArray();
                }
                else
                {
                    buf.Add(b);
                }
            }
        }

        private static string DescribeRomError(byte code)
        {
            switch (code)
            {
                case 0x01: return "Invalid input parameter";
                case 0x02: return "Failed to allocate memory in ROM";
                case 0x03: return "Failed to send command response";
                case 0x04: return "Failed to receive message";
                case 0x05: return "Invalid message format";
                case 0x06: return "Command execution failed";
                case 0x07: return "XOR checksum mismatch";
                case 0x08: return "SPI flash write/CRC error";
                case 0x09: return "SPI flash read error";
                case 0x0A: return "SPI flash read length error";
                case 0x64: return "Invalid parameter (0x64)";
                default:   return "ROM error code 0x" + code.ToString("X2");
            }
        }
    }
}
"@

if (-not ("H1OS.Flasher.Esp32S3RomFlasher" -as [type])) {
    Add-Type -TypeDefinition $CSharpSource -Language CSharp
}

# ---------------------------------------------------------------------------
# 2. Helper Functions: Discovery, Partition Lookup & Checksum Verification
# ---------------------------------------------------------------------------
function Resolve-DistributionRoot {
    $scriptDir = $PSScriptRoot
    if (-not $scriptDir) {
        $scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
    }
    if ((Split-Path -Leaf $scriptDir) -ieq "engine") {
        return (Split-Path -Parent $scriptDir)
    }
    return $scriptDir
}

function Find-Esp32S3Port {
    param([string]$RequestedPort)

    if (-not [string]::IsNullOrWhiteSpace($RequestedPort)) {
        return [PSCustomObject]@{
            PortName    = $RequestedPort.Trim().ToUpper()
            Description = "User-specified COM port"
            IsNativeUsb = $true
        }
    }

    Write-Host "[*] Scanning Windows PnP tree for ESP32-S3 Native USB (VID_303A)..." -ForegroundColor Cyan

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

    throw "No ESP32-S3 USB serial port detected. Verify the USB-C data cable is connected."
}

function Show-PartitionMapTable {
    param([System.Collections.Generic.List[H1OS.Flasher.PartitionEntry]]$PartMap)

    Write-Host ""
    Write-Host "  ESP32-S3 8MB Dual-Slot OTA Flash Partition Map:" -ForegroundColor Cyan
    Write-Host "  -----------------------------------------------------------------------------------" -ForegroundColor DarkGray
    Write-Host ("  {0,-3} {1,-16} {2,-8} {3,-10} {4,-10} {5,-10} {6,10}" -f "#", "Partition", "Type", "SubType", "Start", "End", "Size (KB)") -ForegroundColor White
    Write-Host "  -----------------------------------------------------------------------------------" -ForegroundColor DarkGray
    $idx = 1
    foreach ($p in $PartMap) {
        $color = if ($p.IsSystemRegion) { "DarkCyan" } elseif ($p.TypeStr -eq "app") { "Green" } else { "Yellow" }
        Write-Host ("  {0,-3} {1,-16} {2,-8} {3,-10} 0x{4:X6}   0x{5:X6}   {6,10:N1}" -f `
            $idx, $p.Name, $p.TypeStr, $p.SubTypeStr, $p.Offset, $p.EndOffset, $p.SizeKB) -ForegroundColor $color
        $idx++
    }
    Write-Host "  -----------------------------------------------------------------------------------" -ForegroundColor DarkGray
    Write-Host ""
}

function Find-DistributionBinaries {
    param([string]$DistRoot)

    $factoryBins = @(Get-ChildItem -Path $DistRoot -Filter "*-factory.bin" -File -ErrorAction SilentlyContinue)
    if ($factoryBins.Count -eq 0 -and (Test-Path (Join-Path $DistRoot "firmware"))) {
        $factoryBins = @(Get-ChildItem -Path (Join-Path $DistRoot "firmware") -Filter "*-factory.bin" -File -ErrorAction SilentlyContinue)
    }

    $appBin = $null
    foreach ($cand in @(
        (Join-Path $DistRoot "h1os.bin"),
        (Join-Path $DistRoot "bins\h1os.bin"),
        (Join-Path $DistRoot "firmware\h1os.bin")
    )) {
        if (Test-Path $cand) { $appBin = $cand; break }
    }
    # Cross-project fallback: auto-discover any app .bin if h1os.bin is not present
    if (-not $appBin) {
        $sysNames = @("bootloader.bin", "partition-table.bin", "ota_data_initial.bin")
        $candBins = @(Get-ChildItem -Path $DistRoot, (Join-Path $DistRoot "bins") -Filter "*.bin" -File -ErrorAction SilentlyContinue |
            Where-Object { ($sysNames -notcontains $_.Name.ToLowerInvariant()) -and ($_.Name -notlike "*-factory.bin") })
        if ($candBins.Count -gt 0) {
            $appBin = $candBins[0].FullName
        }
    }

    $bootBin = Join-Path $DistRoot "bins\bootloader.bin"
    $partBin = Join-Path $DistRoot "bins\partition-table.bin"
    $otaBin  = Join-Path $DistRoot "bins\ota_data_initial.bin"

    return [PSCustomObject]@{
        FactoryBin   = if ($factoryBins.Count -gt 0) { $factoryBins[0].FullName } else { $null }
        AppBin       = $appBin
        Bootloader   = if (Test-Path $bootBin) { $bootBin } else { $null }
        PartTable    = if (Test-Path $partBin) { $partBin } else { $null }
        OtaData      = if (Test-Path $otaBin)  { $otaBin }  else { $null }
    }
}

function Test-BundleChecksums {
    param(
        [string]$DistRoot,
        [H1OS.Flasher.FlashSegment[]]$TargetSegments
    )

    $checksumFile = Join-Path $DistRoot "checksums.sha256"
    if (-not (Test-Path $checksumFile)) { return }

    $expectedMap = @{}
    foreach ($line in (Get-Content $checksumFile)) {
        $trimmed = $line.Trim()
        if ($trimmed -match '^([0-9a-fA-F]{64})\s+(.+)$') {
            $hash = $Matches[1].ToLowerInvariant()
            $relPath = ($Matches[2].Trim() -replace '\\', '/').ToLowerInvariant()
            $expectedMap[$relPath] = $hash
        }
    }

    foreach ($seg in $TargetSegments) {
        if ([string]::IsNullOrWhiteSpace($seg.FilePath)) { continue }
        $fullPath = (Resolve-Path $seg.FilePath).Path
        if ($fullPath.StartsWith($DistRoot, [StringComparison]::OrdinalIgnoreCase)) {
            $rel = $fullPath.Substring($DistRoot.Length).TrimStart('\', '/') -replace '\\', '/'
            $relKey = $rel.ToLowerInvariant()
            if ($expectedMap.ContainsKey($relKey)) {
                $actual = (Get-FileHash -Path $fullPath -Algorithm SHA256).Hash.ToLowerInvariant()
                if ($actual -ne $expectedMap[$relKey]) {
                    throw "Pre-flight SHA-256 mismatch for '$rel'! Expected $($expectedMap[$relKey]), got $actual."
                }
                Write-Host "[+] Pre-flight SHA-256 verified : $rel" -ForegroundColor DarkGray
            }
        }
    }
}

# ---------------------------------------------------------------------------
# 3. Advanced Interactive Console (Partition, Dual-OTA & NVS Manager)
# ---------------------------------------------------------------------------
function Invoke-InteractiveManager {
    param(
        [string]$DistRoot,
        [System.Collections.Generic.List[H1OS.Flasher.PartitionEntry]]$PartMap
    )

    Show-PartitionMapTable -PartMap $PartMap

    Write-Host "  ================ ADVANCED PARTITION, DUAL-OTA & NVS MANAGER ================" -ForegroundColor Green
    Write-Host "  [1] Live On-Chip Flash Inspector  (Read & compare MD5 of all 9 partitions)"
    Write-Host "  [2] Dual-OTA Slot Manager         (Flash ota_0, ota_1, Both, or Switch Active Boot Slot)"
    Write-Host "  [3] NVS & Storage Manager         (Wipe or flash nvs, SPIFFS storage, or epd_frame)"
    Write-Host "  [4] Custom Partition Flasher      (Pick any partition by #/name & flash a .bin)"
    Write-Host "  [5] Custom Partition Eraser       (Pick any partition by #/name & scrub to 0xFF)"
    Write-Host "  [6] Update Firmware (Keep PartTable + Keep NVS intact)"
    Write-Host "  [Q] Quit"
    Write-Host "  ============================================================================" -ForegroundColor Green
    $sel = (Read-Host "  Select operation [1-6, Q]").Trim().ToUpperInvariant()

    switch ($sel) {
        "1" {
            return @{ Profile = "Inspect" }
        }
        "2" {
            Write-Host ""
            Write-Host "  --- Dual-Slot OTA Manager (ota_0 @ 0x20000 | ota_1 @ 0x320000) ---" -ForegroundColor Cyan
            Write-Host "  [1] Flash App to ota_0 (0x020000) and set active boot -> ota_0"
            Write-Host "  [2] Flash App to ota_1 (0x320000) and set active boot -> ota_1"
            Write-Host "  [3] Clone App to BOTH ota_0 & ota_1 (Redundant Dual-Slot Image)"
            Write-Host "  [4] Switch Active Boot Slot to ota_0 (Rewrite otadata @ 0x1D000 only)"
            Write-Host "  [5] Switch Active Boot Slot to ota_1 (Rewrite otadata @ 0x1D000 only)"
            $otaChoice = (Read-Host "  Select OTA action [1-5]").Trim()
            switch ($otaChoice) {
                "1" { return @{ Profile = "AppOnly"; TargetSlot = "ota_0"; KeepPartitionTable = $true; KeepNvs = $true } }
                "2" { return @{ Profile = "AppOnly"; TargetSlot = "ota_1"; KeepPartitionTable = $true; KeepNvs = $true } }
                "3" { return @{ Profile = "DualOta"; TargetSlot = "both";  KeepPartitionTable = $true; KeepNvs = $true } }
                "4" { return @{ Profile = "SetBootSlot"; TargetSlot = "ota_0" } }
                "5" { return @{ Profile = "SetBootSlot"; TargetSlot = "ota_1" } }
                default { throw "Invalid OTA selection." }
            }
        }
        "3" {
            Write-Host ""
            Write-Host "  --- NVS, SPIFFS Storage & ePaper Framebuffer Manager ---" -ForegroundColor Cyan
            Write-Host "  [1] Wipe NVS + PHY Calibration (0x009000, 80KB + 0x01F000, 4KB -> 0xFF)"
            Write-Host "  [2] Wipe SPIFFS Storage Partition (0x620000, 1904KB -> 0xFF)"
            Write-Host "  [3] Wipe ePaper Framebuffer epd_frame (0x7FC000, 16KB -> 0xFF)"
            Write-Host "  [4] Flash pre-built NVS image (.bin) to nvs (0x009000)"
            Write-Host "  [5] Flash pre-built SPIFFS image (.bin) to storage (0x620000)"
            Write-Host "  [6] Flash pre-built Framebuffer (.bin) to epd_frame (0x7FC000)"
            $nvsChoice = (Read-Host "  Select data partition action [1-6]").Trim()
            switch ($nvsChoice) {
                "1" { return @{ Profile = "WipeNvs" } }
                "2" { return @{ Profile = "WipeStorage" } }
                "3" { return @{ Profile = "WipeEpdFrame" } }
                "4" {
                    $binPath = Read-Host "  Enter path to NVS .bin file"
                    return @{ Profile = "CustomWrite"; TargetPartition = "nvs"; Binary = $binPath }
                }
                "5" {
                    $binPath = Read-Host "  Enter path to SPIFFS .bin file"
                    return @{ Profile = "CustomWrite"; TargetPartition = "storage"; Binary = $binPath }
                }
                "6" {
                    $binPath = Read-Host "  Enter path to epd_frame .bin file"
                    return @{ Profile = "CustomWrite"; TargetPartition = "epd_frame"; Binary = $binPath }
                }
                default { throw "Invalid NVS/Storage selection." }
            }
        }
        "4" {
            $partInput = (Read-Host "  Enter Partition # (1-$($PartMap.Count)) or Partition Name (e.g. ota_1, storage)").Trim()
            $partName = Resolve-PartitionChoice -PartMap $PartMap -UserInput $partInput
            $binInput = (Read-Host "  Enter path to .bin file to flash into '$partName'").Trim().Trim('"')
            return @{ Profile = "CustomWrite"; TargetPartition = $partName; Binary = $binInput }
        }
        "5" {
            $partInput = (Read-Host "  Enter Partition # (1-$($PartMap.Count)) or Partition Name to ERASE to 0xFF").Trim()
            $partName = Resolve-PartitionChoice -PartMap $PartMap -UserInput $partInput
            return @{ Profile = "CustomErase"; TargetPartition = $partName }
        }
        "6" {
            return @{ Profile = "KeepNvs"; KeepPartitionTable = $true; KeepNvs = $true }
        }
        default {
            Write-Host "[*] Exiting Interactive Manager." -ForegroundColor Yellow
            exit 0
        }
    }
}

function Resolve-PartitionChoice {
    param(
        [System.Collections.Generic.List[H1OS.Flasher.PartitionEntry]]$PartMap,
        [string]$UserInput
    )
    $num = 0
    if ([int]::TryParse($UserInput, [ref]$num)) {
        if ($num -ge 1 -and $num -le $PartMap.Count) {
            return $PartMap[$num - 1].Name
        }
    }
    foreach ($p in $PartMap) {
        if ($p.Name.Equals($UserInput, [StringComparison]::OrdinalIgnoreCase)) {
            return $p.Name
        }
    }
    throw "Unknown partition '$UserInput'."
}

function Get-PartitionByName {
    param(
        [System.Collections.Generic.List[H1OS.Flasher.PartitionEntry]]$PartMap,
        [string]$Name
    )
    foreach ($p in $PartMap) {
        if ($p.Name.Equals($Name, [StringComparison]::OrdinalIgnoreCase)) {
            return $p
        }
    }
    throw "Partition '$Name' was not found in the partition table."
}

# ---------------------------------------------------------------------------
# 4. Execution Plan Builder
# ---------------------------------------------------------------------------
Write-Host "=========================================================================" -ForegroundColor Green
Write-Host "   H1OS Unified Zero-Dependency ESP32-S3 Flasher & Partition Manager     " -ForegroundColor Green
Write-Host "      Target Hardware: Waveshare ESP32-S3 ePaper 1.54 V2 (303A:1001)     " -ForegroundColor Green
Write-Host "=========================================================================" -ForegroundColor Green

try {
    $distRoot = Resolve-DistributionRoot
    $partMap  = [H1OS.Flasher.PartitionTableParser]::LoadPartitionMap($distRoot)
    $bins     = Find-DistributionBinaries -DistRoot $distRoot

    if ($Profile -eq "Interactive") {
        $cmdOverride = Invoke-InteractiveManager -DistRoot $distRoot -PartMap $partMap
        $Profile = $cmdOverride.Profile
        if ($cmdOverride.ContainsKey("TargetSlot"))         { $TargetSlot = $cmdOverride.TargetSlot }
        if ($cmdOverride.ContainsKey("TargetPartition"))    { $TargetPartition = $cmdOverride.TargetPartition }
        if ($cmdOverride.ContainsKey("Binary"))             { $Binary = $cmdOverride.Binary }
        if ($cmdOverride.ContainsKey("KeepPartitionTable")) { $KeepPartitionTable = [switch]$cmdOverride.KeepPartitionTable }
        if ($cmdOverride.ContainsKey("KeepNvs"))            { $KeepNvs = [switch]$cmdOverride.KeepNvs }
    }

    $portInfo = Find-Esp32S3Port -RequestedPort $Port

    # Build list of erase actions and write segments
    $eraseRegions  = New-Object System.Collections.Generic.List[PSCustomObject]
    $writeSegments = New-Object System.Collections.Generic.List[H1OS.Flasher.FlashSegment]

    # Helper to queue a file segment
    function Add-FileSegment([uint32]$segOffset, [uint32]$maxSz, [string]$path, [string]$label) {
        $s = New-Object H1OS.Flasher.FlashSegment
        $s.Offset = $segOffset
        $s.MaxAllowedSize = $maxSz
        $s.FilePath = $path
        $s.Label = $label
        $writeSegments.Add($s)
    }

    function Add-RawSegment([uint32]$segOffset, [uint32]$maxSz, [byte[]]$payload, [string]$label) {
        $s = New-Object H1OS.Flasher.FlashSegment
        $s.Offset = $segOffset
        $s.MaxAllowedSize = $maxSz
        $s.RawPayload = $payload
        $s.Label = $label
        $writeSegments.Add($s)
    }

    # Explicit -Segments override if passed on CLI
    if ($Segments -and $Segments.Count -gt 0) {
        foreach ($entry in $Segments) {
            if ($entry -notmatch '^(0x[0-9a-fA-F]+|\d+|[a-zA-Z0-9_\-]+)=(.+)$') {
                throw "Invalid segment format '$entry'. Expected '0xOFFSET=file.bin' or 'partition_name=file.bin'."
            }
            $lhs = $Matches[1]
            $rhs = $Matches[2]
            $resolvedPath = if ([System.IO.Path]::IsPathRooted($rhs)) { $rhs } else { Join-Path $distRoot $rhs }

            $segOffset = [uint32]0
            $maxSz = [uint32]0
            if ($lhs -match '^(0x[0-9a-fA-F]+|\d+)$') {
                $segOffset = [H1OS.Flasher.PartitionTableParser]::ParseSizeOrHex($lhs)
            } else {
                $pEntry = Get-PartitionByName -PartMap $partMap -Name $lhs
                $segOffset = $pEntry.Offset
                $maxSz = $pEntry.Size
            }
            Add-FileSegment $segOffset $maxSz $resolvedPath "$lhs ($([System.IO.Path]::GetFileName($resolvedPath)))"
        }
    }
    else {
        switch ($Profile) {
            "Factory" {
                # Scrub full 8MB flash die to 0xFF
                $eraseRegions.Add([PSCustomObject]@{
                    Offset = [uint32]0x000000
                    Length = [uint32]($FlashSizeMB * 1024 * 1024)
                    Label  = "Entire ${FlashSizeMB}MB NOR Flash Die (Factory POR Scrub)"
                })

                if ($bins.Bootloader -and $bins.PartTable -and $bins.AppBin) {
                    Add-FileSegment 0x000000 0x008000 $bins.Bootloader "bootloader (0x000000)"
                    Add-FileSegment 0x008000 0x001000 $bins.PartTable  "partition-table (0x008000)"
                    if ($bins.OtaData) {
                        Add-FileSegment 0x01D000 0x002000 $bins.OtaData "otadata (0x01D000 -> ota_0)"
                    } else {
                        Add-RawSegment 0x01D000 0x002000 ([H1OS.Flasher.PartitionTableParser]::BuildOtaDataPayload("ota_0")) "otadata (synthesized -> ota_0)"
                    }
                    Add-FileSegment 0x020000 0x300000 $bins.AppBin "ota_0 App (0x020000)"
                }
                elseif ($bins.FactoryBin) {
                    Add-FileSegment 0x000000 0x800000 $bins.FactoryBin ([System.IO.Path]::GetFileName($bins.FactoryBin))
                }
                else {
                    throw "No factory or modular binaries found in $distRoot."
                }
            }

            "KeepNvs" {
                # Updates Bootloader (unless -KeepPartitionTable), Partition Table (unless -KeepPartitionTable),
                # otadata (unless -KeepOtaData), and ota_0 App while strictly preserving nvs (0x9000), storage (0x620000), and epd_frame (0x7FC000)
                if ($bins.Bootloader -and $bins.PartTable -and $bins.AppBin) {
                    if (-not $KeepPartitionTable.IsPresent) {
                        Add-FileSegment 0x000000 0x008000 $bins.Bootloader "bootloader (0x000000)"
                        Add-FileSegment 0x008000 0x001000 $bins.PartTable  "partition-table (0x008000)"
                    }
                    if (-not $KeepOtaData.IsPresent) {
                        if ($bins.OtaData -and $TargetSlot -eq "ota_0") {
                            Add-FileSegment 0x01D000 0x002000 $bins.OtaData "otadata (0x01D000 -> ota_0)"
                        } else {
                            Add-RawSegment 0x01D000 0x002000 ([H1OS.Flasher.PartitionTableParser]::BuildOtaDataPayload($TargetSlot)) "otadata (0x01D000 -> $TargetSlot)"
                        }
                    }
                    $appPart = Get-PartitionByName -PartMap $partMap -Name $(if ($TargetSlot -eq "ota_1") { "ota_1" } else { "ota_0" })
                    Add-FileSegment $appPart.Offset $appPart.Size $bins.AppBin "$($appPart.Name) App (0x$($appPart.Offset.ToString('X6')))"
                }
                elseif ($bins.FactoryBin) {
                    # FlashSegment automatically splits 0xFF gaps in 0x0..0x20000 so NVS (0x9000) is preserved!
                    Add-FileSegment 0x000000 0x800000 $bins.FactoryBin ([System.IO.Path]::GetFileName($bins.FactoryBin))
                }
                else {
                    throw "No firmware binaries found in $distRoot."
                }
            }

            "AppOnly" {
                $appFile = if (-not [string]::IsNullOrWhiteSpace($Binary)) {
                    if ([System.IO.Path]::IsPathRooted($Binary)) { $Binary } else { Join-Path $distRoot $Binary }
                } else {
                    $bins.AppBin
                }
                if (-not $appFile) { throw "Could not locate h1os.bin for AppOnly update." }

                $slotName = if ($TargetSlot -eq "ota_1") { "ota_1" } else { "ota_0" }
                $appPart = Get-PartitionByName -PartMap $partMap -Name $slotName

                if (-not $KeepOtaData.IsPresent) {
                    if ($bins.OtaData -and $slotName -eq "ota_0") {
                        Add-FileSegment 0x01D000 0x002000 $bins.OtaData "otadata (0x01D000 -> ota_0)"
                    } else {
                        Add-RawSegment 0x01D000 0x002000 ([H1OS.Flasher.PartitionTableParser]::BuildOtaDataPayload($slotName)) "otadata (0x01D000 -> $slotName)"
                    }
                }
                Add-FileSegment $appPart.Offset $appPart.Size $appFile "$slotName App (0x$($appPart.Offset.ToString('X6')))"
            }

            "DualOta" {
                $appFile = if (-not [string]::IsNullOrWhiteSpace($Binary)) {
                    if ([System.IO.Path]::IsPathRooted($Binary)) { $Binary } else { Join-Path $distRoot $Binary }
                } else {
                    $bins.AppBin
                }
                if (-not $appFile) { throw "Could not locate h1os.bin for DualOta flash." }

                $ota0 = Get-PartitionByName -PartMap $partMap -Name "ota_0"
                $ota1 = Get-PartitionByName -PartMap $partMap -Name "ota_1"

                if (-not $KeepOtaData.IsPresent) {
                    if ($bins.OtaData) {
                        Add-FileSegment 0x01D000 0x002000 $bins.OtaData "otadata (0x01D000 -> ota_0)"
                    } else {
                        Add-RawSegment 0x01D000 0x002000 ([H1OS.Flasher.PartitionTableParser]::BuildOtaDataPayload("ota_0")) "otadata (0x01D000 -> ota_0)"
                    }
                }
                Add-FileSegment $ota0.Offset $ota0.Size $appFile "ota_0 Primary App (0x$($ota0.Offset.ToString('X6')))"
                Add-FileSegment $ota1.Offset $ota1.Size $appFile "ota_1 Secondary App (0x$($ota1.Offset.ToString('X6')))"
            }

            "SetBootSlot" {
                $slotName = if ($TargetSlot -eq "ota_1") { "ota_1" } else { "ota_0" }
                $otaPart = Get-PartitionByName -PartMap $partMap -Name "otadata"
                if ($slotName -eq "ota_0" -and $bins.OtaData) {
                    Add-FileSegment $otaPart.Offset $otaPart.Size $bins.OtaData "otadata (Active Boot -> ota_0)"
                } else {
                    Add-RawSegment $otaPart.Offset $otaPart.Size ([H1OS.Flasher.PartitionTableParser]::BuildOtaDataPayload($slotName)) "otadata (Active Boot -> $slotName)"
                }
            }

            "WipeNvs" {
                $nvsPart = Get-PartitionByName -PartMap $partMap -Name "nvs"
                $eraseRegions.Add([PSCustomObject]@{ Offset = $nvsPart.Offset; Length = $nvsPart.Size; Label = "nvs (0x$($nvsPart.Offset.ToString('X6')))" })
                try {
                    $phyPart = Get-PartitionByName -PartMap $partMap -Name "phy_init"
                    $eraseRegions.Add([PSCustomObject]@{ Offset = $phyPart.Offset; Length = $phyPart.Size; Label = "phy_init (0x$($phyPart.Offset.ToString('X6')))" })
                } catch { }
            }

            "WipeStorage" {
                $stPart = Get-PartitionByName -PartMap $partMap -Name "storage"
                $eraseRegions.Add([PSCustomObject]@{ Offset = $stPart.Offset; Length = $stPart.Size; Label = "storage SPIFFS (0x$($stPart.Offset.ToString('X6')))" })
            }

            "WipeEpdFrame" {
                $epdPart = Get-PartitionByName -PartMap $partMap -Name "epd_frame"
                $eraseRegions.Add([PSCustomObject]@{ Offset = $epdPart.Offset; Length = $epdPart.Size; Label = "epd_frame ePaper Buffer (0x$($epdPart.Offset.ToString('X6')))" })
            }

            "CustomWrite" {
                if ([string]::IsNullOrWhiteSpace($Binary)) {
                    throw "CustomWrite requires -Binary <path>."
                }
                $resolvedBin = if ([System.IO.Path]::IsPathRooted($Binary)) { $Binary } else { Join-Path $distRoot $Binary }
                if (-not [string]::IsNullOrWhiteSpace($TargetPartition)) {
                    $pEntry = Get-PartitionByName -PartMap $partMap -Name $TargetPartition
                    Add-FileSegment $pEntry.Offset $pEntry.Size $resolvedBin "$($pEntry.Name) (0x$($pEntry.Offset.ToString('X6')))"
                }
                elseif ($Offset -ne [uint32]::MaxValue) {
                    Add-FileSegment $Offset 0 $resolvedBin "Custom @ 0x$($Offset.ToString('X6'))"
                }
                else {
                    throw "CustomWrite requires either -TargetPartition <name> or -Offset <hex>."
                }
            }

            "CustomErase" {
                if (-not [string]::IsNullOrWhiteSpace($TargetPartition)) {
                    $pEntry = Get-PartitionByName -PartMap $partMap -Name $TargetPartition
                    $eraseRegions.Add([PSCustomObject]@{ Offset = $pEntry.Offset; Length = $pEntry.Size; Label = "$($pEntry.Name) (0x$($pEntry.Offset.ToString('X6')))" })
                }
                elseif ($Offset -ne [uint32]::MaxValue -and $EraseLength -gt 0) {
                    $eraseRegions.Add([PSCustomObject]@{ Offset = $Offset; Length = $EraseLength; Label = "Custom Region (0x$($Offset.ToString('X6')))" })
                }
                else {
                    throw "CustomErase requires -TargetPartition <name> or both -Offset and -EraseLength."
                }
            }
        }
    }

    # Print Execution Summary
    Write-Host "[*] Target Serial Port        : $($portInfo.PortName) ($($portInfo.Description))"
    Write-Host "[*] Operation Profile         : $Profile"

    if ($eraseRegions.Count -gt 0) {
        Write-Host "[*] Erase Regions Queued      : $($eraseRegions.Count)" -ForegroundColor Yellow
        foreach ($er in $eraseRegions) {
            Write-Host ("    -> ERASE 0x{0:X6} ({1,7:N1} KB) : {2}" -f $er.Offset, ($er.Length / 1024.0), $er.Label) -ForegroundColor Yellow
        }
    }

    if ($writeSegments.Count -gt 0) {
        Write-Host "[*] Write Segments Queued     : $($writeSegments.Count)" -ForegroundColor Cyan
        foreach ($ws in $writeSegments) {
            $szBytes = if ($ws.RawPayload) { $ws.RawPayload.Length } else { (Get-Item $ws.FilePath).Length }
            Write-Host ("    -> WRITE 0x{0:X6} ({1,7:N1} KB) : {2}" -f $ws.Offset, ($szBytes / 1024.0), $ws.Label) -ForegroundColor Cyan
        }
        Test-BundleChecksums -DistRoot $distRoot -TargetSegments $writeSegments.ToArray()
    }

    # Execute on Hardware
    $flasher = New-Object H1OS.Flasher.Esp32S3RomFlasher($portInfo.PortName, $Baud, $portInfo.IsNativeUsb)
    try {
        $flasher.EnterBootloader()
        $flasher.SyncWithRom()
        $flasher.AttachAndConfigureSpiFlash($FlashSizeMB)

        if ($Profile -eq "Inspect") {
            Write-Host ""
            Write-Host "  Live On-Chip Partition Inspection (via ESP_SPI_FLASH_MD5 0x13):" -ForegroundColor Cyan
            Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray
            Write-Host ("  {0,-16} {1,-10} {2,10}  {3,-34} {4}" -f "Partition", "Offset", "Size (KB)", "On-Chip MD5", "Status") -ForegroundColor White
            Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray

            foreach ($p in $partMap) {
                $chipMd5 = $flasher.ComputeOnChipMd5($p.Offset, $p.Size)
                $blankMd5 = [H1OS.Flasher.Esp32S3RomFlasher]::ComputeBlankRegionMd5Hex($p.Size)

                $statusStr = "POPULATED DATA"
                $statusColor = "Yellow"
                if ($chipMd5 -eq $blankMd5) {
                    $statusStr = "BLANK (All 0xFF)"
                    $statusColor = "DarkGray"
                }
                else {
                    # Check if a local binary exists for this partition
                    $localCandidate = switch ($p.Name) {
                        "bootloader"      { $bins.Bootloader }
                        "partition-table" { $bins.PartTable }
                        "otadata"         { $bins.OtaData }
                        "ota_0"           { $bins.AppBin }
                        "ota_1"           { $bins.AppBin }
                        default           { $null }
                    }
                    if ($localCandidate -and (Test-Path $localCandidate)) {
                        $localBytes = [System.IO.File]::ReadAllBytes($localCandidate)
                        $subChipMd5 = $flasher.ComputeOnChipMd5($p.Offset, [uint32]$localBytes.Length)
                        $localMd5   = [H1OS.Flasher.Esp32S3RomFlasher]::ComputeHostMd5Hex($localBytes)
                        if ($subChipMd5 -eq $localMd5) {
                            $statusStr = "MATCHES LOCAL $([System.IO.Path]::GetFileName($localCandidate))"
                            $statusColor = "Green"
                        }
                    }
                }

                Write-Host ("  {0,-16} 0x{1:X6}   {2,10:N1}  {3,-34} {4}" -f `
                    $p.Name, $p.Offset, $p.SizeKB, $chipMd5, $statusStr) -ForegroundColor $statusColor
            }
            Write-Host "  ----------------------------------------------------------------------------------------------------" -ForegroundColor DarkGray
        }
        else {
            foreach ($er in $eraseRegions) {
                $flasher.EraseFlashRegion($er.Offset, $er.Length, $er.Label)
            }

            $verify = -not $NoVerify.IsPresent
            $preserveNvsGap = ($Profile -ne "Factory")
            foreach ($ws in $writeSegments) {
                $flasher.FlashSegment($ws, $verify, $preserveNvsGap)
            }
        }

        $flasher.FinishAndReboot()
    }
    finally {
        $flasher.Dispose()
    }

    Write-Host ""
    Write-Host "=========================================================================" -ForegroundColor Green
    Write-Host " [SUCCESS] Operation '$Profile' completed! Device is booting into H1OS.  " -ForegroundColor Green
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
