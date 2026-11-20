"""Offline regression tests for components/h1os/tools/partition/part_backend.py."""

from __future__ import annotations

import importlib.util
import sys
from pathlib import Path
from types import ModuleType


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_part_backend() -> ModuleType:
    tools_dir = str(REPO_ROOT / "components" / "h1os" / "tools")
    if tools_dir not in sys.path:
        sys.path.insert(0, tools_dir)
    mod_path = REPO_ROOT / "components" / "h1os" / "tools" / "partition" / "part_backend.py"
    spec = importlib.util.spec_from_file_location("part_backend", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def test_real_h1os_partitions_valid() -> None:
    pb = _load_part_backend()
    csv_path = REPO_ROOT / "examples" / "H1OS" / "partitions.csv"
    parts = pb.parse_csv_partitions(csv_path)
    assert len(parts) >= 5
    errors = pb.validate_partition_layout(parts, flash_size_bytes=0x800000)
    assert errors == []


def test_validate_partition_layout_negative_cases() -> None:
    pb = _load_part_backend()

    overlap = [
        pb.PartitionEntry(name="nvs", type="data", subtype="nvs", offset=0x9000, size=0x14000),
        pb.PartitionEntry(name="ota_0", type="app", subtype="ota_0", offset=0x10000, size=0x100000),
    ]
    assert any("overlaps" in e.lower() for e in pb.validate_partition_layout(overlap))

    misaligned_app = [
        pb.PartitionEntry(name="ota_0", type="app", subtype="ota_0", offset=0x11000, size=0x100000),
    ]
    assert any("64KB-aligned" in e for e in pb.validate_partition_layout(misaligned_app))

    oversized = [
        pb.PartitionEntry(name="storage", type="data", subtype="spiffs", offset=0x700000, size=0x200000),
    ]
    assert any("exceeds flash size" in e for e in pb.validate_partition_layout(oversized, flash_size_bytes=0x800000))
