#!/usr/bin/env python3
"""
H1OS Firmware Release Packaging Engine (h1os_pack)
Version: 2.4.5-dev
License: Apache-2.0
"""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
import zipfile
from pathlib import Path

# Ensure components/h1os/tools is importable
TOOLS_DIR = Path(__file__).resolve().parent.parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

from h1os_tool import (
    H1OS_TOOLING_VERSION,
    check_tooling_dependencies,
    H1OSConfig,
)

VERSION = H1OS_TOOLING_VERSION

try:
    from rich.console import Console
    from rich.panel import Panel
    from rich.table import Table
    from rich import box
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False


def format_bytes(b: int) -> str:
    """Format bytes into readable string."""
    if b >= 1024 * 1024:
        return f"{b / (1024 * 1024):.2f} MB ({b:,} B)"
    if b >= 1024:
        return f"{b / 1024:.2f} KB ({b:,} B)"
    return f"{b} B"


def resolve_project_and_component_dirs(script_dir: Path, explicit_proj: str = None) -> tuple:
    """Resolve application project root and h1os component root."""
    if explicit_proj:
        app_root = Path(explicit_proj).resolve()
    else:
        app_root = Path.cwd().resolve()

    comp_dir = script_dir.parent.parent
    return app_root, comp_dir


def detect_app_bin_in_dir(build_dir: Path) -> Path:
    """Locate primary application binary inside build directory without guesswork."""
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
    """Resolve semantic version string from h1os_version.h or git describe without guesswork."""
    header_candidates = [
        comp_dir / "include" / "h1os" / "h1os_version.h",
        app_root / "include" / "h1os" / "h1os_version.h",
    ]
    for header in header_candidates:
        if header.exists():
            try:
                for line in header.read_text(encoding="utf-8").splitlines():
                    if "H1OS_VERSION_STRING" in line or "H1OS_VERSION_STR" in line:
                        import re
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

    print("\n[ERROR] Unable to resolve semantic version. Specify -V <version> or define H1OS_VERSION_STRING in h1os_version.h.", file=sys.stderr)
    sys.exit(1)


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
               "  python h1os_pack.py -B build\n"
               "  python h1os_pack.py -c h1os.ini -B build_prod\n"
               "  python h1os_pack.py -C examples/H1OS -B examples/H1OS/build",
    )
    parser.add_argument(
        "-v", "--version-info",
        action="version",
        version=f"%(prog)s {VERSION}",
    )
    parser.add_argument(
        "-c", "--config",
        dest="config_path",
        default=None,
        help="Path to h1os.ini configuration file (optional; resolves project defaults)",
    )
    parser.add_argument(
        "-B", "--build-dir",
        dest="build_dir",
        default=None,
        help="Target build directory containing compiled artifacts (e.g. -B build_prod)",
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
        help="Explicit version string override (e.g. 2.4.5-dev)",
    )
    parser.add_argument(
        "--prefix",
        dest="prefix",
        default=None,
        help="Custom prefix for the release zip file (e.g. prod_)",
    )
    parser.add_argument(
        "--suffix",
        dest="suffix",
        default=None,
        help="Custom suffix for the release zip file",
    )
    parser.add_argument(
        "--partition-file",
        dest="partition_file",
        default=None,
        help="Explicit path to partition table CSV (defaults to project root partitions.csv)",
    )
    return parser.parse_args()


