#!/usr/bin/env python3
"""
H1OS Firmware Release Packaging Engine (h1os_pack)
Version: 2.3.0
License: Apache-2.0
"""
import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import zipfile
from pathlib import Path

VERSION = "2.3.0"

# Canonical H1OS 8MB Dual-OTA layout fallback if partitions.csv is absent
DEFAULT_PARTITIONS_CSV = """# ESP-IDF Partition Table (H1OS Dual-Slot 8MB OTA)
# Name,     Type, SubType, Offset, Size,     Flags
nvs,        data, nvs,     0x9000,   0x14000,
otadata,    data, ota,     0x1D000,  0x2000,
phy_init,   data, phy,     0x1F000,  0x1000,
ota_0,      app,  ota_0,   0x20000,  0x300000,
ota_1,      app,  ota_1,   0x320000, 0x300000,
storage,    data, spiffs,  0x620000, 0x1DC000,
epd_frame,  data, undefined, 0x7FC000, 0x4000,
"""


def resolve_project_and_component_dirs(script_dir: Path, explicit_proj: str = None) -> tuple:
    """Resolve application project root and h1os component root."""
    if explicit_proj:
        app_root = Path(explicit_proj).resolve()
    else:
        app_root = Path.cwd().resolve()

    # Component root: script_dir is components/h1os/tools/pack_build
    comp_dir = script_dir.parent.parent
    return app_root, comp_dir


def detect_app_bin_in_dir(build_dir: Path) -> Path:
    """Locate primary application binary inside build directory."""
    if not build_dir or not build_dir.is_dir():
        return None

    proj_desc = build_dir / "project_description.json"
    if proj_desc.exists():
        try:
            data = json.loads(proj_desc.read_text(encoding="utf-8"))
            app_bin = data.get("app_bin")
            if app_bin and (build_dir / app_bin).exists():
                return (build_dir / app_bin).resolve()
            proj_name = data.get("project_name")
            if proj_name and (build_dir / f"{proj_name}.bin").exists():
                return (build_dir / f"{proj_name}.bin").resolve()
        except Exception:
            pass

    default_bin = build_dir / "h1os.bin"
    return default_bin.resolve() if default_bin.exists() else None


def resolve_version(app_root: Path, comp_dir: Path) -> str:
    """Resolve semantic version string from h1os_version.h or git describe."""
    header = comp_dir / "include" / "h1os" / "h1os_version.h"
    if header.exists():
        try:
            for line in header.read_text(encoding="utf-8").splitlines():
                if "H1OS_VERSION_STR" in line:
                    m = re.search(r'"([^"]+)"', line)
                    if m:
                        return m.group(1).lstrip("v")
        except Exception:
            pass

    try:
        res = subprocess.run(
            ["git", "describe", "--tags", "--always"],
            cwd=str(app_root),
            capture_output=True,
            text=True,
            check=True,
        )
        tag = res.stdout.strip().lstrip("v")
        if tag:
            return tag
    except Exception:
        pass
    return "1.0.0"


def get_git_commit(working_dir: Path) -> str:
    """Get short Git commit hash."""
    try:
        res = subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"],
            cwd=str(working_dir),
            capture_output=True,
            text=True,
            check=False,
        )
        if res.returncode == 0 and res.stdout.strip():
            return res.stdout.strip()
    except Exception:
        pass
    return "unknown"


def parse_flash_args(build_dir: Path, app_bin_path: Path) -> dict:
    """Parse flash arguments and binary map offsets."""
    flash_args_file = build_dir / "flash_args"
    info = {
        "flash_mode": "dio",
        "flash_freq": "80m",
        "flash_size": "8MB",
        "binaries": [],
    }

    if flash_args_file.exists():
        for raw_line in flash_args_file.read_text(encoding="utf-8").splitlines():
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            if line.startswith("--"):
                parts = line.split()
                for i in range(len(parts)):
                    if parts[i] in ["--flash-mode", "--flash_mode"] and i + 1 < len(parts):
                        info["flash_mode"] = parts[i + 1]
                    elif parts[i] in ["--flash-freq", "--flash_freq"] and i + 1 < len(parts):
                        info["flash_freq"] = parts[i + 1]
                    elif parts[i] in ["--flash-size", "--flash_size"] and i + 1 < len(parts):
                        info["flash_size"] = parts[i + 1]
                continue

            tokens = line.split(maxsplit=1)
            if len(tokens) == 2:
                offset_str, bin_rel = tokens[0], tokens[1]
                try:
                    offset_int = int(offset_str, 16)
                    bin_abs = (build_dir / bin_rel).resolve()
                    if bin_abs.exists():
                        info["binaries"].append((offset_int, offset_str, bin_rel, bin_abs))
                except ValueError:
                    pass

    if not info["binaries"]:
        default_layout = [
            (0x0, "0x0", "bootloader/bootloader.bin", build_dir / "bootloader" / "bootloader.bin"),
            (0x8000, "0x8000", "partition_table/partition-table.bin", build_dir / "partition_table" / "partition-table.bin"),
            (0x1D000, "0x1d000", "ota_data_initial.bin", build_dir / "ota_data_initial.bin"),
            (0x20000, "0x20000", app_bin_path.name, app_bin_path),
        ]
        for off_int, off_hex, rel, abs_p in default_layout:
            if abs_p.exists():
                info["binaries"].append((off_int, off_hex, rel, abs_p.resolve()))

    info["binaries"].sort(key=lambda x: x[0])
    return info


