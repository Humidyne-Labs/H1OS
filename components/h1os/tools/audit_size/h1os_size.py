#!/usr/bin/env python3
"""
H1OS Firmware Binary Size & Memory Footprint Diagnostic Inspector (h1os_size)
Version: 2.3.3
License: Apache-2.0
"""
import argparse
import datetime
import json
import os
import re
import subprocess
import sys
from pathlib import Path

VERSION = "2.3.3"
OUTPUT_STREAMS = {}
LOG_FILE_PATH = None


def log_write(text: str):
    """Write diagnostic text to stdout and log file."""
    print(text, end="", flush=True)
    if LOG_FILE_PATH:
        try:
            with open(LOG_FILE_PATH, "a", encoding="utf-8") as f:
                f.write(text)
        except Exception:
            pass


def get_idf_python_exe() -> str:
    """Resolve Python executable from IDF_PYTHON_ENV_PATH or active interpreter."""
    env_path = os.environ.get("IDF_PYTHON_ENV_PATH")
    if env_path:
        p = Path(env_path) / ("Scripts" if os.name == "nt" else "bin") / ("python.exe" if os.name == "nt" else "python")
        if p.exists():
            return str(p)
    return sys.executable


def get_idf_py_path() -> Path:
    """Resolve idf.py path strictly from IDF_PATH environment variable."""
    idf_path = os.environ.get("IDF_PATH")
    if not idf_path:
        print("[ERROR] IDF_PATH environment variable is not set. Please activate ESP-IDF environment.", file=sys.stderr)
        sys.exit(1)
    idf_py = Path(idf_path) / "tools" / "idf.py"
    if not idf_py.exists():
        print(f"[ERROR] idf.py not found at {idf_py}. Check IDF_PATH: {idf_path}", file=sys.stderr)
        sys.exit(1)
    return idf_py


def get_check_sizes_path() -> Path:
    """Resolve check_sizes.py path strictly from IDF_PATH environment variable."""
    idf_path = os.environ.get("IDF_PATH")
    if not idf_path:
        print("[ERROR] IDF_PATH environment variable is not set. Please activate ESP-IDF environment.", file=sys.stderr)
        sys.exit(1)
    script_p = Path(idf_path) / "components" / "partition_table" / "check_sizes.py"
    if not script_p.exists():
        print(f"[ERROR] check_sizes.py not found at {script_p}. Check IDF_PATH: {idf_path}", file=sys.stderr)
        sys.exit(1)
    return script_p


def run_command(key: str, title: str, cmd: str, cwd=None):
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
            errors="replace",
            cwd=cwd,
        )
        output = result.stdout or ""
        log_write(output)
        OUTPUT_STREAMS[key] = output
        return result.returncode
    except Exception as e:
        err_msg = f"[FAILED] Exception running command: {e}\n"
        log_write(err_msg)
        OUTPUT_STREAMS[key] = err_msg
        return -1


def find_target_artifacts(build_dir: Path) -> tuple:
    """Locate primary map file and application binary inside build directory."""
    desc_file = build_dir / "project_description.json"
    if desc_file.exists():
        try:
            data = json.loads(desc_file.read_text(encoding="utf-8"))
            app_bin_name = data.get("app_bin")
            proj_name = data.get("project_name")
            bin_p = (build_dir / app_bin_name) if app_bin_name else (build_dir / f"{proj_name}.bin")
            map_p = build_dir / f"{proj_name}.map"
            return (map_p if map_p.exists() else None, bin_p if bin_p.exists() else None)
        except Exception:
            pass

    map_p = build_dir / "h1os.map"
    bin_p = build_dir / "h1os.bin"
    return (map_p if map_p.exists() else None, bin_p if bin_p.exists() else None)


def format_bytes(b: int) -> str:
    """Format bytes into readable string."""
    if b >= 1024 * 1024:
        return f"{b / (1024*1024):.2f} MB ({b:,} B)"
    if b >= 1024:
        return f"{b / 1024:.2f} KB ({b:,} B)"
    return f"{b} B"


