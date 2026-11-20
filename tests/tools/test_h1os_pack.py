"""Offline regression tests for components/h1os/tools/pack_build/h1os_pack.py."""

from __future__ import annotations

import importlib.util
import re
import sys
from pathlib import Path
from types import ModuleType


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_h1os_pack() -> ModuleType:
    tools_dir = str(REPO_ROOT / "components" / "h1os" / "tools")
    if tools_dir not in sys.path:
        sys.path.insert(0, tools_dir)
    mod_path = REPO_ROOT / "components" / "h1os" / "tools" / "pack_build" / "h1os_pack.py"
    spec = importlib.util.spec_from_file_location("h1os_pack", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def test_format_bytes_and_resolve_version() -> None:
    hp = _load_h1os_pack()
    assert hp.format_bytes(512) == "512 B"
    assert "KB" in hp.format_bytes(4096)
    assert "MB" in hp.format_bytes(2 * 1024 * 1024)

    ver = hp.resolve_version(REPO_ROOT / "examples" / "H1OS", REPO_ROOT / "components" / "h1os")
    vh_text = (REPO_ROOT / "components" / "h1os" / "include" / "h1os" / "h1os_version.h").read_text(encoding="utf-8")
    m = re.search(r'#define\s+H1OS_VERSION_STRING\s+"([^"]+)"', vh_text)
    assert m is not None
    assert ver == m.group(1)


def test_parse_synthetic_flash_args(tmp_path: Path) -> None:
    hp = _load_h1os_pack()
    (tmp_path / "bootloader").mkdir()
    (tmp_path / "partition_table").mkdir()
    boot_bin = tmp_path / "bootloader" / "bootloader.bin"
    pt_bin = tmp_path / "partition_table" / "partition-table.bin"
    app_bin = tmp_path / "h1os.bin"
    boot_bin.write_bytes(b"\xe9" * 16)
    pt_bin.write_bytes(b"\xaa" * 16)
    app_bin.write_bytes(b"\x55" * 16)

    flash_args = tmp_path / "flash_args"
    flash_args.write_text(
        "--flash_mode dio --flash_freq 80m --flash_size 8MB\n"
        "0x0 bootloader/bootloader.bin\n"
        "0x8000 partition_table/partition-table.bin\n"
        "0x20000 h1os.bin\n",
        encoding="utf-8",
    )

    info = hp.parse_flash_args(tmp_path, app_bin)
    assert info["flash_mode"] == "dio"
    assert info["flash_freq"] == "80m"
    assert info["flash_size"] == "8MB"
    offsets = [entry[0] for entry in info["binaries"]]
    assert offsets == [0x0, 0x8000, 0x20000]
