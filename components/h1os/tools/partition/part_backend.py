#!/usr/bin/env python3
"""
H1OS Partition Tooling Backend
==============================
Thin, zero-fallback execution layer wrapping ESP-IDF's parttool.py and otatool.py.
Handles live progress streaming, clean OTA state parsing, and firmware image introspection.
"""

import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Any

# Ensure components/h1os/tools is importable
CURRENT_DIR = Path(__file__).resolve().parent
TOOLS_DIR = CURRENT_DIR.parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

from h1os_tool import H1OSConfig


def find_tool(tool_name: str, comp_subpath: str) -> Optional[Path]:
    """Locate tool script in ESP-IDF installation directory."""
    idf_path_env = os.environ.get("IDF_PATH")
    if idf_path_env:
        cand = Path(idf_path_env) / comp_subpath / f"{tool_name}.py"
        if cand.is_file():
            return cand

    try:
        res = subprocess.run(
            ["where", f"{tool_name}.py"],
            capture_output=True,
            text=True,
            check=False,
        )
        if res.returncode == 0 and res.stdout.strip():
            p = Path(res.stdout.strip().splitlines()[0])
            if p.is_file():
                return p
    except Exception:
        pass

    candidates = [
        Path("C:/esp/v6.1/esp-idf") / comp_subpath / f"{tool_name}.py",
        Path("C:/esp/esp-idf") / comp_subpath / f"{tool_name}.py",
    ]
    for c in candidates:
        if c.is_file():
            return c

    return None


def get_parttool_path() -> Optional[Path]:
    """Resolve path to parttool.py."""
    return find_tool("parttool", "components/partition_table")


def get_otatool_path() -> Optional[Path]:
    """Resolve path to otatool.py."""
    return find_tool("otatool", "components/app_update")


def get_python_exe() -> str:
    """Return active Python executable."""
    return sys.executable


def execute_parttool_erase(
    config: H1OSConfig,
    partition_name: str,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Erase a specific partition on the connected target device."""
    tool = get_parttool_path()
    if not tool:
        return False, "Could not locate 'parttool.py'. Ensure ESP-IDF is installed and in PATH/IDF_PATH."

    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    cmd = [get_python_exe(), str(tool)]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.extend(["erase_partition", "--partition-name", partition_name])

    try:
        res = subprocess.run(cmd, capture_output=True, text=True, check=False)
        if res.returncode == 0:
            return True, f"Successfully erased partition '{partition_name}'."
        err_msg = res.stderr.strip() or res.stdout.strip()
        return False, f"parttool erase failed (code {res.returncode}):\n{err_msg}"
    except Exception as e:
        return False, f"Failed to execute parttool erase: {e}"


def execute_parttool_read(
    config: H1OSConfig,
    partition_name: str,
    output_path: Path,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Read raw binary bytes of a partition from device to output file."""
    tool = get_parttool_path()
    if not tool:
        return False, "Could not locate 'parttool.py'. Ensure ESP-IDF is installed."

    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    output_path.parent.mkdir(parents=True, exist_ok=True)

    cmd = [get_python_exe(), str(tool)]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.extend([
        "read_partition",
        "--partition-name", partition_name,
        "--output", str(output_path),
    ])

    try:
        res = subprocess.run(cmd, capture_output=True, text=True, check=False)
        if res.returncode == 0 and output_path.is_file():
            size = output_path.stat().st_size
            return True, f"Read {size:,} bytes from '{partition_name}' to {output_path.name}."
        err_msg = res.stderr.strip() or res.stdout.strip()
        return False, f"parttool read failed (code {res.returncode}):\n{err_msg}"
    except Exception as e:
        return False, f"Failed to execute parttool read: {e}"


def execute_parttool_write(
    config: H1OSConfig,
    partition_name: str,
    input_path: Path,
    port: Optional[str] = None,
    baud: Optional[int] = None,
    stream: bool = False,
) -> Tuple[bool, str]:
    """Write binary image from input file to target partition on device."""
    tool = get_parttool_path()
    if not tool:
        return False, "Could not locate 'parttool.py'. Ensure ESP-IDF is installed."

    if not input_path.is_file():
        return False, f"Input image file does not exist: {input_path}"

    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    cmd = [get_python_exe(), str(tool)]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.extend([
        "write_partition",
        "--partition-name", partition_name,
        "--input", str(input_path),
    ])

    try:
        if stream:
            proc = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                bufsize=1,
            )
            output_lines = []
            for line in proc.stdout:
                line_str = line.rstrip()
                output_lines.append(line_str)
                if line_str:
                    print(f"  [esptool] {line_str}")
                    sys.stdout.flush()
            proc.wait()
            if proc.returncode == 0:
                return True, f"Successfully wrote {input_path.stat().st_size:,} bytes to '{partition_name}'."
            err_msg = "\n".join(output_lines)
            return False, f"parttool write failed (code {proc.returncode}):\n{err_msg}"
        else:
            res = subprocess.run(cmd, capture_output=True, text=True, check=False)
            if res.returncode == 0:
                return True, f"Successfully wrote {input_path.stat().st_size:,} bytes to '{partition_name}'."
            err_msg = res.stderr.strip() or res.stdout.strip()
            return False, f"parttool write failed (code {res.returncode}):\n{err_msg}"
    except Exception as e:
        return False, f"Failed to execute parttool write: {e}"


