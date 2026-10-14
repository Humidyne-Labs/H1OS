import datetime
import os
import re
import subprocess
import sys
from pathlib import Path

CANDIDATE_DIRS = ["build_dev", "dev_build", "build", "build_prod", "prod_build"]
TIMESTAMP = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
LOG_FILE = f"size_diagnostic_{TIMESTAMP}.log"

# Store output strings for post-analysis
OUTPUT_STREAMS = {}

def log_write(text):
    print(text, end="")
    with open(LOG_FILE, "a", encoding="utf-8") as f:
        f.write(text)

def run_command(key, title, cmd):
    banner = f"\n{'='*65}\n{title}\nCommand: {cmd}\n{'='*65}\n"
    log_write(banner)
    try:
        result = subprocess.run(
            cmd,
            shell=True,
            check=False,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace"
        )
        log_write(result.stdout)
        OUTPUT_STREAMS[key] = result.stdout
    except Exception as e:
        err_msg = f"Error executing command: {e}\n"
        log_write(err_msg)
        OUTPUT_STREAMS[key] = err_msg

def find_active_build_dir():
    for folder in CANDIDATE_DIRS:
        p = Path(folder)
        if p.is_dir() and ((p / "compile_commands.json").exists() or any(p.glob("*.map"))):
            return folder
    for folder in CANDIDATE_DIRS:
        if Path(folder).is_dir():
            return folder
    return None

def find_target_bin(build_dir):
    p = Path(build_dir)
    ignored = {"bootloader.bin", "partition-table.bin"}
    bins = [f for f in p.glob("*.bin") if f.name.lower() not in ignored]
    return bins[0] if bins else None

def format_bytes(b):
    if b >= 1024 * 1024:
        return f"{b / (1024*1024):.2f} MB ({b:,} B)"
    elif b >= 1024:
        return f"{b / 1024:.2f} KB ({b:,} B)"
    return f"{b:,} B"

def render_summary():
    size_out = OUTPUT_STREAMS.get("size", "")
    comp_out = OUTPUT_STREAMS.get("components", "")

    summary_lines = []
    summary_lines.append(f"\n{'='*65}")
    summary_lines.append("                EXECUTIVE SIZE METRICS SUMMARY")
    summary_lines.append(f"{'='*65}\n")

    # 1. Partition Check Parsing
    # Example: h1os.bin binary size 0xbf4d0 bytes. Smallest app partition is 0x300000 bytes. 0x240b30 bytes (75%) free.
    part_match = re.search(
        r'binary size\s+(0x[0-9a-fA-F]+)\s+bytes\.\s+Smallest app partition is\s+(0x[0-9a-fA-F]+)\s+bytes\.\s+(0x[0-9a-fA-F]+)\s+bytes\s+\((\d+)%\)\s+free',
        size_out
    )

    if part_match:
        bin_sz = int(part_match.group(1), 16)
        part_sz = int(part_match.group(2), 16)
        free_sz = int(part_match.group(3), 16)
        free_pct = float(part_match.group(4))
        used_pct = 100.0 - free_pct

        summary_lines.append("1. APP PARTITION HEADROOM (Flash):")
        summary_lines.append(f"   * Partition Max : {format_bytes(part_sz)}")
        summary_lines.append(f"   * Firmware Used : {format_bytes(bin_sz)} [{used_pct:.1f}%]")
        summary_lines.append(f"   * Space Left    : {format_bytes(free_sz)} [{free_pct:.1f}% FREE]")
    else:
        summary_lines.append("1. APP PARTITION HEADROOM: [Data not detected]")

    # 2. Memory Section Usage Parsing
    # Matches table entries like: │ DIRAM   │   89058 │    26.06 │   252702 │   341760 │
    summary_lines.append("\n2. CHIP INTERNAL RAM ALLOCATION:")
    ram_targets = ["DIRAM", "IRAM", "RTC FAST", "RTC SLOW"]
    for ram_sec in ram_targets:
        m = re.search(rf'│\s+{re.escape(ram_sec)}\s+│\s+(\d+)\s+│\s+([\d\.]+)\s+│\s+(\d+)\s+│\s+(\d+)\s+│', size_out)
        if m:
            used = int(m.group(1))
            pct = float(m.group(2))
            remain = int(m.group(3))
            total = int(m.group(4))
            if ram_sec == "IRAM" and remain == 0:
                status = "100.0% (overflow into DIRAM)"
            elif remain == 0:
                status = "CRITICAL (FULL)"
            else:
                status = f"{pct:.1f}% used"
            summary_lines.append(f"   * {ram_sec:<9}: {format_bytes(used):<20} / {format_bytes(total):<18} ({status}, {format_bytes(remain)} free)")

    # 3. Component Flash Attribution Top 6
    # Matches lines from archive table: │ liblvgl__lvgl.a  │  314720 │ ...
    summary_lines.append("\n3. TOP FLASH CONSUMING ARCHIVES:")
    comp_matches = re.findall(r'│\s+([\w\.\-]+)\s+│\s+(\d+)\s+│', comp_out)
    if comp_matches:
        # Sort by total size descending
        sorted_comps = sorted([(name, int(sz)) for name, sz in comp_matches], key=lambda x: x[1], reverse=True)
        
        # Pull top 6 actual static archives (*.a)
        valid_comps = [c for c in sorted_comps if c[0].endswith(".a")][:6]
        for name, sz in valid_comps:
            summary_lines.append(f"   * {name:<26}: {format_bytes(sz):<18}")
    
    summary_lines.append(f"\n{'='*65}\n")
    return "\n".join(summary_lines)

def main():
    log_write(f"ESP-IDF Binary Size Diagnostic (Windows)\nTimestamp: {datetime.datetime.now()}\n")
    log_write(f"Active Python: {sys.executable}\n")

    build_dir = find_active_build_dir()
    if not build_dir:
        log_write(f"\n[ERROR] None of the candidate directories exist: {', '.join(CANDIDATE_DIRS)}\n")
        sys.exit(1)

    log_write(f"Target Build Directory: {build_dir}\n")
    idf_flag = f"-B {build_dir}"

    run_command("size", "1. OVERALL MEMORY BREAKDOWN", f"idf.py {idf_flag} size")
    run_command("components", "2. PER-COMPONENT BREAKDOWN", f"idf.py {idf_flag} size-components")
    run_command("files", "3. PER-FILE BREAKDOWN", f"idf.py {idf_flag} size-files")

    bin_path = find_target_bin(build_dir)
    if bin_path:
        run_command("headers", "4. BINARY IMAGE HEADERS (esptool)", f'"{sys.executable}" -m esptool image-info "{bin_path}"')
    else:
        log_write(f"\n[WARNING] No main application binary found in {build_dir}\n")

    # Render metrics dashboard
    summary_text = render_summary()
    log_write(summary_text)

    log_write(f"Diagnostics completed successfully.\nFull scroll-back log saved to: {LOG_FILE}\n")

if __name__ == "__main__":
    main()