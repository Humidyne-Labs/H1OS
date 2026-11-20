"""Offline regression tests for tools/agent/sanitize.py."""

from __future__ import annotations

import gzip
import importlib.util
import zipfile
from pathlib import Path
from types import ModuleType


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_sanitize() -> ModuleType:
    import sys

    mod_path = REPO_ROOT / "tools" / "agent" / "sanitize.py"
    spec = importlib.util.spec_from_file_location("sanitize", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mod
    spec.loader.exec_module(mod)
    return mod


def test_sanitize_clean_and_leaks_across_files_zip_and_dist_gz(tmp_path: Path) -> None:
    san = _load_sanitize()
    cfg_file = tmp_path / "names.txt"
    cfg_file.write_text("REPLACEMENT = Redacted\nAliceSmith\n", encoding="utf-8")
    cfg = san.NameConfig(config_path=cfg_file)

    clean_root = tmp_path / "clean_ws"
    clean_root.mkdir()
    (clean_root / "note.txt").write_text("Hardware sensor reading OK.\n", encoding="utf-8")
    eng_clean = san.SanitizerEngine(config=cfg, root_dir=clean_root, include_dist=True)
    eng_clean.scan_all(include_git_history=False)
    assert len(eng_clean.text_violations) == 0
    assert len(eng_clean.archive_violations) == 0

    dirty_root = tmp_path / "dirty_ws"
    dirty_root.mkdir()
    (dirty_root / "src.c").write_text(
        r'// path C:\Users\AliceSmith\proj' + "\n",
        encoding="utf-8",
    )
    zip_path = dirty_root / "bundle.zip"
    with zipfile.ZipFile(zip_path, "w") as zf:
        zf.writestr("meta.txt", "Author: AliceSmith\n")

    dist_dir = dirty_root / "dist"
    dist_dir.mkdir()
    gz_path = dist_dir / "vault.json.gz"
    with gzip.open(gz_path, "wb") as gz:
        gz.write(b'{"owner": "AliceSmith"}\n')

    eng_no_dist = san.SanitizerEngine(config=cfg, root_dir=dirty_root, include_dist=False)
    eng_no_dist.scan_all(include_git_history=False)
    assert len(eng_no_dist.text_violations) == 1
    assert len(eng_no_dist.archive_violations) == 1

    eng_with_dist = san.SanitizerEngine(config=cfg, root_dir=dirty_root, include_dist=True)
    eng_with_dist.scan_all(include_git_history=False)
    assert len(eng_with_dist.text_violations) == 1
    assert len(eng_with_dist.archive_violations) == 2
