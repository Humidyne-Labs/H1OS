#!/usr/bin/env python3
"""
H1OS Unified Developer Tooling Dispatcher & Configuration Engine (h1os_tool)
Version: 2.4.1
License: Apache-2.0

Authoritative master entry point for H1OS developer operations:
- Release packaging (pack)
- Binary size & partition headroom auditing (size)
- Flash operations via native esptool (flash, erase)
- Interactive console launching (menu)
"""
import argparse
import configparser
import datetime
from dataclasses import dataclass
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Union

VERSION = "2.4.1"
SYSTEM_SECTIONS = {"project", "dist", "version", "partitions", "target", "build", "audit", "presets"}


def get_idf_python_exe() -> str:
    """Resolve Python executable from IDF_PYTHON_ENV_PATH or active interpreter."""
    env_path = os.environ.get("IDF_PYTHON_ENV_PATH")
    if env_path:
        p = Path(env_path) / ("Scripts" if os.name == "nt" else "bin") / ("python.exe" if os.name == "nt" else "python")
        if p.exists():
            return str(p)
    return sys.executable


@dataclass
class H1OSProfile:
    """Encapsulates a distinct build profile (e.g. prod, dev, test, ci)."""
    name: str
    preset: str
    build_dir: Path
    audit_log_dir: Path
    pack_prefix: str = ""
    pack_suffix: str = ""
    description: str = ""


