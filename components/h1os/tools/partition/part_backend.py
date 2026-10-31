#!/usr/bin/env python3
"""
H1OS Partition Tooling Backend
==============================
Executes hardware flash partition operations via ESP-IDF parttool.py and otatool.py.
"""

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Any

from h1os_tool import H1OSConfig


def find_tool(tool_name: str, fallback_subdir: str) -> Optional[Path]:
    """Find a Python tool script in PATH or under IDF_PATH."""
    p = shutil.which(tool_name)
    if p:
        return Path(p)

    idf_path_str = os.environ.get("IDF_PATH")
    if idf_path_str:
        idf_path = Path(idf_path_str)
        cand = idf_path / fallback_subdir / tool_name
        if cand.is_file():
            return cand
        cand_py = idf_path / fallback_subdir / f"{tool_name}.py"
        if cand_py.is_file():
            return cand_py

    # Common ESP-IDF default install on Windows
    for fallback in [Path("C:/esp/v6.1/esp-idf"), Path("C:/esp/esp-idf")]:
        cand = fallback / fallback_subdir / f"{tool_name}.py"
        if cand.is_file():
            return cand

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

    target_port = port or config.port
    target_baud = str(baud or config.baud or 460800)

    cmd = [
        get_python_exe(),
        str(tool),
        "--port", target_port,
        "--baud", target_baud,
    ]
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

    target_port = port or config.port
    target_baud = str(baud or config.baud or 460800)

    output_path.parent.mkdir(parents=True, exist_ok=True)

    cmd = [
        get_python_exe(),
        str(tool),
        "--port", target_port,
        "--baud", target_baud,
    ]
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
) -> Tuple[bool, str]:
    """Write binary image from input file to target partition on device."""
    tool = get_parttool_path()
    if not tool:
        return False, "Could not locate 'parttool.py'. Ensure ESP-IDF is installed."

    if not input_path.is_file():
        return False, f"Input image file does not exist: {input_path}"

    target_port = port or config.port
    target_baud = str(baud or config.baud or 460800)

    cmd = [
        get_python_exe(),
        str(tool),
        "--port", target_port,
        "--baud", target_baud,
    ]
    if config.partition_file and config.partition_file.is_file():
        cmd.extend(["--partition-table-file", str(config.partition_file)])

    cmd.extend([
        "write_partition",
        "--partition-name", partition_name,
        "--input", str(input_path),
    ])

    try:
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
    """Read and format OTA state machine status via otatool.py."""
    tool = get_otatool_path()
    if not tool:
        return False, "Could not locate 'otatool.py'. Ensure ESP-IDF is installed."

    target_port = port or config.port
    target_baud = str(baud or config.baud or 460800)

    cmd = [
        get_python_exe(),
        str(tool),
        "--port", target_port,
        "--baud", target_baud,
    ]
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

    target_port = port or config.port
    target_baud = str(baud or config.baud or 460800)

    cmd = [
        get_python_exe(),
        str(tool),
        "--port", target_port,
        "--baud", target_baud,
    ]
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
    import re
    fw_match = re.search(
        r"Firmware:\s+(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)\s*\|\s*(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)",
        output,
    )
    if fw_match:
        try:
            seq0 = int(fw_match.group(1), 16)
            seq1 = int(fw_match.group(3), 16)
            valid0 = (seq0 != 0xFFFFFFFF)
            valid1 = (seq1 != 0xFFFFFFFF)
            if valid0 and valid1:
                active_seq = max(seq0, seq1)
                return (active_seq - 1) % num_slots
            elif valid0:
                return (seq0 - 1) % num_slots
            elif valid1:
                return (seq1 - 1) % num_slots
        except ValueError:
            pass
    return 0


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
    # 1. Flash Slot 0
    ok0, msg0 = execute_parttool_write(config, "ota_0", slot0_bin, port=port, baud=baud)
    if not ok0:
        return False, f"Failed writing '{slot0_label}' to ota_0:\n{msg0}"

    # 2. Flash Slot 1
    ok1, msg1 = execute_parttool_write(config, "ota_1", slot1_bin, port=port, baud=baud)
    if not ok1:
        return False, f"Failed writing '{slot1_label}' to ota_1:\n{msg1}"

    # 3. Configure Active Slot
    if active_slot is not None:
        ok_sw, msg_sw = execute_otatool_switch(config, active_slot, port=port, baud=baud)
        if not ok_sw:
            return True, f"Dual images flashed successfully, but active slot switch failed:\n{msg_sw}"

    active_name = slot0_label if active_slot == 0 else slot1_label
    return True, (
        f"Dual-Slot Deployment Complete on {config.chip.upper()}!\n"
        f"  • ota_0 (Slot 0): {slot0_label} ({slot0_bin.name}, {slot0_bin.stat().st_size:,} bytes)\n"
        f"  • ota_1 (Slot 1): {slot1_label} ({slot1_bin.name}, {slot1_bin.stat().st_size:,} bytes)\n"
        f"  • Active Boot Partition: ota_{active_slot} ({active_name})"
    )