def render_summary() -> str:
    """Extract key metrics from captured outputs into an executive dashboard."""
    summary_lines = [
        f"\n{'='*65}",
        f"{'EXECUTIVE SIZE METRICS SUMMARY':^65}",
        f"{'='*65}\n",
    ]

    part_out = OUTPUT_STREAMS.get("partition", "")
    size_out = OUTPUT_STREAMS.get("size", "")
    comp_out = OUTPUT_STREAMS.get("components", "")

    # 1. Partition headroom
    m_part = re.search(r"binary size (0x[0-9a-fA-F]+|\d+) bytes\. Smallest app partition is (0x[0-9a-fA-F]+|\d+) bytes\. (0x[0-9a-fA-F]+|\d+) bytes \((\d+)%\) free", part_out)
    if m_part:
        bin_sz = int(m_part.group(1), 0)
        part_sz = int(m_part.group(2), 0)
        free_sz = int(m_part.group(3), 0)
        free_pct = float(m_part.group(4))
        used_pct = 100.0 - free_pct
        summary_lines.append("1. APP PARTITION HEADROOM (Flash):")
        summary_lines.append(f"   * Partition Max : {format_bytes(part_sz)}")
        summary_lines.append(f"   * Firmware Used : {format_bytes(bin_sz)} [{used_pct:.1f}%]")
        summary_lines.append(f"   * Space Left    : {format_bytes(free_sz)} [{free_pct:.1f}% FREE]\n")

    # 2. Chip internal RAM allocation
    summary_lines.append("2. CHIP INTERNAL RAM ALLOCATION:")
    ram_sections = ["DIRAM", "IRAM", "RTC FAST", "RTC SLOW"]
    for ram_sec in ram_sections:
        pattern = rf"│\s+{re.escape(ram_sec)}\s+│\s+(\d+)\s+│\s+([\d\.]+)\s+│\s+(\d+)\s+│\s+(\d+)\s+│"
        m_ram = re.search(pattern, size_out)
        if m_ram:
            used = int(m_ram.group(1))
            pct = float(m_ram.group(2))
            remain = int(m_ram.group(3))
            total = int(m_ram.group(4))
            if remain == 0 and pct >= 100.0:
                status = "100.0% (overflow into DIRAM)" if ram_sec == "IRAM" else "CRITICAL (FULL)"
            else:
                status = f"{pct:.1f}% used"
            summary_lines.append(f"   * {ram_sec:<9}: {format_bytes(used):<20} / {format_bytes(total):<18} ({status}, {format_bytes(remain)} free)")

    # 3. Component Flash attribution top 6
    summary_lines.append("\n3. TOP FLASH CONSUMING ARCHIVES:")
    comp_matches = re.findall(r'│\s+([\w\.\-]+)\s+│\s+(\d+)\s+│', comp_out)
    if comp_matches:
        sorted_comps = sorted([(name, int(sz)) for name, sz in comp_matches], key=lambda x: x[1], reverse=True)
        valid_comps = [c for c in sorted_comps if c[0].endswith(".a")][:6]
        for name, sz in valid_comps:
            summary_lines.append(f"   * {name:<26}: {format_bytes(sz):<18}")

    summary_lines.append(f"\n{'='*65}\n")
    return "\n".join(summary_lines)


def parse_args():
    parser = argparse.ArgumentParser(
        description=f"H1OS Firmware Binary Size & Memory Footprint Diagnostic Inspector v{VERSION}",
        epilog="Examples:\n"
               "  python h1os_size.py -B build_prod --log-file build_prod/logs/prod_20261031_140500.log\n"
               "  python h1os_size.py -C examples/H1OS -B examples/H1OS/build_dev --log-file examples/H1OS/build_dev/logs/debug_20261031_140500.log",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "-v", "--version",
        action="version",
        version=f"%(prog)s {VERSION}",
    )
    parser.add_argument(
        "-B", "--build-dir",
        dest="build_dir",
        required=True,
        help="Explicit target build directory path (required; auto-searching is disabled)",
    )
    parser.add_argument(
        "-C", "--project-dir",
        dest="project_dir",
        default=None,
        help="Application project root directory (defaults to current working directory)",
    )
    parser.add_argument(
        "--rebuild",
        action="store_true",
        default=False,
        help="Force rebuilding firmware via 'idf.py build' before running size diagnostics",
    )
    parser.add_argument(
        "--log-file",
        dest="log_file",
        required=True,
        help="Explicit destination log file path for audit diagnostic output (mandatory; zero-fallback)",
    )
    return parser.parse_args()