class H1OSConfig:
    """Parses, validates, and provides access to h1os.ini settings without guessing."""

    def __init__(self, project_dir: Optional[str] = None, config_path: Optional[str] = None):
        self.comp_dir = Path(__file__).resolve().parent.parent

        # 1. Resolve project directory
        if project_dir:
            self.project_dir = Path(project_dir).resolve()
        else:
            self.project_dir = Path.cwd().resolve()

        # 2. Locate h1os.ini
        if config_path:
            self.ini_path = Path(config_path).resolve()
        else:
            candidates = [
                self.project_dir / "h1os.ini",
                Path.cwd().resolve() / "h1os.ini",
            ]
            self.ini_path = None
            for cand in candidates:
                if cand.is_file():
                    self.ini_path = cand
                    break

        if not self.ini_path or not self.ini_path.is_file():
            print(f"\n[ERROR] H1OS configuration file 'h1os.ini' was not found in: {self.project_dir}", file=sys.stderr)
            print("Please create h1os.ini from components/h1os/h1os.ini.template or pass --config <path>.\n", file=sys.stderr)
            sys.exit(1)

        # 3. Parse INI file
        self.parser = configparser.ConfigParser()
        try:
            self.parser.read(str(self.ini_path), encoding="utf-8")
        except Exception as e:
            print(f"\n[ERROR] Failed to parse {self.ini_path}: {e}\n", file=sys.stderr)
            sys.exit(1)

        # 4. Resolve Base Settings
        proj_rel = self.parser.get("project", "project_dir", fallback=".")
        self.app_root = (self.ini_path.parent / proj_rel).resolve()
        self.app_name = self.parser.get("project", "app_name", fallback="").strip()

        # Resolve dist_dir (supports [dist] dist_dir = dist or [build] dist_dir = dist)
        d_out = ""
        if self.parser.has_section("dist") and self.parser.has_option("dist", "dist_dir"):
            d_out = self.parser.get("dist", "dist_dir").strip()
        elif self.parser.has_section("build") and self.parser.has_option("build", "dist_dir"):
            d_out = self.parser.get("build", "dist_dir").strip()
        if not d_out:
            d_out = "dist"
        self.dist_dir = (self.app_root / d_out).resolve()

        # 5. Parse Dynamic Build Profiles (e.g. [dev], [prod], [test], [profile.dev], etc.)
        self.profiles: Dict[str, H1OSProfile] = {}
        for sec in self.parser.sections():
            is_prof = False
            prof_name = sec
            if sec.startswith("profile.") or sec.startswith("profile:"):
                is_prof = True
                prof_name = sec.split(".", 1)[-1].split(":", 1)[-1].strip().lower()
            elif sec.lower() not in SYSTEM_SECTIONS:
                is_prof = True
                prof_name = sec.strip().lower()

            if is_prof:
                preset = self.parser.get(sec, "preset", fallback=prof_name).strip() or prof_name
                b_dir_str = self.parser.get(sec, "build_dir", fallback=f"build_{prof_name}").strip()
                b_dir = (self.app_root / b_dir_str).resolve()
                audit_str = (
                    self.parser.get(sec, "audit_log", fallback="")
                    or self.parser.get(sec, "audit_log_dir", fallback="")
                ).strip()
                if not audit_str:
                    audit_str = f"{b_dir_str}/logs"
                audit_dir = (self.app_root / audit_str).resolve()
                p_prefix = self.parser.get(sec, "pack_prefix", fallback=f"{prof_name}_").strip()
                p_suffix = self.parser.get(sec, "pack_suffix", fallback="").strip()
                desc = self.parser.get(sec, "description", fallback=f"{prof_name.upper()} Profile").strip()

                self.profiles[prof_name] = H1OSProfile(
                    name=prof_name,
                    preset=preset,
                    build_dir=b_dir,
                    audit_log_dir=audit_dir,
                    pack_prefix=p_prefix,
                    pack_suffix=p_suffix,
                    description=desc,
                )

        # Fallback to legacy [build] section if no profile sections were found
        if not self.profiles and self.parser.has_section("build"):
            b_prod = self.parser.get("build", "build_dir_prod", fallback="build_prod").strip()
            b_dev = self.parser.get("build", "build_dir_dev", fallback="build_dev").strip()
            p_prod = self.parser.get("build", "preset_prod", fallback="prod").strip()
            p_dev = self.parser.get("build", "preset_dev", fallback="dev").strip()
            log_prod = self.parser.get("audit", "prod_build_audit_log", fallback=f"{b_prod}/logs").strip() if self.parser.has_section("audit") else f"{b_prod}/logs"
            log_dev = self.parser.get("audit", "dev_build_audit_log", fallback=f"{b_dev}/logs").strip() if self.parser.has_section("audit") else f"{b_dev}/logs"
            p_pref_prod = self.parser.get("build", "pack_prefix_prod", fallback="prod_").strip()
            p_pref_dev = self.parser.get("build", "pack_prefix_dev", fallback="debug_").strip()
            p_suff = self.parser.get("build", "pack_suffix", fallback="").strip()

            self.profiles["prod"] = H1OSProfile(
                name="prod",
                preset=p_prod,
                build_dir=(self.app_root / b_prod).resolve(),
                audit_log_dir=(self.app_root / log_prod).resolve(),
                pack_prefix=p_pref_prod,
                pack_suffix=p_suff,
                description="Production Release",
            )
            self.profiles["dev"] = H1OSProfile(
                name="dev",
                preset=p_dev,
                build_dir=(self.app_root / b_dev).resolve(),
                audit_log_dir=(self.app_root / log_dev).resolve(),
                pack_prefix=p_pref_dev,
                pack_suffix=p_suff,
                description="Development Build",
            )

        # Backward compatibility aliases
        self.pack_prefix = self.parser.get("build", "pack_prefix", fallback="").strip() if self.parser.has_section("build") else ""
        self.pack_suffix = self.parser.get("build", "pack_suffix", fallback="").strip() if self.parser.has_section("build") else ""
        self.pack_prefix_prod = self.profiles["prod"].pack_prefix if "prod" in self.profiles else ""
        self.pack_prefix_dev = self.profiles["dev"].pack_prefix if "dev" in self.profiles else ""
        self.preset_prod = self.profiles["prod"].preset if "prod" in self.profiles else "prod"
        self.preset_dev = self.profiles["dev"].preset if "dev" in self.profiles else "dev"
        self.build_dir_prod = self.profiles["prod"].build_dir if "prod" in self.profiles else None
        self.build_dir_dev = self.profiles["dev"].build_dir if "dev" in self.profiles else None
        self.prod_build_audit_log = str(self.profiles["prod"].audit_log_dir.relative_to(self.app_root)) if "prod" in self.profiles else "build_prod/logs"
        self.dev_build_audit_log = str(self.profiles["dev"].audit_log_dir.relative_to(self.app_root)) if "dev" in self.profiles else "build_dev/logs"

        # Target settings (active connection & silicon parameters)
        self.chip = self.parser.get("target", "chip", fallback="").strip()
        if not self.chip:
            print(f"\n[ERROR] Mandatory setting 'chip' missing under [target] in {self.ini_path}.", file=sys.stderr)
            sys.exit(1)
        self.port = self.parser.get("target", "port", fallback="").strip()
        try:
            self.baud = self.parser.getint("target", "baud")
        except Exception:
            print(f"\n[ERROR] Mandatory setting 'baud' missing or invalid under [target] in {self.ini_path}.", file=sys.stderr)
            sys.exit(1)
        conf_log_dir = self.parser.get("target", "log_dir", fallback="").strip()
        self.log_dir = (self.app_root / conf_log_dir).resolve() if conf_log_dir else None

        # 5. Validate & Resolve Partitions Table (No guessing)
        part_conf = (
            self.parser.get("partitions", "partition_file_location", fallback="")
            or self.parser.get("partitions", "part_file_location", fallback="")
            or self.parser.get("partitions", "partition_file", fallback="")
        ).strip()
        if part_conf:
            part_path = (self.app_root / part_conf).resolve()
        else:
            part_path = (self.app_root / "partitions.csv").resolve()

        if not part_path.is_file():
            print(f"\n[ERROR] Partition table file not found: {part_path}", file=sys.stderr)
            print("Ensure CMake has provisioned partitions.csv in project root or configure [partitions] partition_file_location in h1os.ini.\n", file=sys.stderr)
            sys.exit(1)
        self.partition_file = part_path

        # 6. Validate & Resolve Semantic Version (No guessing)
        explicit_v = self.parser.get("version", "version", fallback="").strip()
        if explicit_v:
            self.version = explicit_v.lstrip("v")
        else:
            v_file_rel = self.parser.get("version", "version_file", fallback="").strip()
            v_regex = self.parser.get("version", "version_regex", fallback="").strip()
            if not v_file_rel or not v_regex:
                print(f"\n[ERROR] Version extraction not configured in {self.ini_path}.", file=sys.stderr)
                print("Provide explicit 'version' or both 'version_file' and 'version_regex' under [version].\n", file=sys.stderr)
                sys.exit(1)

            candidates = [
                (self.app_root / v_file_rel).resolve(),
                (self.ini_path.parent / v_file_rel).resolve(),
                (self.comp_dir / v_file_rel).resolve(),
            ]
            v_target = None
            for c in candidates:
                if c.is_file():
                    v_target = c
                    break

            if not v_target:
                print(f"\n[ERROR] Version extraction file does not exist: {candidates[0]}", file=sys.stderr)
                sys.exit(1)

            try:
                content = v_target.read_text(encoding="utf-8")
                match = re.search(v_regex, content)
                if not match or not match.group(1):
                    print(f"\n[ERROR] Version regex '{v_regex}' did not match any content in: {v_target}", file=sys.stderr)
                    sys.exit(1)
                self.version = match.group(1).lstrip("v")
            except Exception as e:
                print(f"\n[ERROR] Failed to read version file {v_target}: {e}", file=sys.stderr)
                sys.exit(1)

        # 7. Git metadata
        self.git_commit = self._get_git_commit()
        self.git_tag = self._get_git_tag()

    def _get_git_commit(self) -> str:
        try:
            res = subprocess.run(
                ["git", "rev-parse", "--short", "HEAD"],
                cwd=str(self.app_root),
                capture_output=True,
                text=True,
                check=False,
            )
            if res.returncode == 0 and res.stdout.strip():
                return res.stdout.strip()
        except Exception:
            pass
        return "unknown"

    def _get_git_tag(self) -> str:
        try:
            res = subprocess.run(
                ["git", "describe", "--tags", "--always"],
                cwd=str(self.app_root),
                capture_output=True,
                text=True,
                check=False,
            )
            if res.returncode == 0 and res.stdout.strip():
                return res.stdout.strip().lstrip("v")
        except Exception:
            pass
        return ""

    def resolve_profile(self, profile: Optional[str] = None, build_dir: Optional[str] = None) -> Optional[H1OSProfile]:
        """Resolve a configured H1OSProfile by name or build directory path without guessing."""
        if profile:
            p_clean = profile.strip().lower()
            if p_clean in self.profiles:
                return self.profiles[p_clean]
            print(f"\n[ERROR] Build profile '{profile}' is not defined in {self.ini_path}.", file=sys.stderr)
            print(f"Available configured profiles: {', '.join(self.profiles.keys())}\n", file=sys.stderr)
            return None

        if build_dir:
            b_target = Path(build_dir).resolve()
            for prof in self.profiles.values():
                if prof.build_dir == b_target:
                    return prof

        # Default fallback
        if "prod" in self.profiles:
            return self.profiles["prod"]
        if self.profiles:
            return next(iter(self.profiles.values()))
        return None

    @property
    def audit_log_dir(self) -> Path:
        """Destination directory for size audit diagnostic logs."""
        prof = self.resolve_profile()
        if prof and prof.audit_log_dir:
            return prof.audit_log_dir
        return (self.app_root / "build" / "logs").resolve()

    @property
    def dumps_dir(self) -> Path:
        """Destination directory for raw flash partition dumps and hex logs."""
        return (self.dist_dir / "dumps").resolve()