def execute_otatool_read(
    config: H1OSConfig,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Read raw OTA state machine status via otatool.py."""
    tool = get_otatool_path()
    if not tool:
        return False, "Could not locate 'otatool.py'. Ensure ESP-IDF is installed."

    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    cmd = [get_python_exe(), str(tool)]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.append("read_otadata")

    try:
        res = subprocess.run(cmd, capture_output=True, text=True, check=False)
        out = res.stdout.strip() or res.stderr.strip()
        if res.returncode == 0:
            return True, out
        return False, f"otatool read_otadata failed (code {res.returncode}):\n{out}"
    except Exception as e:
        return False, f"Failed to execute otatool: {e}"


def parse_otadata_info(output: str) -> Dict[str, Any]:
    """Parse clean, structured OTA state machine dictionary from otatool output."""
    info = {
        "active_slot": 0,
        "slot0_seq": "0xFFFFFFFF",
        "slot0_crc": "0x00000000",
        "slot0_valid": False,
        "slot1_seq": "0xFFFFFFFF",
        "slot1_crc": "0x00000000",
        "slot1_valid": False,
        "chip": "",
        "mac": "",
        "summary": "Unknown",
        "raw": output,
    }

    chip_m = re.search(r"Detecting chip type\.\.\.\s*([^\r\n]+)", output)
    if chip_m:
        info["chip"] = chip_m.group(1).strip()
    mac_m = re.search(r"MAC:\s*([0-9a-fA-F:]{17})", output)
    if mac_m:
        info["mac"] = mac_m.group(1).strip()

    fw_match = re.search(
        r"Firmware:\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s*\|\s*(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)",
        output,
    )
    if fw_match:
        s0_str, c0_str, s1_str, c1_str = fw_match.groups()
        info["slot0_seq"] = s0_str.upper()
        info["slot0_crc"] = c0_str.upper()
        info["slot1_seq"] = s1_str.upper()
        info["slot1_crc"] = c1_str.upper()
        try:
            s0_val = int(s0_str, 16)
            s1_val = int(s1_str, 16)
            info["slot0_valid"] = (s0_val != 0xFFFFFFFF)
            info["slot1_valid"] = (s1_val != 0xFFFFFFFF)
            if info["slot0_valid"] and info["slot1_valid"]:
                active_seq = max(s0_val, s1_val)
                info["active_slot"] = (active_seq - 1) % 2
            elif info["slot0_valid"]:
                info["active_slot"] = (s0_val - 1) % 2
            elif info["slot1_valid"]:
                info["active_slot"] = (s1_val - 1) % 2
        except ValueError:
            pass

    act = info["active_slot"]
    info["summary"] = f"Boot Target: ota_{act} (Slot {act})"
    return info


def execute_otatool_switch(
    config: H1OSConfig,
    target_slot: int,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Switch active OTA boot partition slot (0 or 1)."""
    tool = get_otatool_path()
    if not tool:
        return False, "Could not locate 'otatool.py'. Ensure ESP-IDF is installed."

    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    cmd = [get_python_exe(), str(tool)]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.extend(["switch_ota_partition", "--slot", str(target_slot)])

    try:
        res = subprocess.run(cmd, capture_output=True, text=True, check=False)
        if res.returncode == 0:
            return True, f"Successfully switched active boot partition to slot {target_slot} (ota_{target_slot})."
        err_msg = res.stderr.strip() or res.stdout.strip()
        return False, f"otatool switch failed (code {res.returncode}):\n{err_msg}"
    except Exception as e:
        return False, f"Failed to execute otatool switch: {e}"


def parse_active_ota_slot(output: str, num_slots: int = 2) -> int:
    """Parse active OTA slot index from otatool read_otadata output."""
    info = parse_otadata_info(output)
    return info.get("active_slot", 0)


def execute_otatool_toggle(
    config: H1OSConfig,
    num_slots: int = 2,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Toggle active boot partition between slot 0 and slot 1."""
    ok, read_msg = execute_otatool_read(config, port=port, baud=baud)
    current_slot = parse_active_ota_slot(read_msg, num_slots=num_slots) if ok else 0
    next_slot = 1 if current_slot == 0 else 0

    ok_switch, switch_msg = execute_otatool_switch(config, next_slot, port=port, baud=baud)
    if ok_switch:
        return True, f"Active boot slot toggled: ota_{current_slot} (Slot {current_slot}) -> ota_{next_slot} (Slot {next_slot})."
    return False, f"Failed to toggle OTA boot slot:\n{switch_msg}"


def execute_dual_slot_deploy(
    config: H1OSConfig,
    slot0_bin: Path,
    slot1_bin: Path,
    slot0_label: str = "Slot 0",
    slot1_label: str = "Slot 1",
    active_slot: Optional[int] = 0,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, str]:
    """Flash two compiled binaries to ota_0 and ota_1 in sequence and configure active boot slot."""
    print("\n" + "=" * 70)
    print(f"[*] Dual-Slot OTA Deployment: 2 Binaries -> ota_0 & ota_1")
    print(f"    Port: {port or config.port or 'Auto-detect'} | Baud: {baud or config.baud or 460800}")
    print("=" * 70)

    # 1. Flash Slot 0
    print(f"\n[*] [1/3] Flashing '{slot0_label}' ({slot0_bin.name}, {slot0_bin.stat().st_size:,} bytes) -> ota_0...")
    sys.stdout.flush()
    ok0, msg0 = execute_parttool_write(config, "ota_0", slot0_bin, port=port, baud=baud, stream=True)
    if not ok0:
        return False, f"Failed writing '{slot0_label}' to ota_0:\n{msg0}"
    print(f"[+] Slot 0 (ota_0) written and verified successfully.")
    sys.stdout.flush()

    # 2. Flash Slot 1
    print(f"\n[*] [2/3] Flashing '{slot1_label}' ({slot1_bin.name}, {slot1_bin.stat().st_size:,} bytes) -> ota_1...")
    sys.stdout.flush()
    ok1, msg1 = execute_parttool_write(config, "ota_1", slot1_bin, port=port, baud=baud, stream=True)
    if not ok1:
        return False, f"Failed writing '{slot1_label}' to ota_1:\n{msg1}"
    print(f"[+] Slot 1 (ota_1) written and verified successfully.")
    sys.stdout.flush()

    # 3. Configure Active Slot
    if active_slot is not None:
        print(f"\n[*] [3/3] Setting Active Boot Partition to Slot {active_slot} (ota_{active_slot})...")
        sys.stdout.flush()
        ok_sw, msg_sw = execute_otatool_switch(config, active_slot, port=port, baud=baud)
        if not ok_sw:
            return True, f"Dual images flashed successfully, but active slot switch failed:\n{msg_sw}"
        print(f"[+] Active boot partition committed: ota_{active_slot}")
        sys.stdout.flush()

    active_name = slot0_label if active_slot == 0 else slot1_label
    print("\n" + "=" * 70)
    return True, (
        f"Dual-Slot Deployment Complete on {config.chip.upper()}!\n"
        f"  • ota_0 (Slot 0): {slot0_label} ({slot0_bin.name}, {slot0_bin.stat().st_size:,} bytes)\n"
        f"  • ota_1 (Slot 1): {slot1_label} ({slot1_bin.name}, {slot1_bin.stat().st_size:,} bytes)\n"
        f"  • Active Boot Target: ota_{active_slot} ({active_name})"
    )


def read_flash_header(
    config: H1OSConfig,
    offset: int,
    size: int = 1024,
    port: Optional[str] = None,
    baud: Optional[int] = None,
) -> Tuple[bool, bytes]:
    """Read raw bytes from a physical flash offset using esptool.py."""
    target_port = (port or config.port or "").strip()
    target_baud = str(baud or config.baud or 460800)

    with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as tf:
        temp_path = Path(tf.name)

    cmd = [
        get_python_exe(),
        "-m", "esptool",
    ]
    if target_port:
        cmd.extend(["--port", target_port])
    if target_baud:
        cmd.extend(["--baud", target_baud])

    cmd.extend([
        "read-flash",
        hex(offset),
        str(size),
        str(temp_path),
    ])

    try:
        res = subprocess.run(cmd, capture_output=True, text=True, check=False, timeout=8)
        if res.returncode == 0 and temp_path.is_file():
            data = temp_path.read_bytes()
            temp_path.unlink(missing_ok=True)
            return True, data
        temp_path.unlink(missing_ok=True)
        return False, b""
    except Exception:
        temp_path.unlink(missing_ok=True)
        return False, b""


def parse_app_descriptor(raw_bytes: bytes) -> Optional[Dict[str, Any]]:
    """Parse esp_image_header_t and esp_app_desc_t from partition header bytes."""
    if len(raw_bytes) < 288:
        return None
    magic = raw_bytes[0]
    if magic != 0xE9:
        return None

    seg_count = raw_bytes[1]
    entry_addr = struct.unpack("<I", raw_bytes[4:8])[0]
    hash_appended = bool(raw_bytes[23])

    desc_bytes = raw_bytes[32:32+256]
    desc_magic = struct.unpack("<I", desc_bytes[0:4])[0]
    if desc_magic != 0xABCD5432:
        return None

    sec_ver = struct.unpack("<I", desc_bytes[4:8])[0]
    version = desc_bytes[16:48].split(b"\x00")[0].decode("utf-8", "ignore")
    project = desc_bytes[48:80].split(b"\x00")[0].decode("utf-8", "ignore")
    b_time  = desc_bytes[80:96].split(b"\x00")[0].decode("utf-8", "ignore")
    b_date  = desc_bytes[96:112].split(b"\x00")[0].decode("utf-8", "ignore")
    idf_ver = desc_bytes[112:144].split(b"\x00")[0].decode("utf-8", "ignore")
    sha256_hex = desc_bytes[144:176].hex()

    return {
        "project": project,
        "version": version,
        "compile_time": f"{b_date} {b_time}".strip(),
        "idf_ver": idf_ver,
        "entry_addr": hex(entry_addr),
        "seg_count": seg_count,
        "sha256": sha256_hex,
        "sha256_short": sha256_hex[:16] + "...",
    }
