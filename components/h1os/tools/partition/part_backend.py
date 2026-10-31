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