def run_pack(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[str] = None,
    no_zip: bool = False,
    version_override: Optional[str] = None,
    out_dir: Optional[str] = None,
    prefix: Optional[str] = None,
    suffix: Optional[str] = None,
) -> int:
    """Run release packaging worker for a designated profile or build directory."""
    pack_script = config.comp_dir / "tools" / "pack_build" / "h1os_pack.py"
    if not pack_script.is_file():
        print(f"[ERROR] Packaging script not found: {pack_script}", file=sys.stderr)
        return 1

    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        print("[ERROR] No valid build profile or directory specified or found. Provide -P <profile> or -B <build_dir>.", file=sys.stderr)
        return 1

    if not b_dir.is_dir():
        print(f"[ERROR] Build directory does not exist: {b_dir}", file=sys.stderr)
        print("Please build firmware first via 'idf.py build' or CMakePresets.", file=sys.stderr)
        return 1

    py_exe = get_idf_python_exe()
    cmd = [
        py_exe,
        str(pack_script),
        "-C", str(config.app_root),
        "-B", str(b_dir),
    ]

    if no_zip:
        cmd.append("--no-zip")

    if config.partition_file:
        cmd.extend(["--partition-file", str(config.partition_file)])

    if version_override:
        cmd.extend(["-V", version_override])
    elif config.version:
        cmd.extend(["-V", config.version])

    if out_dir:
        cmd.extend(["-o", str(Path(out_dir).resolve())])
    elif config.dist_dir:
        cmd.extend(["-o", str(config.dist_dir)])

    eff_prefix = prefix
    if eff_prefix is None:
        if prof and prof.pack_prefix:
            eff_prefix = prof.pack_prefix
        elif config.pack_prefix:
            eff_prefix = config.pack_prefix

    eff_suffix = suffix
    if eff_suffix is None:
        if prof and prof.pack_suffix:
            eff_suffix = prof.pack_suffix
        elif config.pack_suffix:
            eff_suffix = config.pack_suffix

    if eff_prefix:
        cmd.extend(["--prefix", eff_prefix])
    if eff_suffix:
        cmd.extend(["--suffix", eff_suffix])

    res = subprocess.run(cmd)
    return res.returncode