def main():
    check_tooling_dependencies()
    args = parse_args()
    script_dir = Path(__file__).resolve().parent

    # Attempt to load H1OSConfig if available
    cfg = None
    try:
        cfg = H1OSConfig(project_dir=args.project_dir, config_path=args.config_path)
    except SystemExit:
        if args.config_path:
            sys.exit(1)
    except Exception:
        pass

    # Resolve build directory
    if not args.build_dir and cfg:
        prof = cfg.resolve_profile()
        if prof and prof.build_dir.is_dir():
            args.build_dir = str(prof.build_dir)

    if not args.build_dir:
        print("\n[ERROR] Target build directory was not provided via -B <build_dir>.", file=sys.stderr)
        print("Please compile first or provide a valid path via -B <build_dir>.", file=sys.stderr)
        sys.exit(1)

    build_dir_raw = Path(args.build_dir)
    if not build_dir_raw.is_dir():
        print(f"\n[ERROR] Target build directory does not exist: {args.build_dir}", file=sys.stderr)
        print("Please compile first or provide a valid path via -B <build_dir>.", file=sys.stderr)
        sys.exit(1)

    build_dir = build_dir_raw.resolve()

    # Resolve application root and component root
    if args.project_dir:
        app_root = Path(args.project_dir).resolve()
    elif cfg:
        app_root = cfg.app_root
    else:
        app_root = Path.cwd().resolve()
    comp_dir = script_dir.parent.parent

    app_bin_path = detect_app_bin_in_dir(build_dir)
    if not app_bin_path:
        print(f"\n[ERROR] Could not find application binary in build directory: {build_dir}", file=sys.stderr)
        print("Please compile firmware first.", file=sys.stderr)
        sys.exit(1)

    app_bin_name = app_bin_path.name
    app_stem = app_bin_path.stem
    app_title = (cfg.app_name.upper() if (cfg and cfg.app_name) else app_stem.upper())

    git_commit = get_git_commit(app_root)
    raw_version = (cfg.version if (cfg and cfg.version) else None) or resolve_version(app_root, comp_dir)
    version = args.version.lstrip("v") if args.version else raw_version

    console = Console(width=78) if HAVE_RICH else None
    if console:
        console.print()
        console.print(Panel(
            f"[bold cyan]{app_title} Firmware Release Packager v{VERSION}[/]\n"
            f"Target Release: [bold green]v{version}[/] (Commit: [yellow]{git_commit}[/])\n"
            f"App Root      : {app_root}\n"
            f"Build Dir     : {build_dir}",
            title="H1OS Release Packager",
            border_style="cyan",
            box=box.ROUNDED,
            width=78,
        ))
        console.print()
    else:
        print(f"\n{'='*72}")
        print(f"  {app_title} Firmware Packager v{VERSION}")
        print(f"  App Root      : {app_root}")
        print(f"  Build Dir     : {build_dir}")
        print(f"  Target Release: v{version} (Commit: {git_commit})")
        print(f"{'='*72}\n")

    flash_info = parse_flash_args(build_dir, app_bin_path)

    # Place release folder directly in project's dist/ directory
    if args.out_dir:
        dist_base = Path(args.out_dir).resolve()
    elif cfg and cfg.dist_dir:
        dist_base = cfg.dist_dir
    else:
        dist_base = app_root / "dist"

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
    max_offset = max(off for off, _, _, _ in flash_info["binaries"])
    last_bin = [abs_p for off, _, _, abs_p in flash_info["binaries"] if off == max_offset][0]
    total_size = max_offset + last_bin.stat().st_size
    buf = bytearray(b"\xFF" * total_size)
    for off_int, _, _, abs_p in flash_info["binaries"]:
        data = abs_p.read_bytes()
        buf[off_int : off_int + len(data)] = data
    factory_bin_path.write_bytes(buf)

    if console:
        table_bins = Table(title="Bundled Firmware Partition Binaries", box=box.ROUNDED, width=78, border_style="cyan")
        table_bins.add_column("Flash Offset", style="yellow", width=14)
        table_bins.add_column("Partition Binary", style="bold white", width=36)
        table_bins.add_column("Size", style="cyan", justify="right", width=20)
        for off_int, off_hex, rel, abs_p in flash_info["binaries"]:
            sz = abs_p.stat().st_size
            table_bins.add_row(off_hex, Path(rel).name, format_bytes(sz))
        table_bins.add_row("0x0 (Monolithic)", factory_bin_name, format_bytes(len(buf)))
        console.print(table_bins)
        console.print()
    else:
        print(f"[*] Generating monolithic factory binary: {factory_bin_name}...")
        print(f"    [+] Created: {factory_bin_name} ({len(buf)/1024.0:.1f} KB)")

    # Step 3: Provision partitions.csv strictly from project root or explicit partition_file
    if args.partition_file:
        part_csv = Path(args.partition_file).resolve()
    elif cfg and cfg.partition_file:
        part_csv = cfg.partition_file
    else:
        part_csv = (app_root / "partitions.csv").resolve()

    if not part_csv.is_file():
        print(f"\n[ERROR] Partition table file not found: {part_csv}", file=sys.stderr)
        print("Please ensure partitions.csv is in project root or configured via partition_file_location in h1os.ini.\n", file=sys.stderr)
        sys.exit(1)

    shutil.copy2(part_csv, dist_root / "partitions.csv")

    # Step 4: Copy flasher.ps1 from script_dir
    flasher_ps1 = script_dir / "flasher.ps1"
    if flasher_ps1.exists():
        shutil.copy2(flasher_ps1, dist_root / "flasher.ps1")

    # Step 5: Copy modular Control-Vector batch files from disk
    bat_files = [
        "flash_update_keep_nvs.bat",
        "flash_app_only.bat",
        "flash_factory.bat",
        "flash_nvs_wipe.bat",
        "flash_now.bat",
    ]
    bundled_bats = []
    for bat_name in bat_files:
        src_bat = script_dir / bat_name
        if src_bat.exists():
            shutil.copy2(src_bat, dist_root / bat_name)
            bundled_bats.append(bat_name)

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

    # Step 8: Create Release Zip Archive in dist_base/
    zip_path = None
    if not args.no_zip:
        prefix_val = args.prefix
        if prefix_val is None and cfg:
            prof = cfg.resolve_profile(build_dir=str(build_dir))
            prefix_val = (prof.pack_prefix if (prof and prof.pack_prefix) else cfg.pack_prefix) or ""
        elif prefix_val is None:
            prefix_val = ""

        suffix_val = args.suffix
        if suffix_val is None and cfg:
            prof = cfg.resolve_profile(build_dir=str(build_dir))
            suffix_val = (prof.pack_suffix if (prof and prof.pack_suffix) else cfg.pack_suffix) or ""
        elif suffix_val is None:
            suffix_val = ""

        if prefix_val or suffix_val:
            zip_filename = f"{prefix_val}{version}{suffix_val}.zip"
        else:
            zip_filename = f"{app_stem}-v{version}.zip"

        zip_path = dist_base / zip_filename
        with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as z:
            for p in sorted(dist_root.rglob("*")):
                if p.is_file():
                    z.write(p, arcname=p.relative_to(dist_base))

    if console:
        summary_body = (
            f"[bold green]✓ Release Bundle Generated Successfully[/]\n\n"
            f"  * [bold white]Destination[/]     : {dist_root}\n"
            f"  * [bold white]Monolithic Image[/]: {factory_bin_name} ({format_bytes(len(buf))})\n"
            f"  * [bold white]Partition Table [/]: {part_csv.name}\n"
            f"  * [bold white]Control Vectors [/]: {len(bundled_bats)} batch runners + flasher.ps1\n"
            f"  * [bold white]SHA-256 Digest  [/]: checksums.sha256\n"
        )
        if zip_path and zip_path.exists():
            summary_body += f"  * [bold white]Release Archive [/]: {zip_path.name} ({format_bytes(zip_path.stat().st_size)})"

        console.print(Panel(
            summary_body,
            title=f"[bold green]{app_title} v{version} Release Summary[/]",
            border_style="green",
            box=box.ROUNDED,
            width=78,
        ))
        console.print()
    else:
        print(f"    [+] Created partition table: {part_csv.name}")
        if flasher_ps1.exists():
            print(f"    [+] Created flasher.ps1")
        if zip_path:
            print(f"    [+] Created Release Zip: {zip_path}")
        print(f"\n[SUCCESS] {app_title} v{version} Release Bundle ready at: {dist_root}\n")


if __name__ == "__main__":
    main()
