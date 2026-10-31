# ==============================================================================
# H1OS UNDERGROUND // tokyo_bloodline_lite.ps1 [NO-BLOB / AUDITABLE EDITION v2.6]
# App-Phreak Aesthetic Hardware USB Bus Controller & SE0 Port Cycler
# Zero Embedded Binary Data — Scans Working Directory for .wav / .mp3 Audio
# ==============================================================================
# Startup Arguments:
#   -NoAudio / -Mute / -Silent / -SoundOff / -NoSound : Disable audio on startup
#   -AudioFile <path>                                 : Optional custom .wav/.mp3
# ==============================================================================

param(
    [Alias("Mute", "Silent", "DisableAudio", "SoundOff", "NoSound")]
    [switch]$NoAudio,
    [string]$AudioFile = ""
)

$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator);
if (-not $isAdmin) {
    $forwardArgs = "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"";
    if ($NoAudio.IsPresent) {
        $forwardArgs += " -NoAudio";
    }
    if (-not [string]::IsNullOrEmpty($AudioFile)) {
        $forwardArgs += " -AudioFile `"$AudioFile`"";
    }
    Start-Process powershell.exe -Verb RunAs -ArgumentList $forwardArgs;
    exit;
}

Add-Type -AssemblyName System.Windows.Forms;
Add-Type -AssemblyName System.Drawing;

if (-not ([System.Management.Automation.PSTypeName]'UsbHubPortCycler').Type) {
    $csharpCode = @"
using System;
using System.IO;
using System.Media;
using System.Text;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

public class UsbHubPortCycler {
    private const uint GENERIC_WRITE = 0x40000000;
    private const uint FILE_SHARE_READ = 0x00000001;
    private const uint FILE_SHARE_WRITE = 0x00000002;
    private const uint OPEN_EXISTING = 3;
    /* IOCTL_USB_HUB_CYCLE_PORT = CTL_CODE(FILE_DEVICE_USB, 273, METHOD_BUFFERED, FILE_ANY_ACCESS) = 0x220444 */
    private const uint IOCTL_USB_HUB_CYCLE_PORT = 0x220444;

    [StructLayout(LayoutKind.Sequential)]
    public struct USB_CYCLE_PORT_PARAMS {
        public uint ConnectionIndex;
        public uint StatusReturned;
    }

    [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    private static extern SafeFileHandle CreateFile(
        string lpFileName, uint dwDesiredAccess, uint dwShareMode,
        IntPtr lpSecurityAttributes, uint dwCreationDisposition,
        uint dwFlagsAndAttributes, IntPtr hTemplateFile
    );

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool DeviceIoControl(
        SafeFileHandle hDevice, uint dwIoControlCode,
        ref USB_CYCLE_PORT_PARAMS lpInBuffer, uint nInBufferSize,
        ref USB_CYCLE_PORT_PARAMS lpOutBuffer, uint nOutBufferSize,
        out uint lpBytesReturned, IntPtr lpOverlapped
    );

    public static int CyclePort(string hubPath, uint portIndex) {
        using (SafeFileHandle h = CreateFile(hubPath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero)) {
            if (h.IsInvalid) return Marshal.GetLastWin32Error();
            USB_CYCLE_PORT_PARAMS p = new USB_CYCLE_PORT_PARAMS { ConnectionIndex = portIndex, StatusReturned = 0 };
            uint ret;
            bool ok = DeviceIoControl(h, IOCTL_USB_HUB_CYCLE_PORT, ref p, (uint)Marshal.SizeOf(p), ref p, (uint)Marshal.SizeOf(p), out ret, IntPtr.Zero);
            if (!ok) return Marshal.GetLastWin32Error();
            return 0;
        }
    }
}

public class Win32WindowDrag {
    [DllImport("user32.dll")]
    public static extern bool ReleaseCapture();

    [DllImport("user32.dll")]
    public static extern IntPtr SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

    public static void DragForm(IntPtr handle) {
        ReleaseCapture();
        SendMessage(handle, 0xA1, 0x02, 0);
    }
}

/* Thread-Safe Bridge Decoupling the 30 FPS UI/Visualizer Thread from Background USB Bus Operations */
public class BusLogItem {
    public string Timestamp;
    public string Tag;
    public string Message;
    public string BadgeSummary;
}

public class BusNodeRecord {
    public string InstanceId;
    public string FriendlyName;
    public string Status;
    public bool IsFaulted;
    public string ParentHub;
    public uint PortIndex;
}

public class BusSnapshot {
    public string[] ComPorts;
    public BusNodeRecord[] Nodes;
    public int FaultCount;
}

public static class BusAsyncBridge {
    private static readonly object _lock = new object();
    private static readonly Queue<BusLogItem> _logs = new Queue<BusLogItem>();
    private static BusSnapshot _latestSnapshot = null;
    private static bool _hasNewSnapshot = false;
    private static bool _isBusy = false;

    public static bool IsBusy {
        get { lock (_lock) { return _isBusy; } }
        set { lock (_lock) { _isBusy = value; } }
    }

    public static void PostLog(string msg, string tag, string badgeSummary) {
        lock (_lock) {
            BusLogItem item = new BusLogItem();
            item.Timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
            item.Tag = tag;
            item.Message = msg;
            item.BadgeSummary = badgeSummary;
            _logs.Enqueue(item);
        }
    }

    public static BusLogItem TryDequeueLog() {
        lock (_lock) {
            if (_logs.Count > 0) return _logs.Dequeue();
            return null;
        }
    }

    public static void PublishSnapshot(string[] comPorts, BusNodeRecord[] nodes, int faultCount) {
        lock (_lock) {
            BusSnapshot s = new BusSnapshot();
            s.ComPorts = comPorts != null ? comPorts : new string[0];
            s.Nodes = nodes != null ? nodes : new BusNodeRecord[0];
            s.FaultCount = faultCount;
            _latestSnapshot = s;
            _hasNewSnapshot = true;
        }
    }

    public static BusSnapshot TryTakeSnapshot() {
        lock (_lock) {
            if (!_hasNewSnapshot) return null;
            _hasNewSnapshot = false;
            return _latestSnapshot;
        }
    }
}

/* External File Audio Player (.wav via SoundPlayer, .mp3 via winmm.dll MCI) — Zero Embedded Binary Blob */
public class ExternalAudioPlayer {
    [DllImport("winmm.dll", CharSet = CharSet.Auto)]
    private static extern int mciSendString(string command, StringBuilder buffer, int bufferSize, IntPtr hwndCallback);

    private static SoundPlayer _wavPlayer;
    private static bool _usingMci = false;
    private static bool _isPlaying = false;
    private static string _activeTrackName = "NONE";

    public static bool IsPlaying { get { return _isPlaying; } }
    public static string ActiveTrackName { get { return _activeTrackName; } }

    public static bool StartFile(string filePath) {
        StopAudio();
        if (String.IsNullOrEmpty(filePath) || !File.Exists(filePath)) {
            _activeTrackName = "NO TRACK FOUND";
            return false;
        }
        string ext = Path.GetExtension(filePath).ToLowerInvariant();
        string baseName = Path.GetFileNameWithoutExtension(filePath).ToUpperInvariant();
        if (baseName.Length > 21) baseName = baseName.Substring(0, 21);

        if (ext == ".mp3") {
            mciSendString("close tb_bgm", null, 0, IntPtr.Zero);
            int rc = mciSendString("open \"" + filePath + "\" type mpegvideo alias tb_bgm", null, 0, IntPtr.Zero);
            if (rc == 0) {
                mciSendString("play tb_bgm repeat", null, 0, IntPtr.Zero);
                _usingMci = true;
                _isPlaying = true;
                _activeTrackName = baseName;
                return true;
            }
        } else if (ext == ".wav") {
            try {
                _wavPlayer = new SoundPlayer(filePath);
                _wavPlayer.PlayLooping();
                _usingMci = false;
                _isPlaying = true;
                _activeTrackName = baseName;
                return true;
            } catch {}
        }
        _activeTrackName = "AUDIO LOAD ERR";
        return false;
    }

    public static void StopAudio() {
        try {
            if (_usingMci) {
                mciSendString("stop tb_bgm", null, 0, IntPtr.Zero);
                mciSendString("close tb_bgm", null, 0, IntPtr.Zero);
                _usingMci = false;
            }
            if (_wavPlayer != null) {
                _wavPlayer.Stop();
            }
        } catch {}
        _isPlaying = false;
    }
}

public class CyberBannerControl : Panel {
    public bool FaultAlert { get; set; }
    public bool AudioActive { get; set; }
    public bool ShowNfo { get; set; }
    public int PulseFlash { get; set; }
    public string StatusBadgeText { get; set; }

    private float _phase = 0.0f;
    private PointF[] _stars;
    private float[] _starSpeeds;
    private Random _rng = new Random(1337);

    public CyberBannerControl() {
        this.DoubleBuffered = true;
        this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);
        this.StatusBadgeText = "SYS_NOMINAL · SE0 ARMED · ZERO FAULTS";
        _stars = new PointF[55];
        _starSpeeds = new float[55];
        for (int i = 0; i < _stars.Length; i++) {
            _stars[i] = new PointF((float)(_rng.NextDouble() * 700.0), (float)(_rng.NextDouble() * 145.0));
            _starSpeeds[i] = 0.3f + (float)(_rng.NextDouble() * 1.4f);
        }
    }

    public void AdvanceFrame() {
        _phase += 0.085f;
        if (PulseFlash > 0) PulseFlash--;
        for (int i = 0; i < _stars.Length; i++) {
            _stars[i].X -= _starSpeeds[i];
            if (_stars[i].X < 0) {
                _stars[i].X = this.Width > 10 ? this.Width : 700;
                _stars[i].Y = (float)(_rng.NextDouble() * 130.0);
            }
        }
        this.Invalidate();
    }

    private void DrawWireCube(Graphics g, float cx, float cy, float size, float angle, Color col) {
        float[,] verts = new float[,] {
            {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
            {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
        };
        int[,] edges = new int[,] {
            {0,1},{1,2},{2,3},{3,0},
            {4,5},{5,6},{6,7},{7,4},
            {0,4},{1,5},{2,6},{3,7},
            {0,6},{1,7}
        };
        PointF[] proj = new PointF[8];
        float cosA = (float)Math.Cos(angle);
        float sinA = (float)Math.Sin(angle);
        float cosB = (float)Math.Cos(angle * 0.7f);
        float sinB = (float)Math.Sin(angle * 0.7f);

        for (int i = 0; i < 8; i++) {
            float x = verts[i,0];
            float y = verts[i,1];
            float z = verts[i,2];
            float x1 = x * cosA - z * sinA;
            float z1 = x * sinA + z * cosA;
            float y2 = y * cosB - z1 * sinB;
            float z2 = y * sinB + z1 * cosB;
            float scale = size / (3.2f + z2 * 0.45f);
            proj[i] = new PointF(cx + x1 * scale, cy + y2 * scale);
        }

        using (Pen p = new Pen(col, 1.2f)) {
            for (int e = 0; e < edges.GetLength(0); e++) {
                g.DrawLine(p, proj[edges[e,0]], proj[edges[e,1]]);
            }
        }
        using (Pen pInner = new Pen(Color.FromArgb(140, 255, 255, 255), 1.0f)) {
            g.DrawPolygon(pInner, new PointF[] {
                new PointF(cx, cy - size * 0.24f),
                new PointF(cx + size * 0.24f, cy),
                new PointF(cx, cy + size * 0.24f),
                new PointF(cx - size * 0.24f, cy)
            });
        }
    }

    protected override void OnPaint(PaintEventArgs e) {
        Graphics g = e.Graphics;
        g.SmoothingMode = SmoothingMode.AntiAlias;
        g.TextRenderingHint = TextRenderingHint.ClearTypeGridFit;
        int w = this.Width;
        int h = this.Height;

        /* 1. Deep Tokyo-Night / Vampire Void Gradient Background */
        Color cTop = FaultAlert ? Color.FromArgb(35, 4, 12) : Color.FromArgb(11, 5, 18);
        Color cBot = FaultAlert ? Color.FromArgb(65, 6, 20) : Color.FromArgb(26, 8, 38);
        if (PulseFlash > 0) {
            cTop = Color.FromArgb(55, 15, 45);
            cBot = Color.FromArgb(90, 15, 55);
        }
        using (LinearGradientBrush bgBrush = new LinearGradientBrush(new Rectangle(0, 0, w, h), cTop, cBot, LinearGradientMode.Vertical)) {
            g.FillRectangle(bgBrush, 0, 0, w, h);
        }

        /* 2. Drifting Underground Starfield */
        using (SolidBrush sbWhite = new SolidBrush(Color.FromArgb(180, 235, 220, 255)))
        using (SolidBrush sbRed   = new SolidBrush(Color.FromArgb(200, 255, 50, 100))) {
            for (int i = 0; i < _stars.Length; i++) {
                float sz = (i % 4 == 0) ? 2.2f : 1.2f;
                g.FillRectangle((i % 5 == 0) ? sbRed : sbWhite, _stars[i].X, _stars[i].Y, sz, sz);
            }
        }

        /* 3. Vampire Blood-Moon Crescent (Upper Right) */
        float moonX = w - 135;
        float moonY = 14;
        using (SolidBrush moonGlow = new SolidBrush(Color.FromArgb(35, 255, 30, 80))) {
            g.FillEllipse(moonGlow, moonX - 10, moonY - 10, 84, 84);
        }
        using (SolidBrush moonBody = new SolidBrush(FaultAlert ? Color.FromArgb(230, 255, 45, 75) : Color.FromArgb(220, 240, 230, 255))) {
            g.FillEllipse(moonBody, moonX, moonY, 64, 64);
        }
        using (SolidBrush moonCut = new SolidBrush(cTop)) {
            g.FillEllipse(moonCut, moonX - 14, moonY - 6, 62, 62);
        }

        /* 4. Neo-Tokyo Midnight Skyline Silhouette along Horizon */
        int[] bWidths = new int[] { 28, 42, 22, 36, 54, 30, 44, 26, 48, 34, 40, 25, 50, 38, 32, 45, 30, 42, 35, 40 };
        int[] bHeights = new int[] { 26, 42, 18, 34, 48, 22, 38, 28, 44, 20, 36, 30, 46, 25, 39, 32, 24, 40, 29, 35 };
        int bx = 0;
        using (SolidBrush cityBrush = new SolidBrush(Color.FromArgb(210, 8, 4, 14)))
        using (SolidBrush winPink = new SolidBrush(Color.FromArgb(130, 255, 20, 110)))
        using (SolidBrush winCyan = new SolidBrush(Color.FromArgb(120, 0, 240, 255))) {
            for (int i = 0; i < bWidths.Length && bx < w; i++) {
                int bw = bWidths[i];
                int bh = bHeights[i];
                int by = h - 24 - bh;
                g.FillRectangle(cityBrush, bx, by, bw, bh + 24);
                for (int wy = by + 4; wy < h - 28; wy += 6) {
                    for (int wx = bx + 4; wx < bx + bw - 5; wx += 6) {
                        if (((wx + wy + i) % 3) == 0) {
                            g.FillRectangle(((wx + i) % 2 == 0) ? winPink : winCyan, wx, wy, 2, 3);
                        }
                    }
                }
                bx += bw - 2;
            }
        }

        if (ShowNfo) {
            /* App-Phreak Underground NFO Overlay */
            using (SolidBrush nfoBg = new SolidBrush(Color.FromArgb(220, 10, 4, 18))) {
                g.FillRectangle(nfoBg, 14, 10, w - 28, h - 34);
            }
            using (Pen nfoBorder = new Pen(Color.FromArgb(255, 0, 110), 1.0f)) {
                g.DrawRectangle(nfoBorder, 14, 10, w - 29, h - 35);
            }
            using (Font fNfoTitle = new Font("Consolas", 9.5f, FontStyle.Bold))
            using (Font fNfoBody  = new Font("Consolas", 8.2f, FontStyle.Regular))
            using (SolidBrush bMag = new SolidBrush(Color.FromArgb(255, 45, 130)))
            using (SolidBrush bCyn = new SolidBrush(Color.FromArgb(0, 240, 255)))
            using (SolidBrush bWht = new SolidBrush(Color.FromArgb(235, 230, 245))) {
                g.DrawString(":: H1 // TOKYO-BLOODLINE :: LITE NO-BLOB EDITION [v2.6 NFO] ::", fNfoTitle, bMag, 26, 16);
                g.DrawString("CORE   : Async Win32 IOCTL_USB_HUB_CYCLE_PORT (0x220444) SE0 Reset", fNfoBody, bWht, 26, 36);
                g.DrawString("TARGET : ESP32-S3 / ULP / JTAG / CP210x / CH34x / FTDI / Code 43 Nodes", fNfoBody, bWht, 26, 52);
                g.DrawString("AUDIO  : Scans working dir for tokyo_bloodline_synth (.mp3 / .wav)", fNfoBody, bCyn, 26, 68);
                g.DrawString("FLAGS  : Launch with -NoAudio (or -Mute / -Silent) to disable BGM", fNfoBody, bMag, 26, 84);
                g.DrawString("CREDITS: Humiditron // Humidyne Labs (2026) * App-Phreak Aesthetic", fNfoBody, bWht, 26, 100);
            }
        } else {
            /* 5. Twin Rotating 3D Wireframe Cyber-Emblems */
            Color cubeCol = FaultAlert ? Color.FromArgb(255, 40, 70) : Color.FromArgb(0, 235, 255);
            DrawWireCube(g, 54.0f, 64.0f, 54.0f, _phase, cubeCol);
            DrawWireCube(g, w - 54.0f, 64.0f, 54.0f, -_phase * 1.1f, Color.FromArgb(255, 20, 120));

            /* 6. Sliced Retro-Cyber Gradient Title */
            string mainTitle = "TOKYO // BLOODLINE";
            using (Font fLogo = new Font("Impact", 30.0f, FontStyle.Bold | FontStyle.Italic)) {
                SizeF sz = g.MeasureString(mainTitle, fLogo);
                float tx = (w - sz.Width) * 0.5f;
                float ty = 13.0f;

                using (SolidBrush shadowB = new SolidBrush(Color.FromArgb(220, 0, 0, 0))) {
                    g.DrawString(mainTitle, fLogo, shadowB, tx + 3, ty + 3);
                }
                using (SolidBrush cyanGlow = new SolidBrush(Color.FromArgb(140, 0, 245, 255))) {
                    g.DrawString(mainTitle, fLogo, cyanGlow, tx - 1, ty - 1);
                }

                RectangleF gradRect = new RectangleF(tx, ty, sz.Width, sz.Height);
                using (LinearGradientBrush logoGrad = new LinearGradientBrush(gradRect, Color.FromArgb(255, 165, 0), Color.FromArgb(135, 15, 235), LinearGradientMode.Vertical)) {
                    ColorBlend cb = new ColorBlend(4);
                    cb.Colors = new Color[] {
                        Color.FromArgb(255, 180, 15),
                        Color.FromArgb(255, 30, 85),
                        Color.FromArgb(215, 15, 195),
                        Color.FromArgb(110, 20, 235)
                    };
                    cb.Positions = new float[] { 0.0f, 0.45f, 0.75f, 1.0f };
                    logoGrad.InterpolationColors = cb;
                    g.DrawString(mainTitle, fLogo, logoGrad, tx, ty);
                }
            }
        }

        /* 7. Horizontal CRT Scanline Overlay across Banner Logo & Skyline */
        using (Pen scanPen = new Pen(Color.FromArgb(85, 5, 2, 10), 1.0f)) {
            for (int y = 0; y < h; y += 3) {
                g.DrawLine(scanPen, 0, y, w, y);
            }
        }

        /* 8. Downplayed, Low-Profile Sub-Banner Caption & Status Strip */
        if (!ShowNfo) {
            using (SolidBrush pillBg = new SolidBrush(Color.FromArgb(185, 9, 4, 15)))
            using (Pen pillBorder = new Pen(Color.FromArgb(80, 120, 45, 190), 1.0f)) {
                g.FillRectangle(pillBg, 160, 74, w - 320, 34);
                g.DrawRectangle(pillBorder, 160, 74, w - 320, 34);
            }
            using (Font fSub = new Font("Consolas", 7.5f, FontStyle.Regular))
            using (Font fStat = new Font("Consolas", 8.0f, FontStyle.Bold)) {
                string sub = "usb ctrl punk  ·  se0 bus controller & turbo port whacker";
                SizeF sSub = g.MeasureString(sub, fSub);
                using (SolidBrush bSub = new SolidBrush(Color.FromArgb(165, 150, 195))) {
                    g.DrawString(sub, fSub, bSub, (w - sSub.Width) * 0.5f, 77.0f);
                }
                SizeF sStat = g.MeasureString(StatusBadgeText, fStat);
                Color stCol = FaultAlert ? Color.FromArgb(255, 55, 75) : Color.FromArgb(0, 225, 200);
                using (SolidBrush bStat = new SolidBrush(stCol)) {
                    g.DrawString(StatusBadgeText, fStat, bStat, (w - sStat.Width) * 0.5f, 91.0f);
                }
            }
        }

        /* 9. Bottom 8-Bit Chiptune Spectrum / Bus Activity Visualizer Strip */
        int vizY = h - 22;
        using (SolidBrush vizBg = new SolidBrush(Color.FromArgb(210, 8, 4, 14))) {
            g.FillRectangle(vizBg, 0, vizY, w, 22);
        }
        int barCount = 44;
        int barW = (w - 24) / barCount;
        for (int b = 0; b < barCount; b++) {
            double wave = AudioActive
                ? (Math.Abs(Math.Sin(_phase * 1.9 + b * 0.42)) * 0.65 + Math.Abs(Math.Cos(_phase * 3.1 - b * 0.27)) * 0.35)
                : (0.15 + 0.08 * Math.Sin(_phase * 0.7 + b * 0.3));
            int bh = Math.Max(2, (int)(wave * 16.0));
            int bxPos = 12 + b * barW;
            Color barCol = (b % 3 == 0)
                ? Color.FromArgb(220, 255, 25, 100)
                : ((b % 3 == 1) ? Color.FromArgb(210, 0, 235, 255) : Color.FromArgb(210, 185, 50, 255));
            if (FaultAlert) barCol = Color.FromArgb(235, 255, 40, 60);
            using (SolidBrush bb = new SolidBrush(barCol)) {
                g.FillRectangle(bb, bxPos, vizY + 19 - bh, barW - 2, bh);
            }
        }

        /* 10. Crisp Double Frame Border */
        using (Pen pOuter = new Pen(Color.FromArgb(220, 235, 230, 250), 1.0f))
        using (Pen pInner = new Pen(FaultAlert ? Color.FromArgb(255, 35, 70) : Color.FromArgb(170, 255, 20, 110), 1.0f)) {
            g.DrawRectangle(pOuter, 0, 0, w - 1, h - 1);
            g.DrawRectangle(pInner, 3, 3, w - 7, h - 7);
        }
    }
}
"@;
    Add-Type -TypeDefinition $csharpCode -ReferencedAssemblies @("System.Windows.Forms", "System.Drawing");
}

# ==============================================================================
# PALETTE & TYPOGRAPHY (APP-PHREAK AESTHETIC / TOKYO VAMPIRE HACKER)
# ==============================================================================
$clBg         = [System.Drawing.Color]::FromArgb(11, 6, 17);
$clPanel      = [System.Drawing.Color]::FromArgb(18, 10, 28);
$clSlotBg     = [System.Drawing.Color]::FromArgb(13, 7, 21);
$clBorderWht  = [System.Drawing.Color]::FromArgb(225, 220, 240);
$clBorderPink = [System.Drawing.Color]::FromArgb(255, 25, 110);
$clBorderCyan = [System.Drawing.Color]::FromArgb(0, 235, 255);
$clBorderPurp = [System.Drawing.Color]::FromArgb(120, 45, 190);
$clTextWhite  = [System.Drawing.Color]::FromArgb(242, 238, 255);
$clTextPink   = [System.Drawing.Color]::FromArgb(255, 45, 125);
$clTextCyan   = [System.Drawing.Color]::FromArgb(0, 240, 255);
$clTextWarn   = [System.Drawing.Color]::FromArgb(255, 175, 20);
$clTextAlert  = [System.Drawing.Color]::FromArgb(255, 40, 65);
$clTextDim    = [System.Drawing.Color]::FromArgb(165, 145, 195);

$fntTitleBar  = New-Object System.Drawing.Font("Consolas", 9.5, [System.Drawing.FontStyle]::Bold);
$fntLabel     = New-Object System.Drawing.Font("Consolas", 9.0, [System.Drawing.FontStyle]::Bold);
$fntSlot      = New-Object System.Drawing.Font("Consolas", 9.5, [System.Drawing.FontStyle]::Bold);
$fntBadge     = New-Object System.Drawing.Font("Consolas", 8.25, [System.Drawing.FontStyle]::Bold);
$fntDiag      = New-Object System.Drawing.Font("Consolas", 8.0, [System.Drawing.FontStyle]::Regular);
$fntButton    = New-Object System.Drawing.Font("Consolas", 9.0, [System.Drawing.FontStyle]::Bold);

# ==============================================================================
# MAIN BORDERLESS FORM (LAYERED WINDOW FRAME)
# ==============================================================================
$form = New-Object System.Windows.Forms.Form;
$form.Text = "H1 // TOKYO-BLOODLINE :: USB CTRL PUNK v2.6 [LITE]";
$form.Size = New-Object System.Drawing.Size(740, 560);
$form.StartPosition = "CenterScreen";
$form.BackColor = $clBg;
$form.ForeColor = $clTextWhite;
$form.FormBorderStyle = [System.Windows.Forms.FormBorderStyle]::None;
$form.MaximizeBox = $false;
$form.TopMost = $true;

$form.Add_Paint({
    param($s, $e)
    $g = $e.Graphics;
    $w = $form.ClientSize.Width;
    $h = $form.ClientSize.Height;

    $scanPen = New-Object System.Drawing.Pen([System.Drawing.Color]::FromArgb(40, 0, 0, 0), 1);
    for ($y = 0; $y -lt $h; $y += 3) {
        $g.DrawLine($scanPen, 0, $y, $w, $y);
    }
    $scanPen.Dispose();

    $pWhite = New-Object System.Drawing.Pen($clBorderWht, 1);
    $pPink  = New-Object System.Drawing.Pen($clBorderPink, 1);
    $pPurp  = New-Object System.Drawing.Pen($clBorderPurp, 1);
    $pDash  = New-Object System.Drawing.Pen($clBorderPurp, 1);
    $pDash.DashStyle = [System.Drawing.Drawing2D.DashStyle]::Dot;

    $g.DrawRectangle($pWhite, 0, 0, $w - 1, $h - 1);
    $g.DrawRectangle($pPurp,  3, 3, $w - 7, $h - 7);
    $g.DrawRectangle($pWhite, 6, 6, $w - 13, $h - 13);

    $btnRects = @(
        (New-Object System.Drawing.Rectangle(14, 434, 348, 40)),
        (New-Object System.Drawing.Rectangle(378, 434, 348, 40)),
        (New-Object System.Drawing.Rectangle(14, 480, 348, 40)),
        (New-Object System.Drawing.Rectangle(378, 480, 348, 40))
    );
    foreach ($r in $btnRects) {
        $g.DrawRectangle($pDash, $r);
    }

    $pWhite.Dispose();
    $pPink.Dispose();
    $pPurp.Dispose();
    $pDash.Dispose();
});

# ==============================================================================
# CUSTOM DRAGGABLE TITLE BAR ([AUDIO] + [NFO] + [X] BOXES)
# ==============================================================================
$pnlTitleBar = New-Object System.Windows.Forms.Panel;
$pnlTitleBar.Location = New-Object System.Drawing.Point(14, 12);
$pnlTitleBar.Size = New-Object System.Drawing.Size(712, 28);
$pnlTitleBar.BackColor = $clPanel;
$pnlTitleBar.Cursor = [System.Windows.Forms.Cursors]::SizeAll;
$pnlTitleBar.Add_Paint({
    param($s, $e)
    $p = New-Object System.Drawing.Pen($clBorderWht, 2);
    $e.Graphics.DrawRectangle($p, 1, 1, $pnlTitleBar.Width - 3, $pnlTitleBar.Height - 3);
    $p.Dispose();
});
$pnlTitleBar.Add_MouseDown({
    if ($_.Button -eq [System.Windows.Forms.MouseButtons]::Left) {
        [Win32WindowDrag]::DragForm($form.Handle);
    }
});
$form.Controls.Add($pnlTitleBar);

$lblTitleText = New-Object System.Windows.Forms.Label;
$lblTitleText.Location = New-Object System.Drawing.Point(10, 5);
$lblTitleText.Size = New-Object System.Drawing.Size(520, 18);
$lblTitleText.Font = $fntTitleBar;
$lblTitleText.ForeColor = $clTextWhite;
$lblTitleText.Text = "H1 // TOKYO-BLOODLINE :: USB CTRL PUNK v2.6 [LITE]";
$lblTitleText.Cursor = [System.Windows.Forms.Cursors]::SizeAll;
$lblTitleText.Add_MouseDown({
    if ($_.Button -eq [System.Windows.Forms.MouseButtons]::Left) {
        [Win32WindowDrag]::DragForm($form.Handle);
    }
});
$pnlTitleBar.Controls.Add($lblTitleText);

function New-TitleBarButton([string]$txt, [int]$x, [int]$w, [System.Drawing.Color]$fg) {
    $b = New-Object System.Windows.Forms.Button;
    $b.Location = New-Object System.Drawing.Point($x, 3);
    $b.Size = New-Object System.Drawing.Size($w, 22);
    $b.Text = $txt;
    $b.Font = $fntBadge;
    $b.FlatStyle = [System.Windows.Forms.FlatStyle]::Flat;
    $b.FlatAppearance.BorderColor = $clBorderWht;
    $b.FlatAppearance.BorderSize = 1;
    $b.BackColor = $clSlotBg;
    $b.ForeColor = $fg;
    $b.Cursor = [System.Windows.Forms.Cursors]::Hand;
    return $b;
}

$btnAudioToggle = New-TitleBarButton "AUDIO: ON" 538 82 $clTextCyan;
$btnNfoToggle   = New-TitleBarButton "NFO"       624 46 $clTextPink;
$btnCloseApp    = New-TitleBarButton "X"         674 32 $clTextWhite;

$pnlTitleBar.Controls.Add($btnAudioToggle);
$pnlTitleBar.Controls.Add($btnNfoToggle);
$pnlTitleBar.Controls.Add($btnCloseApp);

# ==============================================================================
# ANIMATED GDI+ CYBERPUNK ARTWORK & VISUALIZER BANNER
# ==============================================================================
$artBanner = New-Object CyberBannerControl;
$artBanner.Location = New-Object System.Drawing.Point(14, 46);
$artBanner.Size = New-Object System.Drawing.Size(712, 148);
$artBanner.Cursor = [System.Windows.Forms.Cursors]::SizeAll;
$artBanner.Add_MouseDown({
    if ($_.Button -eq [System.Windows.Forms.MouseButtons]::Left) {
        [Win32WindowDrag]::DragForm($form.Handle);
    }
});
$form.Controls.Add($artBanner);

# ==============================================================================
# HEADER STATE & DIAGNOSTIC BADGE STRIP
# ==============================================================================
function New-StatusBadge([int]$x, [int]$y, [int]$w, [int]$h, [string]$initialText, [System.Drawing.Color]$borderCol, [System.Drawing.Color]$textCol) {
    $lbl = New-Object System.Windows.Forms.Label;
    $lbl.Location = New-Object System.Drawing.Point($x, $y);
    $lbl.Size = New-Object System.Drawing.Size($w, $h);
    $lbl.BackColor = $clSlotBg;
    $lbl.ForeColor = $textCol;
    $lbl.Font = $fntBadge;
    $lbl.TextAlign = [System.Drawing.ContentAlignment]::MiddleCenter;
    $lbl.BorderStyle = [System.Windows.Forms.BorderStyle]::FixedSingle;
    $lbl.Text = $initialText;
    $form.Controls.Add($lbl);
    return $lbl;
}

$bdgBusState   = New-StatusBadge 14  200 260 24 "BUS STATE: [ SCANNING... ]"  $clBorderCyan $clTextCyan;
$bdgActiveCom  = New-StatusBadge 280 200 226 24 "COM PORTS: [ NONE ]"         $clBorderPurp $clTextWhite;
$bdgFaultCount = New-StatusBadge 512 200 214 24 "CODE-43 FAULTS: [ 00 ]"      $clBorderPink $clTextCyan;

# ==============================================================================
# HARDWARE READOUT FIELDS & DIAGNOSTIC INFO
# ==============================================================================
function Add-FieldLabel([string]$text, [int]$x, [int]$y) {
    $l = New-Object System.Windows.Forms.Label;
    $l.Location = New-Object System.Drawing.Point($x, $y);
    $l.Size = New-Object System.Drawing.Size(700, 16);
    $l.Font = $fntLabel;
    $l.ForeColor = $clTextWhite;
    $l.BackColor = [System.Drawing.Color]::Transparent;
    $l.Text = $text;
    $form.Controls.Add($l);
    return $l;
}

function Add-ReadoutBox([int]$x, [int]$y, [int]$w, [int]$h, [string]$defaultVal, [System.Drawing.Color]$fg) {
    $tb = New-Object System.Windows.Forms.TextBox;
    $tb.Location = New-Object System.Drawing.Point($x, $y);
    $tb.Size = New-Object System.Drawing.Size($w, $h);
    $tb.ReadOnly = $true;
    $tb.BackColor = $clSlotBg;
    $tb.ForeColor = $fg;
    $tb.Font = $fntSlot;
    $tb.BorderStyle = [System.Windows.Forms.BorderStyle]::FixedSingle;
    $tb.TextAlign = [System.Windows.Forms.HorizontalAlignment]::Center;
    $tb.Text = $defaultVal;
    $form.Controls.Add($tb);
    return $tb;
}

$null = Add-FieldLabel "TARGET USB NODE // BUS SCOPE:" 14 230;
$cmbTargets = New-Object System.Windows.Forms.ComboBox;
$cmbTargets.Location = New-Object System.Drawing.Point(14, 247);
$cmbTargets.Size = New-Object System.Drawing.Size(712, 24);
$cmbTargets.DropDownStyle = [System.Windows.Forms.ComboBoxStyle]::DropDownList;
$cmbTargets.BackColor = $clSlotBg;
$cmbTargets.ForeColor = $clTextCyan;
$cmbTargets.FlatStyle = [System.Windows.Forms.FlatStyle]::Flat;
$cmbTargets.Font = $fntSlot;
$cmbTargets.Items.Add("[ ALL DETECTED USB & SERIAL TARGETS (AUTO-SWEEP) ]") | Out-Null;
$cmbTargets.SelectedIndex = 0;
$form.Controls.Add($cmbTargets);

$null = Add-FieldLabel "HARDWARE ID // DEVICE SIGNATURE:" 14 276;
$txtHwId = Add-ReadoutBox 14 293 712 22 "XXXX-XXXX-XXXX-XXXX // AWAITING BUS ENUMERATION" $clTextPink;

$null = Add-FieldLabel "UPSTREAM HUB SYMLINK // SE0 IOCTL VECTOR:" 14 320;
$txtHubVector = Add-ReadoutBox 14 337 712 22 "\\?\USB#ROOT_HUB30 // IOCTL_USB_HUB_CYCLE_PORT [0x220444]" $clTextWhite;

$null = Add-FieldLabel "DIAGNOSTIC INFO (BUS CONTROL & RECOVERY):" 14 364;
$txtDiagFeed = New-Object System.Windows.Forms.TextBox;
$txtDiagFeed.Location = New-Object System.Drawing.Point(14, 381);
$txtDiagFeed.Size = New-Object System.Drawing.Size(712, 46);
$txtDiagFeed.Multiline = $true;
$txtDiagFeed.ReadOnly = $true;
$txtDiagFeed.ScrollBars = [System.Windows.Forms.ScrollBars]::None;
$txtDiagFeed.BackColor = $clSlotBg;
$txtDiagFeed.ForeColor = $clTextCyan;
$txtDiagFeed.Font = $fntDiag;
$txtDiagFeed.BorderStyle = [System.Windows.Forms.BorderStyle]::FixedSingle;
$form.Controls.Add($txtDiagFeed);

# ==============================================================================
# HARDWARE ACTION BUTTONS (4 RECOVERY VECTORS PRESERVED)
# ==============================================================================
function New-ActionButton([string]$text, [int]$x, [int]$y, [int]$w, [int]$h, [System.Drawing.Color]$borderCol, [System.Drawing.Color]$fgCol) {
    $btn = New-Object System.Windows.Forms.Button;
    $btn.Location = New-Object System.Drawing.Point($x, $y);
    $btn.Size = New-Object System.Drawing.Size($w, $h);
    $btn.Text = $text;
    $btn.Font = $fntButton;
    $btn.FlatStyle = [System.Windows.Forms.FlatStyle]::Flat;
    $btn.FlatAppearance.BorderColor = $borderCol;
    $btn.FlatAppearance.BorderSize = 1;
    $btn.FlatAppearance.MouseOverBackColor = [System.Drawing.Color]::FromArgb(45, 15, 65);
    $btn.FlatAppearance.MouseDownBackColor = [System.Drawing.Color]::FromArgb(90, 20, 80);
    $btn.BackColor = $clPanel;
    $btn.ForeColor = $fgCol;
    $btn.Cursor = [System.Windows.Forms.Cursors]::Hand;
    $form.Controls.Add($btn);
    return $btn;
}

$btnPortCycle = New-ActionButton ">> [1] PATCH PORT (SE0 REPLUG) <<"        17 437 342 34 $clTextWarn  $clTextWarn;
$btnPnpDev    = New-ActionButton ">> [2] RESTART DRIVER (PNP TOGGLE) <<"   381 437 342 34 $clTextCyan  $clTextCyan;
$btnPurge     = New-ActionButton ">> [3] PURGE FAULTED NODE (CODE 43) <<"   17 483 342 34 $clTextAlert $clTextAlert;
$btnBusScan   = New-ActionButton ">> [4] SCAN FOR HARDWARE CHANGES <<"     381 483 342 34 $clTextPink  $clTextPink;

# ==============================================================================
# FOOTER STATUS BADGE & CONTROLS BAR
# ==============================================================================
$chkTop = New-Object System.Windows.Forms.CheckBox;
$chkTop.Location = New-Object System.Drawing.Point(16, 526);
$chkTop.Size = New-Object System.Drawing.Size(145, 20);
$chkTop.Text = "PIN ALWAYS ON TOP";
$chkTop.Font = $fntBadge;
$chkTop.ForeColor = $clTextDim;
$chkTop.Checked = $true;
$chkTop.Add_CheckedChanged({ $form.TopMost = $chkTop.Checked });
$form.Controls.Add($chkTop);

$bdgFooterOp = New-StatusBadge 170 524 330 22 "LAST OP: [ IDLE // READY FOR SE0 INJECTION ]" $clBorderPurp $clTextWhite;
$bdgFooterAudio = New-StatusBadge 506 524 220 22 "BGM: [ SCANNING DIR... ]" $clBorderPurp $clTextPink;

# ==============================================================================
# WORKING DIRECTORY AUDIO DISCOVERY (SCANS FOR .WAV OR .MP3)
# ==============================================================================
function Find-WorkingDirAudioTrack {
    if (-not [string]::IsNullOrEmpty($AudioFile) -and (Test-Path $AudioFile)) {
        return (Resolve-Path $AudioFile).Path;
    }
    $searchDirs = @();
    if ($PSScriptRoot) { $searchDirs += $PSScriptRoot }
    $cwd = (Get-Location).Path;
    if ($cwd -and ($searchDirs -notcontains $cwd)) { $searchDirs += $cwd }

    $preferredNames = @(
        "tokyo_bloodline_synth.wav",
        "tokyo_bloodline_synth.mp3"
    );
    foreach ($dir in $searchDirs) {
        foreach ($name in $preferredNames) {
            $cand = Join-Path $dir $name;
            if (Test-Path $cand) { return $cand }
        }
        $anyWav = Get-ChildItem -Path $dir -Filter "*.wav" -File -ErrorAction SilentlyContinue | Select-Object -First 1;
        if ($anyWav) { return $anyWav.FullName }
        $anyMp3 = Get-ChildItem -Path $dir -Filter "*.mp3" -File -ErrorAction SilentlyContinue | Select-Object -First 1;
        if ($anyMp3) { return $anyMp3.FullName }
    }
    return "";
}

$script:discoveredAudioPath = Find-WorkingDirAudioTrack;

# ==============================================================================
# DECOUPLED BACKGROUND RUNSPACE ENGINE (ZERO UI THREAD BLOCKING)
# ==============================================================================
$script:diagLines = New-Object System.Collections.Generic.List[string];
$script:cachedNodes = @();
$script:runspacePool = [runspacefactory]::CreateRunspacePool(1, 2);
$script:runspacePool.ApartmentState = [System.Threading.ApartmentState]::MTA;
$script:runspacePool.Open();
$script:activeTasks = New-Object System.Collections.Generic.List[PSObject];

$script:WorkerScriptBlock = {
    param(
        [string]$Action,
        [string]$TargetInstanceId
    )

    function Get-SafeName($dev) {
        if ($null -eq $dev) { return "Unknown USB Node" }
        if (-not [string]::IsNullOrEmpty($dev.FriendlyName)) { return $dev.FriendlyName }
        if (-not [string]::IsNullOrEmpty($dev.Name)) { return $dev.Name }
        return "Unknown USB Device (Code 43)";
    }

    function Get-TargetDevicesInternal {
        $serial = @(Get-PnpDevice -PresentOnly -ErrorAction SilentlyContinue | Where-Object {
            ($_.Class -in @('Ports', 'USB')) -and
            ($_.FriendlyName -match 'Espressif|ESP32|CP210|CH34|FTDI|Silicon Labs|USB Serial Device|JTAG|WCH')
        });
        $faulted = @(Get-PnpDevice -PresentOnly -ErrorAction SilentlyContinue | Where-Object {
            ($_.Class -in @('Unknown', 'USB', 'Ports') -or [string]::IsNullOrEmpty($_.Class)) -and
            (
                ($_.FriendlyName -match 'Unknown|Unrecognized|Descriptor Request Failed|Port Reset Failed|Failed') -or
                ($_.Status -in @('Error', 'Degraded', 'Unknown')) -or
                ($_.Problem -notin @('CM_PROB_NONE', $null, 0))
            ) -and ($_.InstanceId -match '^USB\\') -and
            (@($serial.InstanceId) -notcontains $_.InstanceId)
        });
        return @{ Serial = $serial; Faulted = $faulted };
    }

    function Get-HubInfoInternal([string]$InstanceId) {
        $parent = (Get-PnpDeviceProperty -InstanceId $InstanceId -KeyName "DEVPKEY_Device_Parent" -ErrorAction SilentlyContinue).Data;
        $portIndex = (Get-PnpDeviceProperty -InstanceId $InstanceId -KeyName "DEVPKEY_Device_Address" -ErrorAction SilentlyContinue).Data;
        if (-not $portIndex -or $portIndex -eq 0) {
            $loc = (Get-PnpDeviceProperty -InstanceId $InstanceId -KeyName "DEVPKEY_Device_LocationInfo" -ErrorAction SilentlyContinue).Data;
            if ($loc -match 'Port_#0*([0-9]+)') {
                $portIndex = [uint32]$Matches[1];
            }
        }
        if (-not $portIndex -or $portIndex -eq 0) {
            $paths = (Get-PnpDeviceProperty -InstanceId $InstanceId -KeyName "DEVPKEY_Device_LocationPaths" -ErrorAction SilentlyContinue).Data;
            if ($paths) {
                $paths | ForEach-Object {
                    if ($_ -match 'USB\([0-9]+\)#.*\.USB\(([0-9]+)\)' -or $_ -match '#USB\(([0-9]+)\)') {
                        $portIndex = [uint32]$Matches[1];
                    }
                };
            }
        }
        if (-not $portIndex) { $portIndex = 0 }
        return @{ Parent = [string]$parent; PortIndex = [uint32]$portIndex };
    }

    function Cycle-TargetPortInternal([string]$InstanceId) {
        try {
            $info = Get-HubInfoInternal -InstanceId $InstanceId;
            $parent = $info.Parent;
            $portIndex = $info.PortIndex;

            if ($parent -and $portIndex -gt 0) {
                $guid = "{f18a0e88-c30c-11d0-8815-00a0c906bed8}";
                $pHash = $parent.Replace('\', '#');
                $hubPaths = @(
                    "\\?\$pHash#$guid",
                    "\\.\$pHash#$guid",
                    "\\.\$pHash",
                    "\\.\$parent"
                );

                $err = -1;
                foreach ($hubPath in $hubPaths) {
                    $res = [UsbHubPortCycler]::CyclePort($hubPath, [uint32]$portIndex);
                    if ($res -eq 0) {
                        [BusAsyncBridge]::PostLog("IOCTL_USB_HUB_CYCLE_PORT ACK on Port #$portIndex ($hubPath)", "HW", "SE0 PORT #$portIndex ACK");
                        return $true;
                    }
                    $err = $res;
                }

                [BusAsyncBridge]::PostLog("IOCTL rejected by hub (Win32 Err $err); falling back to PnP DevNode reset...", "WARN", "IOCTL FALLBACK -> PNP");
                pnputil /restart-device "$InstanceId" 2>&1 | Out-Null;
                if ($LASTEXITCODE -eq 0) {
                    [BusAsyncBridge]::PostLog("PnP DevNode successfully restarted via pnputil.", "PNP", "PNP RESTART ACK");
                    return $true;
                } else {
                    pnputil /remove-device "$InstanceId" 2>&1 | Out-Null;
                    [BusAsyncBridge]::PostLog("PnP DevNode removed; bus rescan will renegotiate descriptor.", "PNP", "PNP NODE PURGED");
                    return $true;
                }
            }
        } catch {
            [BusAsyncBridge]::PostLog("Cycle-TargetPort exception: $($_.Exception.Message)", "ERR", "PORT CYCLE ERR");
            return $false;
        }
        return $false;
    }

    function Publish-BusStateSnapshot {
        $rawPorts = @([System.IO.Ports.SerialPort]::GetPortNames() | Sort-Object);
        $targets = Get-TargetDevicesInternal;
        $all = @($targets.Faulted) + @($targets.Serial);
        $faultIds = @($targets.Faulted | ForEach-Object { $_.InstanceId });

        $records = New-Object System.Collections.Generic.List[BusNodeRecord];
        foreach ($d in $all) {
            if ($null -eq $d -or [string]::IsNullOrEmpty($d.InstanceId)) { continue }
            $rec = New-Object BusNodeRecord;
            $rec.InstanceId = [string]$d.InstanceId;
            $rec.FriendlyName = [string](Get-SafeName $d);
            $rec.Status = if ($d.Status) { $d.Status.ToString().ToUpper() } else { "UNKNOWN" };
            $rec.IsFaulted = ($faultIds -contains $d.InstanceId);
            $hInfo = Get-HubInfoInternal -InstanceId $d.InstanceId;
            $rec.ParentHub = $hInfo.Parent;
            $rec.PortIndex = $hInfo.PortIndex;
            $records.Add($rec);
        }
        [BusAsyncBridge]::PublishSnapshot([string[]]$rawPorts, $records.ToArray(), [int]$targets.Faulted.Count);
    }

    if ($Action -eq "Poll") {
        Publish-BusStateSnapshot;
        return;
    }

    [BusAsyncBridge]::IsBusy = $true;
    try {
        $targets = Get-TargetDevicesInternal;
        $all = @($targets.Faulted) + @($targets.Serial);
        $selected = if (-not [string]::IsNullOrEmpty($TargetInstanceId)) {
            @($all | Where-Object { $_.InstanceId -eq $TargetInstanceId })
        } else {
            $all
        };

        if ($Action -eq "PortCycle") {
            [BusAsyncBridge]::PostLog("Executing hardware USB port cycle (IOCTL_USB_HUB_CYCLE_PORT)...", "HW", "RUNNING SE0 PORT CYCLE...");
            if ($selected.Count -eq 0) {
                [BusAsyncBridge]::PostLog("No target USB hardware detected on bus.", "WARN", "NO USB TARGETS FOUND");
            } else {
                $ackCount = 0;
                foreach ($dev in $selected) {
                    $dName = Get-SafeName $dev;
                    $res = Cycle-TargetPortInternal -InstanceId $dev.InstanceId;
                    if ($res) { $ackCount++ }
                    [BusAsyncBridge]::PostLog("Cycle port -> ${dName}: $(if ($res) {'ACK'} else {'BYPASS/FAIL'})", "HW", "SE0 CYCLE: $ackCount/$($selected.Count) ACK");
                }
                Start-Sleep -Milliseconds 400;
                pnputil /scan-devices | Out-Null;
            }
        }
        elseif ($Action -eq "PnpRestart") {
            [BusAsyncBridge]::PostLog("Cycling PnP DevNode driver states (Disable/Enable)...", "PNP", "CYCLING PNP DRIVERS...");
            if ($selected.Count -eq 0) {
                [BusAsyncBridge]::PostLog("No target nodes found to toggle.", "WARN", "NO NODES TO TOGGLE");
            } else {
                foreach ($dev in $selected) {
                    $dName = Get-SafeName $dev;
                    try {
                        Disable-PnpDevice -InstanceId $dev.InstanceId -Confirm:$false -ErrorAction Stop | Out-Null;
                        Start-Sleep -Milliseconds 250;
                        Enable-PnpDevice -InstanceId $dev.InstanceId -Confirm:$false -ErrorAction Stop | Out-Null;
                        [BusAsyncBridge]::PostLog("DevNode restarted: $dName", "PNP", "PNP DRIVER RESTART ACK");
                    } catch {
                        pnputil /restart-device "$($dev.InstanceId)" 2>&1 | Out-Null;
                        [BusAsyncBridge]::PostLog("pnputil fallback used for: $dName", "PNP", "PNPUTIL FALLBACK ACK");
                    }
                }
            }
        }
        elseif ($Action -eq "Purge") {
            [BusAsyncBridge]::PostLog("Purging un-enumerated/corrupt Code 43 nodes from PnP manager...", "PURGE", "PURGING CODE 43 NODES...");
            if ($targets.Faulted.Count -eq 0) {
                [BusAsyncBridge]::PostLog("No faulted Code 43 nodes currently present.", "INFO", "ZERO FAULTED NODES");
            } else {
                foreach ($f in $targets.Faulted) {
                    $fName = Get-SafeName $f;
                    pnputil /remove-device "$($f.InstanceId)" 2>&1 | Out-Null;
                    [BusAsyncBridge]::PostLog("Purged faulted node: $fName", "PURGE", "PURGED $($targets.Faulted.Count) NODE(S)");
                }
            }
            pnputil /scan-devices | Out-Null;
            [BusAsyncBridge]::PostLog("PnP hardware scan issued post-purge.", "INFO", "PURGE + RESCAN COMPLETE");
        }
        elseif ($Action -eq "BusScan") {
            [BusAsyncBridge]::PostLog("Issuing pnputil /scan-devices across root hubs..." , "PNP", "SCANNING USB BUS...");
            pnputil /scan-devices | Out-Null;
            [BusAsyncBridge]::PostLog("Hardware bus rescan complete.", "INFO", "BUS RESCAN COMPLETE");
        }

        Publish-BusStateSnapshot;
    } finally {
        [BusAsyncBridge]::IsBusy = $false;
    }
};

function Start-BackgroundBusTask([string]$Action, [string]$TargetInstanceId = "") {
    if ($Action -ne "Poll" -and [BusAsyncBridge]::IsBusy) {
        [BusAsyncBridge]::PostLog("Bus operation already in progress; please wait...", "WARN", "BUS OP IN FLIGHT");
        return;
    }
    $ps = [powershell]::Create();
    $ps.RunspacePool = $script:runspacePool;
    [void]$ps.AddScript($script:WorkerScriptBlock).AddArgument($Action).AddArgument($TargetInstanceId);
    $handle = $ps.BeginInvoke();
    $script:activeTasks.Add([PSCustomObject]@{ PowerShell = $ps; Handle = $handle });
}

function Update-ActiveSelectionDetails {
    $nodes = $script:cachedNodes;
    $activeNode = $null;
    if ($cmbTargets.SelectedIndex -gt 0 -and ($cmbTargets.SelectedIndex - 1) -lt $nodes.Count) {
        $activeNode = $nodes[$cmbTargets.SelectedIndex - 1];
    } elseif ($nodes.Count -gt 0) {
        $activeNode = $nodes[0];
    }

    if ($null -ne $activeNode) {
        $idClean = $activeNode.InstanceId.Replace('\', ' // ');
        $txtHwId.Text = "$idClean [$($activeNode.Status)]";
        if ($activeNode.ParentHub -and $activeNode.PortIndex -gt 0) {
            $pShort = $activeNode.ParentHub.Replace('\', '#');
            $txtHubVector.Text = "\\?\$pShort // PORT #$($activeNode.PortIndex) [IOCTL_0x220444]";
        } else {
            $txtHubVector.Text = "HUB_PARENT: $($activeNode.ParentHub) // PNP FALLBACK READY";
        }
    } else {
        $txtHwId.Text = "NO TARGET SILICON DETECTED // INSERT ESP32 / JTAG / UART DEVICE";
        $txtHubVector.Text = "\\?\USB#ROOT_HUB30 // AWAITING UPSTREAM PORT ATTACHMENT";
    }
}

function Apply-BusSnapshotToUi([BusSnapshot]$snap) {
    if ($null -eq $snap) { return }
    $script:cachedNodes = @($snap.Nodes);

    $portStr = if ($snap.ComPorts.Length -gt 0) { $snap.ComPorts -join ", " } else { "NONE" };
    $bdgActiveCom.Text = "COM PORTS: [ $portStr ]";

    $faultCnt = $snap.FaultCount;
    $bdgFaultCount.Text = ("CODE-43 FAULTS: [ {0:D2} ]" -f $faultCnt);

    if ($faultCnt -gt 0) {
        $artBanner.FaultAlert = $true;
        $artBanner.StatusBadgeText = "ALERT: $faultCnt FAULTED USB NODE(S) · SE0 RESET REQUIRED";
        $bdgBusState.Text = "BUS STATE: [ CODE-43 FAULT! ]";
        $bdgBusState.ForeColor = $clTextAlert;
        $bdgFaultCount.ForeColor = $clTextAlert;
    } else {
        $artBanner.FaultAlert = $false;
        $artBanner.StatusBadgeText = "SYS_NOMINAL · PORTS: [$portStr] · FAULTS: 0";
        $bdgBusState.Text = "BUS STATE: [ NOMINAL // ARMED ]";
        $bdgBusState.ForeColor = $clTextCyan;
        $bdgFaultCount.ForeColor = $clTextCyan;
    }

    $expectedLabels = @("[ ALL DETECTED USB & SERIAL TARGETS (AUTO-SWEEP) ]");
    foreach ($n in $script:cachedNodes) {
        $tag = if ($n.IsFaulted) { "FAULT" } else { "OK" };
        $expectedLabels += "[$tag] $($n.FriendlyName) ($($n.InstanceId))";
    }
    $currentLabels = @();
    foreach ($item in $cmbTargets.Items) { $currentLabels += $item.ToString() }
    if (($expectedLabels -join '|') -ne ($currentLabels -join '|')) {
        $prevIdx = $cmbTargets.SelectedIndex;
        $cmbTargets.Items.Clear();
        foreach ($lbl in $expectedLabels) { $cmbTargets.Items.Add($lbl) | Out-Null }
        if ($prevIdx -ge 0 -and $prevIdx -lt $cmbTargets.Items.Count) {
            $cmbTargets.SelectedIndex = $prevIdx;
        } else {
            $cmbTargets.SelectedIndex = 0;
        }
    }

    Update-ActiveSelectionDetails;
}

function Get-SelectedTargetInstanceId {
    if ($cmbTargets.SelectedIndex -gt 0 -and ($cmbTargets.SelectedIndex - 1) -lt $script:cachedNodes.Count) {
        return [string]$script:cachedNodes[$cmbTargets.SelectedIndex - 1].InstanceId;
    }
    return "";
}

$cmbTargets.Add_SelectedIndexChanged({
    Update-ActiveSelectionDetails;
});

# ==============================================================================
# NON-BLOCKING ASYNC BUTTON HANDLERS (DECOUPLED FROM UI & VISUALIZER)
# ==============================================================================
$btnPortCycle.Add_Click({
    $targetId = Get-SelectedTargetInstanceId;
    Start-BackgroundBusTask -Action "PortCycle" -TargetInstanceId $targetId;
});

$btnPnpDev.Add_Click({
    $targetId = Get-SelectedTargetInstanceId;
    Start-BackgroundBusTask -Action "PnpRestart" -TargetInstanceId $targetId;
});

$btnPurge.Add_Click({
    Start-BackgroundBusTask -Action "Purge";
});

$btnBusScan.Add_Click({
    Start-BackgroundBusTask -Action "BusScan";
});

# ==============================================================================
# EXTERNAL AUDIO INITIALIZATION & TOGGLE LOGIC (WORKING DIR SCANNER)
# ==============================================================================
function Sync-AudioUiState {
    if ([ExternalAudioPlayer]::IsPlaying) {
        $btnAudioToggle.Text = "AUDIO: ON";
        $btnAudioToggle.ForeColor = $clTextCyan;
        $bdgFooterAudio.Text = "BGM: [ $([ExternalAudioPlayer]::ActiveTrackName) ]";
        $bdgFooterAudio.ForeColor = $clTextPink;
        $artBanner.AudioActive = $true;
    } else {
        $btnAudioToggle.Text = "AUDIO: OFF";
        $btnAudioToggle.ForeColor = $clTextDim;
        $bdgFooterAudio.Text = "BGM: [ MUTED // SILENT ]";
        $bdgFooterAudio.ForeColor = $clTextDim;
        $artBanner.AudioActive = $false;
    }
}

$btnAudioToggle.Add_Click({
    if ([ExternalAudioPlayer]::IsPlaying) {
        [ExternalAudioPlayer]::StopAudio();
        [BusAsyncBridge]::PostLog("Soundtrack muted by operator.", "AUD", "AUDIO MUTED");
    } else {
        $script:discoveredAudioPath = Find-WorkingDirAudioTrack;
        if ([ExternalAudioPlayer]::StartFile($script:discoveredAudioPath)) {
            [BusAsyncBridge]::PostLog("Playing external track: $(Split-Path $script:discoveredAudioPath -Leaf)", "AUD", "SYNTH BGM ON");
        } else {
            [BusAsyncBridge]::PostLog("No .wav or .mp3 audio file found in working directory.", "WARN", "NO AUDIO FILE FOUND");
        }
    }
    Sync-AudioUiState;
});

$btnNfoToggle.Add_Click({
    $artBanner.ShowNfo = -not $artBanner.ShowNfo;
    $btnNfoToggle.ForeColor = if ($artBanner.ShowNfo) { $clTextCyan } else { $clTextPink };
    $artBanner.Invalidate();
});

$btnCloseApp.Add_Click({
    $form.Close();
});

# ==============================================================================
# DEDICATED 30 FPS UI VISUALIZER & ASYNC BRIDGE DRAIN TIMER
# ==============================================================================
$animTimer = New-Object System.Windows.Forms.Timer;
$animTimer.Interval = 30;
$script:pollDivider = 0;

$animTimer.Add_Tick({
    $artBanner.AdvanceFrame();

    while ($true) {
        $item = [BusAsyncBridge]::TryDequeueLog();
        if ($null -eq $item) { break }
        $entry = "[$($item.Timestamp)] [$($item.Tag)] $($item.Message)";
        $script:diagLines.Add($entry);
        while ($script:diagLines.Count -gt 3) {
            $script:diagLines.RemoveAt(0);
        }
        $txtDiagFeed.Text = ($script:diagLines -join "`r`n");
        if (-not [string]::IsNullOrEmpty($item.BadgeSummary)) {
            $bdgFooterOp.Text = "LAST OP: [ $($item.BadgeSummary) ]";
            if ($item.Tag -eq "ERR" -or $item.Tag -eq "WARN") {
                $bdgFooterOp.ForeColor = $clTextWarn;
            } elseif ($item.Tag -eq "HW" -or $item.Tag -eq "PNP" -or $item.Tag -eq "PURGE") {
                $bdgFooterOp.ForeColor = $clTextCyan;
            } else {
                $bdgFooterOp.ForeColor = $clTextWhite;
            }
        }
        $artBanner.PulseFlash = 4;
    }

    $snap = [BusAsyncBridge]::TryTakeSnapshot();
    if ($null -ne $snap) {
        Apply-BusSnapshotToUi $snap;
    }

    for ($i = $script:activeTasks.Count - 1; $i -ge 0; $i--) {
        $t = $script:activeTasks[$i];
        if ($t.Handle.IsCompleted) {
            try { $t.PowerShell.EndInvoke($t.Handle) | Out-Null } catch {}
            try { $t.PowerShell.Dispose() } catch {}
            $script:activeTasks.RemoveAt($i);
        }
    }

    $script:pollDivider = ($script:pollDivider + 1) % 80;
    if ($script:pollDivider -eq 0 -and (-not [BusAsyncBridge]::IsBusy) -and $script:activeTasks.Count -eq 0) {
        Start-BackgroundBusTask -Action "Poll";
    }
});

$form.Add_Shown({
    if ($NoAudio.IsPresent) {
        [ExternalAudioPlayer]::StopAudio();
        Sync-AudioUiState;
        [BusAsyncBridge]::PostLog("Tokyo-Bloodline Lite Console online (-NoAudio active: soundtrack muted).", "SYS", "READY [SILENT MODE]");
    } else {
        $script:discoveredAudioPath = Find-WorkingDirAudioTrack;
        if ([ExternalAudioPlayer]::StartFile($script:discoveredAudioPath)) {
            Sync-AudioUiState;
            [BusAsyncBridge]::PostLog("Tokyo-Bloodline Lite online. Loaded $(Split-Path $script:discoveredAudioPath -Leaf).", "SYS", "READY [EXT BGM ON]");
        } else {
            Sync-AudioUiState;
            [BusAsyncBridge]::PostLog("Tokyo-Bloodline Lite online (no .wav/.mp3 found in dir; running silent).", "SYS", "READY [NO AUDIO FILE]");
        }
    }
    Start-BackgroundBusTask -Action "Poll";
    $animTimer.Start();
});

$form.Add_FormClosing({
    $animTimer.Stop();
    $animTimer.Dispose();
    [ExternalAudioPlayer]::StopAudio();
    foreach ($t in $script:activeTasks) {
        try { $t.PowerShell.Dispose() } catch {}
    }
    try { $script:runspacePool.Close(); $script:runspacePool.Dispose() } catch {}
});

[System.Windows.Forms.Application]::Run($form);