def run_size(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[str] = None,
) -> int:
    """Run binary size diagnostic worker for a designated profile or build directory."""
    size_script = config.comp_dir / "tools" / "audit_size" / "h1os_size.py"
    if not size_script.is_file():
        print(f"[ERROR] Size diagnostic script not found: {size_script}", file=sys.stderr)
        return 1

    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        print("[ERROR] No valid build profile or directory specified or found. Provide -P <profile> or -B <build_dir>.", file=sys.stderr)
        return 1

    if not b_dir.is_dir():
        print(f"[ERROR] Build directory does not exist: {b_dir}", file=sys.stderr)
        print("Please build firmware first via 'idf.py build' or CMakePresets.", file=sys.stderr)
        return 1

    target_log_dir = prof.audit_log_dir if prof else (b_dir / "logs")
    target_log_dir.mkdir(parents=True, exist_ok=True)
    prefix = (prof.pack_prefix if prof else config.pack_prefix) or ""
    suffix = (prof.pack_suffix if prof else config.pack_suffix) or ""
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    log_filename = f"{prefix}{timestamp}{suffix}.log"
    log_file_path = target_log_dir / log_filename

    py_exe = get_idf_python_exe()
    cmd = [
        py_exe,
        str(size_script),
        "-C", str(config.app_root),
        "-B", str(b_dir),
        "--log-file", str(log_file_path),
    ]
    res = subprocess.run(cmd)
    return res.returncode


def run_erase(config: H1OSConfig, port: Optional[str] = None, baud: Optional[int] = None, chip: Optional[str] = None) -> int:
    """Erase entire SPI flash using esptool."""
    py_exe = get_idf_python_exe()
    target_chip = chip or config.chip
    target_port = port or config.port
    target_baud = baud or config.baud

    cmd = [py_exe, "-m", "esptool", "--chip", target_chip]
    if target_port:
        cmd.extend(["-p", target_port])
    if target_baud:
        cmd.extend(["-b", str(target_baud)])
    cmd.append("erase-flash")

    print(f"\n[*] Executing Flash Erase: {' '.join(cmd)}")
    res = subprocess.run(cmd)
    return res.returncode


