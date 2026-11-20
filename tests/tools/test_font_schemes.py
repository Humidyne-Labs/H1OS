"""Offline verification tests for epd-font v1.0.23 schemes and CSV metric tables."""

from __future__ import annotations

import csv
import json
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
FONTS_ROOT = REPO_ROOT / "components" / "h1os" / "tools" / "fonts"


def test_schemes_valid_json_and_metadata() -> None:
    scheme_files = sorted((FONTS_ROOT / "schemes").glob("*.json"))
    assert len(scheme_files) >= 3
    for path in scheme_files:
        data = json.loads(path.read_text(encoding="utf-8"))
        assert "schema_version" in data
        if path.name.startswith("h1os_"):
            assert "output_branding" in data
            roles = data["output_branding"].get("semantic_roles", {})
            assert "HUMID1_FONT_UI_BODY" in roles


def test_metrics_csv_headers_populated() -> None:
    metrics_dir = FONTS_ROOT / "metrics"
    cw_files = sorted(metrics_dir.glob("char_widths_*.csv"))
    kp_files = sorted(metrics_dir.glob("kern_pairs_*.csv"))
    assert len(cw_files) > 0
    assert len(cw_files) == len(kp_files)

    sample_cw = metrics_dir / "char_widths_humid1_font_plex_sans_normal_14.csv"
    assert sample_cw.is_file()
    with sample_cw.open("r", encoding="utf-8") as fh:
        reader = csv.DictReader(fh)
        assert reader.fieldnames is not None
        assert {"unicode_dec", "adv_w_raw", "width_px"}.issubset(set(reader.fieldnames))
        rows = list(reader)
        assert len(rows) > 50

    sample_kp = metrics_dir / "kern_pairs_humid1_font_plex_sans_normal_14.csv"
    assert sample_kp.is_file()
    with sample_kp.open("r", encoding="utf-8") as fh:
        kp_reader = csv.DictReader(fh)
        assert kp_reader.fieldnames is not None
        assert {"left_code", "right_code", "kern_raw_16th"}.issubset(set(kp_reader.fieldnames))
