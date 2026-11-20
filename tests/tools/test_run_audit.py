"""Offline unit tests for tools/agent/run_audit.py core verification gates."""

from __future__ import annotations

import importlib.util
from pathlib import Path
from types import ModuleType


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_run_audit() -> ModuleType:
    import sys

    mod_path = REPO_ROOT / "tools" / "agent" / "run_audit.py"
    spec = importlib.util.spec_from_file_location("run_audit", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mod
    spec.loader.exec_module(mod)
    return mod


def test_repo_layers_pass() -> None:
    ra = _load_run_audit()
    res = ra.check_layers(REPO_ROOT)
    assert res.status == "PASS"


def test_waiver_validation_rejects_s0_and_malformed(tmp_path: Path) -> None:
    ra = _load_run_audit()
    src = tmp_path / "components" / "h1os" / "src"
    src.mkdir(parents=True)
    (src / "bad_s0.c").write_text(
        "// [H1OS-WAIVER: PIT-01-B | Class: S0 | Reason: test | Proof: unit]\n",
        encoding="utf-8",
    )
    (src / "bad_fmt.c").write_text("// [H1OS-WAIVER: missing fields]\n", encoding="utf-8")
    (src / "ok.c").write_text(
        "// [H1OS-WAIVER: PIT-01-E | Class: S2 | Reason: bounded | Proof: test.c:1]\n",
        encoding="utf-8",
    )

    res, valid = ra.scan_waivers(tmp_path)
    assert res.status == "FAIL"
    assert "components/h1os/src/ok.c" in valid
    assert 1 in valid["components/h1os/src/ok.c"]


def test_lexicon_permits_lvgl_and_flags_prohibited_terms(tmp_path: Path) -> None:
    ra = _load_run_audit()
    docs = tmp_path / "docs"
    docs.mkdir()
    ok_md = docs / "clean.md"
    ok_md.write_text("Configure `lv_font_t.fallback` for missing glyphs.\n", encoding="utf-8")
    res_ok = ra.check_lexicon(tmp_path)
    assert res_ok.status == "PASS"

    bad_c = tmp_path / "driver.c"
    bad_c.write_text("// Trigger the " + "stand" + "-down " + "boun" + "cer logic\n", encoding="utf-8")
    res_bad = ra.check_lexicon(tmp_path)
    assert res_bad.status == "FAIL"