def run_flash(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[str] = None,
    port: Optional[str] = None,
    baud: Optional[int] = None,
    chip: Optional[str] = None,
) -> int:
    """Flash firmware binaries using esptool write-flash @flash_args."""
    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        print("[ERROR] No valid build profile or directory specified or found. Provide -P <profile> or -B <build_dir>.", file=sys.stderr)
        return 1

    if not b_dir.is_dir():
        print(f"[ERROR] Build directory does not exist: {b_dir}", file=sys.stderr)
        print("Please build firmware first via 'idf.py build' or CMakePresets.", file=sys.stderr)
        return 1

    flash_args_file = b_dir / "flash_args"
    if not flash_args_file.is_file():
        print(f"[ERROR] Flash arguments file not found: {flash_args_file}", file=sys.stderr)
        print("Please build firmware first to generate flash_args.", file=sys.stderr)
        return 1

    py_exe = get_idf_python_exe()
    target_chip = chip or config.chip
    target_port = port or config.port
    target_baud = baud or config.baud

    cmd = [py_exe, "-m", "esptool", "--chip", target_chip]
    if target_port:
        cmd.extend(["-p", target_port])
    if target_baud:
        cmd.extend(["-b", str(target_baud)])
    cmd.extend(["write-flash", f"@{flash_args_file.name}"])

    print(f"\n[*] Executing Firmware Flash: {' '.join(cmd)}")
    print(f"[*] Target Profile: {prof.name.upper() if prof else 'CUSTOM'}")
    print(f"[*] Working Directory: {b_dir}\n")
    res = subprocess.run(cmd, cwd=str(b_dir))
    return res.returncode


def run_build(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[str] = None,
    preset: Optional[str] = None,
    clean: bool = False,
    reconfig_only: bool = False,
) -> int:
    """Execute ESP-IDF CMake / Ninja build or reconfiguration."""
    idf_path = os.environ.get("IDF_PATH")
    if not idf_path:
        print("[ERROR] IDF_PATH environment variable is not set. Please activate ESP-IDF environment.", file=sys.stderr)
        return 1

    idf_py = Path(idf_path) / "tools" / "idf.py"
    if not idf_py.is_file():
        print(f"[ERROR] idf.py not found at: {idf_py}", file=sys.stderr)
        return 1

    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        print("[ERROR] No build directory or profile configured or provided.", file=sys.stderr)
        return 1

    eff_preset = preset or (prof.preset if prof else None)

    if clean:
        print(f"\n[*] Executing Clean on: {b_dir}")
        if b_dir.exists():
            import shutil
            shutil.rmtree(str(b_dir), ignore_errors=True)
            print(f"    [+] Erased build directory: {b_dir}")
        dep_lock = config.app_root / "dependencies.lock"
        if dep_lock.is_file():
            dep_lock.unlink()
            print(f"    [+] Erased: {dep_lock}")
        mg_comp = config.app_root / "managed_components"
        if mg_comp.is_dir():
            import shutil
            shutil.rmtree(str(mg_comp), ignore_errors=True)
            print(f"    [+] Erased: {mg_comp}")

    py_exe = get_idf_python_exe()
    action = "reconfigure" if reconfig_only else "build"
    cmd = [py_exe, str(idf_py), "-C", str(config.app_root), "-B", str(b_dir)]
    if eff_preset:
        cmd.extend(["--preset", eff_preset])
    cmd.append(action)

    print(f"\n[*] Executing ESP-IDF {'Reconfigure' if reconfig_only else 'Build'}: {' '.join(cmd)}\n")
    res = subprocess.run(cmd)
    return res.returncode


