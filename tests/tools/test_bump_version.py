"""Offline regression tests for tools/agent/bump_version.py."""

from __future__ import annotations

import importlib.util
from pathlib import Path
from types import ModuleType

import pytest


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_bump_version() -> ModuleType:
    mod_path = REPO_ROOT / "tools" / "agent" / "bump_version.py"
    spec = importlib.util.spec_from_file_location("bump_version", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    import sys

    sys.modules[spec.name] = mod
    spec.loader.exec_module(mod)
    return mod


def test_parse_semver_valid_and_invalid() -> None:
    bv = _load_bump_version()
    v1 = bv.parse_semver("2.4.10-dev")
    assert v1.version_string == "2.4.10-dev"
    assert v1.shields_badge_token == "v2.4.10--dev"  # noqa: S105

    v2 = bv.parse_semver("v3.0.1")
    assert v2.version_string == "3.0.1"
    assert v2.shields_badge_token == "v3.0.1"  # noqa: S105

    with pytest.raises(ValueError):
        bv.parse_semver("2.4")


def test_repo_version_sync_and_dry_run() -> None:
    bv = _load_bump_version()
    cur = bv.read_current_version_from_header(REPO_ROOT)
    assert bv.SEMVER_RE.match(cur.version_string) is not None
    assert bv.check_sync(REPO_ROOT, cur, "6.1.1") == 0
    assert bv.apply_bump(REPO_ROOT, cur, "6.1.1", dry_run=True) == 0