def sha256_file(filepath: Path) -> str:
    """Compute SHA-256 hash of a file."""
    h = hashlib.sha256()
    with open(filepath, "rb") as f:
        while chunk := f.read(65536):
            h.update(chunk)
    return h.hexdigest()


def parse_args():
    parser = argparse.ArgumentParser(
        description=f"H1OS Firmware Release Packaging Engine v{VERSION}",
        epilog="Examples:\n"
               "  python h1os_pack.py -B build_prod\n"
               "  python h1os_pack.py -B build_dev --dev\n"
               "  python h1os_pack.py -C examples/H1OS -B examples/H1OS/build_prod",
    )
    parser.add_argument(
        "-B", "--build-dir",
        dest="build_dir",
        required=True,
        help="Explicit build directory (required; auto-searching is disabled)",
    )
    parser.add_argument(
        "-C", "--project-dir",
        dest="project_dir",
        default=None,
        help="Explicit application project directory (defaults to current working directory)",
    )
    parser.add_argument(
        "-o", "--out-dir",
        dest="out_dir",
        default=None,
        help="Custom output directory for release artifacts",
    )
    parser.add_argument(
        "--no-zip",
        action="store_true",
        default=False,
        help="Skip zip bundle generation",
    )
    parser.add_argument(
        "-V", "--version",
        dest="version",
        default=None,
        help="Explicit version string override (e.g. 2.4.7)",
    )
    parser.add_argument(
        "--prod",
        action="store_true",
        default=False,
        help="Force production naming (strip -dev tag)",
    )
    parser.add_argument(
        "--dev",
        action="store_true",
        default=False,
        help="Force dev naming (keep -dev tag)",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    script_dir = Path(__file__).resolve().parent

    # Strict build directory validation - zero auto-searching
    build_dir_raw = Path(args.build_dir)
    if not build_dir_raw.is_dir():
        print(f"\n[ERROR] Target build directory does not exist: {args.build_dir}", file=sys.stderr)
        print("Please compile first or provide a valid path via -B <build_dir> (e.g. -B build_prod).", file=sys.stderr)
        sys.exit(1)

    build_dir = build_dir_raw.resolve()
    app_root, comp_dir = resolve_project_and_component_dirs(script_dir, args.project_dir)

    app_bin_path = detect_app_bin_in_dir(build_dir)
    if not app_bin_path:
        print(f"\n[ERROR] Could not find application binary in build directory: {build_dir}", file=sys.stderr)
        print("Please compile firmware first (e.g. 'idf.py -B build_prod build').", file=sys.stderr)
        sys.exit(1)

    app_bin_name = app_bin_path.name
    app_stem = app_bin_path.stem
    app_title = app_stem.upper()

    git_commit = get_git_commit(app_root)
    raw_version = resolve_version(app_root, comp_dir)
    is_prod_build = "prod" in build_dir.name.lower()

    if args.version:
        version = args.version.lstrip("v")
    elif args.prod or (is_prod_build and not args.dev):
        version = re.sub(r"-(dev|alpha|beta|rc\d*)$", "", raw_version, flags=re.IGNORECASE)
    else:
        version = raw_version

    build_flavor = "Production" if is_prod_build else "Development"

    print(f"\n{'='*72}")
    print(f"  {app_title} {build_flavor} Firmware Packager v{VERSION}")
    print(f"  App Root      : {app_root}")
    print(f"  Build Dir     : {build_dir}")
    print(f"  Target Release: v{version} (Commit: {git_commit})")
    print(f"{'='*72}\n")

    flash_info = parse_flash_args(build_dir, app_bin_path)

    # Place release folder directly in project's dist/ directory
    dist_base = Path(args.out_dir) if args.out_dir else (app_root / "dist")
    dist_root = dist_base / f"{app_stem}-v{version}"
    dist_root.mkdir(parents=True, exist_ok=True)
    bins_dir = dist_root / "bins"
    bins_dir.mkdir(parents=True, exist_ok=True)

    factory_bin_name = f"{app_stem}-v{version}-factory.bin"
    factory_bin_path = dist_root / factory_bin_name

    # Step 1: Copy modular binaries into dist/bins/ and dist/<app>.bin
    for _, _, rel, abs_p in flash_info["binaries"]:
        dest_filename = Path(rel).name
        shutil.copy2(abs_p, bins_dir / dest_filename)
        if abs_p.resolve() == app_bin_path.resolve():
            shutil.copy2(abs_p, dist_root / app_bin_name)

    # Step 2: Merge monolithic 0x0 factory binary
    print(f"[*] Generating monolithic factory binary: {factory_bin_name}...")
    max_offset = max(off for off, _, _, _ in flash_info["binaries"])
    last_bin = [abs_p for off, _, _, abs_p in flash_info["binaries"] if off == max_offset][0]
    total_size = max_offset + last_bin.stat().st_size
    buf = bytearray(b"\xFF" * total_size)
    for off_int, _, _, abs_p in flash_info["binaries"]:
        data = abs_p.read_bytes()
        buf[off_int : off_int + len(data)] = data
    factory_bin_path.write_bytes(buf)
    print(f"    [+] Created: {factory_bin_name} ({len(buf)/1024.0:.1f} KB)")

    # Step 3: Provision partitions.csv (canonical component path, app root, or hardcoded layout)
    canonical_part_csv = comp_dir / "partition" / "partitions.csv"
    if canonical_part_csv.exists():
        shutil.copy2(canonical_part_csv, dist_root / "partitions.csv")
    elif (app_root / "partitions.csv").exists():
        shutil.copy2(app_root / "partitions.csv", dist_root / "partitions.csv")
    else:
        (dist_root / "partitions.csv").write_text(DEFAULT_PARTITIONS_CSV, encoding="utf-8")

    # Step 4: Copy flasher.ps1 from script_dir
    flasher_ps1 = script_dir / "flasher.ps1"
    if flasher_ps1.exists():
        shutil.copy2(flasher_ps1, dist_root / "flasher.ps1")
        print(f"    [+] Bundled flasher.ps1 from {flasher_ps1}")
    else:
        print("    [!] Warning: flasher.ps1 not found in script directory.")

    # Step 5: Copy all modular Control-Vector batch files directly from disk (purged hardcoded strings)
    print("[*] Copying modular Control-Vector batch scripts from disk...")
    bat_files = [
        "flash_update_keep_nvs.bat",
        "flash_app_only.bat",
        "flash_factory.bat",
        "flash_nvs_wipe.bat",
        "flash_now.bat",
    ]
    for bat_name in bat_files:
        src_bat = script_dir / bat_name
        if src_bat.exists():
            shutil.copy2(src_bat, dist_root / bat_name)
        else:
            print(f"    [!] Warning: Batch script {bat_name} not found on disk in {script_dir}")

    # Step 6: Copy README.md from disk
    readme_src = script_dir / "README.md"
    if readme_src.exists():
        shutil.copy2(readme_src, dist_root / "README.md")
        shutil.copy2(readme_src, dist_root / "README.txt")

    # Step 7: Compute SHA-256 Checksums
    checksums_file = dist_root / "checksums.sha256"
    checksum_lines = []
    for p in sorted(dist_root.rglob("*")):
        if p.is_file() and p.name != "checksums.sha256":
            rel_name = p.relative_to(dist_root).as_posix()
            sha = sha256_file(p)
            checksum_lines.append(f"{sha}  {rel_name}")
    checksums_file.write_text("\n".join(checksum_lines) + "\n", encoding="utf-8")

    # Step 8: Create Release Zip Archive in app_root/dist/
    if not args.no_zip:
        zip_path = dist_base / f"{app_stem}-v{version}-bundle.zip"
        with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as z:
            for p in sorted(dist_root.rglob("*")):
                if p.is_file():
                    z.write(p, arcname=p.relative_to(dist_base))
        print(f"    [+] Created Release Zip: {zip_path}")

    print(f"\n[SUCCESS] {app_title} v{version} Release Bundle ready at: {dist_root}\n")


if __name__ == "__main__":
    main()