def run_clean(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[str] = None,
    clean_all: bool = False,
) -> int:
    """Erase target build directory, dependencies, or all profiles without rebuilding."""
    import shutil

    if clean_all:
        print("\n[*] Executing Clean on ALL configured profiles and dependencies...")
        for prof in config.profiles.values():
            if prof.build_dir.exists():
                shutil.rmtree(str(prof.build_dir), ignore_errors=True)
                print(f"    [+] Erased build directory: {prof.build_dir}")
        dep_lock = config.app_root / "dependencies.lock"
        if dep_lock.is_file():
            dep_lock.unlink()
            print(f"    [+] Erased: {dep_lock}")
        mg_comp = config.app_root / "managed_components"
        if mg_comp.is_dir():
            shutil.rmtree(str(mg_comp), ignore_errors=True)
            print(f"    [+] Erased: {mg_comp}")
        print("[+] Clean All complete.\n")
        return 0

    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        print("[ERROR] No build directory or profile configured or provided.", file=sys.stderr)
        return 1

    print(f"\n[*] Executing Clean on: {b_dir}")
    if b_dir.exists():
        shutil.rmtree(str(b_dir), ignore_errors=True)
        print(f"    [+] Erased build directory: {b_dir}")
    else:
        print(f"    [*] Directory already clean (does not exist): {b_dir}")

    print(f"[+] Clean complete for '{prof.name if prof else b_dir.name}'.\n")
    return 0


def auto_detect_serial_port() -> Optional[str]:
    """Auto-detect connected ESP or active serial port without resetting target."""
    try:
        import serial.tools.list_ports
        ports = list(serial.tools.list_ports.comports())
        if not ports:
            return None
        # Prioritize Espressif USB-JTAG / USB CDC / UART bridges
        for p in ports:
            desc = (p.description or "").lower()
            hwid = (p.hwid or "").lower()
            mfg = (p.manufacturer or "").lower()
            if "303a" in hwid or "espressif" in desc or "espressif" in mfg:
                return p.device
            if any(k in desc or k in hwid for k in ("jtag", "usb serial", "uart", "ch340", "cp210", "ftdi")):
                return p.device
        # Exclude legacy motherboard COM1 if other ports exist
        non_com1 = [p.device for p in ports if p.device.upper() != "COM1"]
        if non_com1:
            return non_com1[0]
        return ports[0].device
    except Exception:
        return None


def spawn_serial_monitor(
    config: H1OSConfig,
    profile: Optional[str] = None,
    build_dir: Optional[Union[str, Path]] = None,
    port: Optional[str] = None,
    baud: Optional[int] = None,
    timestamps: bool = False,
    log: bool = False,
) -> Tuple[bool, str]:
    """Spawn an independent, detached H1OS serial monitor in an external terminal window."""
    monitor_script = config.comp_dir / "tools" / "monitor" / "h1os_monitor.py"
    if not monitor_script.is_file():
        return False, f"H1OS monitor script not found: {monitor_script}"

    prof = config.resolve_profile(profile, build_dir)
    if build_dir:
        b_dir = Path(build_dir).resolve()
    elif prof:
        b_dir = prof.build_dir
    else:
        first_prof = list(config.profiles.values())[0] if config.profiles else None
        b_dir = first_prof.build_dir if first_prof else None

    eff_port = port or config.port
    if not eff_port:
        eff_port = auto_detect_serial_port()

    eff_baud = baud or config.baud or 115200
    eff_chip = config.chip or "esp32s3"
    if config.log_dir:
        target_log_dir = config.log_dir
    elif prof and prof.audit_log_dir:
        target_log_dir = prof.audit_log_dir
    else:
        target_log_dir = (config.app_root / "build_prod" / "logs").resolve()

    py_exe = get_idf_python_exe()

    mon_args = [py_exe, str(monitor_script), "-b", str(eff_baud), "--chip", eff_chip, "--log-dir", str(target_log_dir)]
    if eff_port:
        mon_args.extend(["-p", eff_port])
    if timestamps:
        mon_args.append("-t")
    if log:
        mon_args.append("-l")

    app_root_str = str(config.app_root)
    child_args = [f"'{a}'" if (" " in a or "\\" in a) else a for a in mon_args]
    child_command = f"& {child_args[0]} " + " ".join(child_args[1:])

    if os.name == "nt":
        # 1. Prefer Windows Terminal (wt.exe) with PowerShell profile for flicker-free DirectX rendering
        wt_exe = shutil.which("wt.exe") or shutil.which("wt")
        if wt_exe:
            try:
                wt_cmd = [
                    wt_exe,
                    "nt",
                    "--profile", "PowerShell",
                    "powershell", "-Command", child_command,
                ]
                subprocess.Popen(wt_cmd, cwd=app_root_str)
                return True, f"Spawned H1OS Serial Monitor on {eff_port or 'auto-detect'} in Windows Terminal."
            except Exception:
                pass

        # 2. Fallback: Standalone PowerShell window
        try:
            ps_cmd = ["powershell.exe", "-Command", child_command]
            subprocess.Popen(
                ps_cmd,
                cwd=app_root_str,
                creationflags=subprocess.CREATE_NEW_CONSOLE,
            )
            return True, f"Spawned H1OS Serial Monitor on {eff_port or 'auto-detect'} in PowerShell."
        except Exception:
            try:
                cmd = ["conhost.exe"] + mon_args
                subprocess.Popen(
                    cmd,
                    cwd=app_root_str,
                    creationflags=subprocess.CREATE_NEW_CONSOLE,
                )
                return True, f"Spawned H1OS Serial Monitor on {eff_port or 'auto-detect'} in external terminal."
            except Exception as e:
                return False, f"Failed to spawn external monitor window: {e}"

    elif sys.platform == "darwin":
        osa_script = f'tell application "Terminal" to do script "cd \'{app_root_str}\' && {args_str}"'
        try:
            subprocess.Popen(["osascript", "-e", osa_script])
            return True, f"Spawned H1OS Serial Monitor on {eff_port or 'auto-detect'} in macOS Terminal."
        except Exception as e:
            return False, f"Failed to spawn macOS Terminal: {e}"

    else:
        for term in ("x-terminal-emulator", "gnome-terminal", "konsole", "xterm"):
            if shutil.which(term):
                try:
                    if term == "gnome-terminal":
                        cmd = [term, "--title=H1OS Serial Monitor", "--", "bash", "-c", f"cd '{app_root_str}' && {args_str}; exec bash"]
                    else:
                        cmd = [term, "-T", "H1OS Serial Monitor", "-e", f"bash -c 'cd \"{app_root_str}\" && {args_str}; exec bash'"]
                    subprocess.Popen(cmd)
                    return True, f"Spawned H1OS Serial Monitor on {eff_port or 'auto-detect'} in {term}."
                except Exception as e:
                    return False, f"Failed to spawn {term}: {e}"
        return False, "No graphical terminal emulator found (tried x-terminal-emulator, gnome-terminal, konsole, xterm)."