def main():
    global LOG_FILE_PATH
    args = parse_args()

    # Strict zero-fallback log destination validation
    if not args.log_file:
        print("\n[ERROR] No audit log file destination provided via --log-file.", file=sys.stderr)
        print("Zero-fallback policy requires an explicit log destination configured in h1os.ini.\n", file=sys.stderr)
        sys.exit(1)

    log_path = Path(args.log_file).resolve()
    log_path.parent.mkdir(parents=True, exist_ok=True)
    LOG_FILE_PATH = log_path

    # Strict build path validation - zero auto-searching allowed
    build_dir_raw = Path(args.build_dir)
    if not build_dir_raw.is_dir():
        print(f"\n[ERROR] Target build directory does not exist: {args.build_dir}", file=sys.stderr)
        print("Please provide an existing build directory via -B <build_dir> (e.g. -B build_prod).", file=sys.stderr)
        sys.exit(1)

    build_dir_path = build_dir_raw.resolve()

    # Resolve project root for audit log output
    if args.project_dir:
        project_root = Path(args.project_dir).resolve()
    elif (build_dir_path.parent / "CMakeLists.txt").exists() and (build_dir_path.parent / "main").is_dir():
        project_root = build_dir_path.parent.resolve()
    else:
        project_root = Path.cwd().resolve()

    py_exe = get_idf_python_exe()
    idf_py = get_idf_py_path()
    check_sizes_script = get_check_sizes_path()

    idf_cmd = f'"{py_exe}" "{idf_py}" -C "{project_root}" -B "{build_dir_path}"'

    # 1. Optional explicit rebuild (only when explicitly requested via --rebuild)
    if args.rebuild:
        log_write("\n[REBUILD] Executing full firmware build as requested...\n")
        run_command("build", "0. REBUILD FIRMWARE", f"{idf_cmd} build", cwd=str(project_root))

    # 2. Strict Artifact Sanity Check: Never guess or trigger an implicit build
    map_path, bin_path = find_target_artifacts(build_dir_path)
    part_bin = build_dir_path / "partition_table" / "partition-table.bin"

    missing_artifacts = []
    if not map_path or not map_path.is_file():
        missing_artifacts.append("Firmware linker map file (*.map)")
    if not bin_path or not bin_path.is_file():
        missing_artifacts.append("Application firmware binary (*.bin)")
    if not part_bin.is_file():
        missing_artifacts.append("Partition table binary (partition_table/partition-table.bin)")

    if missing_artifacts:
        err_msg = f"\n[ERROR] Build artifacts not found in: {build_dir_path}\n"
        for m in missing_artifacts:
            err_msg += f"  - Missing: {m}\n"
        err_msg += (
            "\nZero-fallback policy prohibits silent background compilation during size audit.\n"
            "Please compile firmware first via 'idf.py build' or CMakePresets (or pass --rebuild).\n"
        )
        print(err_msg, file=sys.stderr)
        if LOG_FILE_PATH:
            try:
                with open(LOG_FILE_PATH, "a", encoding="utf-8") as f:
                    f.write(err_msg)
            except Exception:
                pass
        sys.exit(1)

    log_write(f"H1OS Binary Size Diagnostic v{VERSION} (Windows)\n")
    log_write(f"Timestamp: {datetime.datetime.now()}\n")
    log_write(f"Target Build Directory: {build_dir_path}\n")
    log_write(f"Project Root Directory: {project_root}\n")
    log_write(f"Destination Log File  : {LOG_FILE_PATH}\n")
    log_write(f"Active Python: {py_exe}\n")
    log_write("\n[MODE] Instant Direct Inspection (0% CPU, no Ninja dependency check)\n")

    # Step A: Partition table check
    if check_sizes_script and part_bin.exists() and bin_path:
        cmd = f'"{py_exe}" "{check_sizes_script}" --offset 0x8000 partition --type app "{part_bin}" "{bin_path}"'
        run_command("partition", "1. APP PARTITION HEADROOM CHECK", cmd)

    # Step B: Overall memory breakdown (esp_idf_size)
    cmd_size = f'"{py_exe}" -m esp_idf_size "{map_path}"'
    run_command("size", "2. OVERALL MEMORY BREAKDOWN", cmd_size)

    # Step C: Per-component breakdown (esp_idf_size --archives)
    cmd_comp = f'"{py_exe}" -m esp_idf_size --archives "{map_path}"'
    run_command("components", "3. PER-COMPONENT BREAKDOWN", cmd_comp)

    # Step D: Per-file breakdown (esp_idf_size --files)
    cmd_files = f'"{py_exe}" -m esp_idf_size --files "{map_path}"'
    run_command("files", "4. PER-FILE BREAKDOWN", cmd_files)

    # Step E: Binary image headers (esptool image-info)
    cmd_hdr = f'"{py_exe}" -m esptool image-info "{bin_path}"'
    run_command("headers", "5. BINARY IMAGE HEADERS (esptool)", cmd_hdr)

    # Render metrics dashboard
    summary_text = render_summary()
    log_write(summary_text)

    log_write(f"Diagnostics completed successfully.\nFull scroll-back log saved to: {LOG_FILE_PATH}\n")


if __name__ == "__main__":
    main()