def run_menu(config: H1OSConfig) -> int:
    """Launch interactive Rich developer tooling console."""
    menu_script = config.comp_dir / "tools" / "menu" / "h1os_menu.py"
    if not menu_script.is_file():
        print(f"[ERROR] Menu script not found: {menu_script}", file=sys.stderr)
        return 1

    py_exe = get_idf_python_exe()
    cmd = [py_exe, str(menu_script), "-C", str(config.app_root)]
    res = subprocess.run(cmd)
    return res.returncode


def main():
    parser = argparse.ArgumentParser(
        description=f"H1OS Master Developer Tooling & Dispatcher v{VERSION}",
        epilog="Examples:\n"
               "  python h1os_tool.py menu\n"
               "  python h1os_tool.py pack -B my_build\n"
               "  python h1os_tool.py pack -B my_build --prefix prod_\n"
               "  python h1os_tool.py size -B my_build\n"
               "  python h1os_tool.py flash -B my_build\n"
               "  python h1os_tool.py erase",
    )
    parser.add_argument("-C", "--project-dir", dest="project_dir", default=None, help="Application project root directory")
    parser.add_argument("-c", "--config", dest="config", default=None, help="Explicit path to h1os.ini")

    subparsers = parser.add_subparsers(dest="command", help="Available subcommands")

    # pack subcommand
    pack_p = subparsers.add_parser("pack", help="Package H1OS Zero-Dependency Release Bundle")
    pack_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    pack_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    pack_p.add_argument("--no-zip", action="store_true", default=False, help="Skip zip bundle generation")
    pack_p.add_argument("-V", "--version", dest="version", default=None, help="Explicit version string override")
    pack_p.add_argument("-o", "--out-dir", dest="out_dir", default=None, help="Custom output directory")
    pack_p.add_argument("--prefix", dest="prefix", default=None, help="Custom prefix for the release zip file")
    pack_p.add_argument("--suffix", dest="suffix", default=None, help="Custom suffix for the release zip file")

    # size subcommand
    size_p = subparsers.add_parser("size", help="Run H1OS Binary Size & Partition Headroom Diagnostic")
    size_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    size_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")

    # build subcommand
    build_p = subparsers.add_parser("build", help="Execute ESP-IDF build with optional preset and clean")
    build_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    build_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    build_p.add_argument("--preset", dest="preset", default=None, help="CMake preset to build")
    build_p.add_argument("--clean", action="store_true", default=False, help="Perform clean rebuild (erase build_dir, lock, components)")

    # reconfigure subcommand
    reconf_p = subparsers.add_parser("reconfigure", help="Execute ESP-IDF CMake reconfiguration")
    reconf_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    reconf_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    reconf_p.add_argument("--preset", dest="preset", default=None, help="CMake preset to reconfigure")

    # clean subcommand (isolated clean without rebuilding)
    clean_p = subparsers.add_parser("clean", help="Erase target build directory without rebuilding")
    clean_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    clean_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    clean_p.add_argument("--all", action="store_true", default=False, help="Clean all configured build directories and dependencies")

    # flash subcommand
    flash_p = subparsers.add_parser("flash", help="Flash firmware binaries to hardware via esptool")
    flash_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile (defined in h1os.ini)")
    flash_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    flash_p.add_argument("-p", "--port", dest="port", default=None, help="Serial COM port")
    flash_p.add_argument("-b", "--baud", type=int, dest="baud", default=None, help="Serial baud rate")
    flash_p.add_argument("--chip", dest="chip", default=None, help="Target silicon chip (default: esp32s3)")

    # erase subcommand
    erase_p = subparsers.add_parser("erase", help="Erase entire target SPI flash die via esptool")
    erase_p.add_argument("-p", "--port", dest="port", default=None, help="Serial COM port")
    erase_p.add_argument("-b", "--baud", type=int, dest="baud", default=None, help="Serial baud rate")
    erase_p.add_argument("--chip", dest="chip", default=None, help="Target silicon chip (default: esp32s3)")

    # monitor subcommand
    monitor_p = subparsers.add_parser("monitor", help="Spawn dedicated H1OS serial monitor in external terminal window")
    monitor_p.add_argument("-P", "--profile", dest="profile", default=None, help="Target build profile")
    monitor_p.add_argument("-B", "--build-dir", dest="build_dir", default=None, help="Explicit build directory")
    monitor_p.add_argument("-p", "--port", dest="port", default=None, help="Serial COM port")
    monitor_p.add_argument("-b", "--baud", type=int, dest="baud", default=None, help="Serial baud rate")
    monitor_p.add_argument("-t", "--timestamps", action="store_true", default=False, help="Enable millisecond timestamps on launch (default: OFF)")
    monitor_p.add_argument("-l", "--log", action="store_true", default=False, help="Enable session disk logging on launch (default: OFF)")

    # menu subcommand
    subparsers.add_parser("menu", help="Launch interactive Rich developer tooling console")

    args = parser.parse_args()

    # Load configuration
    config = H1OSConfig(project_dir=args.project_dir, config_path=args.config)

    # If no subcommand given, default to menu
    if not args.command or args.command == "menu":
        sys.exit(run_menu(config))
    elif args.command == "pack":
        sys.exit(run_pack(
            config,
            profile=args.profile,
            build_dir=args.build_dir,
            no_zip=args.no_zip,
            version_override=args.version,
            out_dir=args.out_dir,
            prefix=args.prefix,
            suffix=args.suffix,
        ))
    elif args.command == "size":
        sys.exit(run_size(config, profile=args.profile, build_dir=args.build_dir))
    elif args.command == "build":
        sys.exit(run_build(config, profile=args.profile, build_dir=args.build_dir, preset=args.preset, clean=args.clean, reconfig_only=False))
    elif args.command == "reconfigure":
        sys.exit(run_build(config, profile=args.profile, build_dir=args.build_dir, preset=args.preset, clean=False, reconfig_only=True))
    elif args.command == "clean":
        sys.exit(run_clean(config, profile=args.profile, build_dir=args.build_dir, clean_all=args.all))
    elif args.command == "flash":
        sys.exit(run_flash(config, profile=args.profile, build_dir=args.build_dir, port=args.port, baud=args.baud, chip=args.chip))
    elif args.command == "erase":
        sys.exit(run_erase(config, port=args.port, baud=args.baud, chip=args.chip))
    elif args.command == "monitor":
        ok, msg = spawn_serial_monitor(
            config,
            profile=args.profile,
            build_dir=args.build_dir,
            port=args.port,
            baud=args.baud,
            timestamps=args.timestamps,
            log=args.log,
        )
        print(msg)
        sys.exit(0 if ok else 1)
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
