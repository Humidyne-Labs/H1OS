"""Offline regression tests for tools/agent/optimize_images.py."""

from __future__ import annotations

import importlib.util
from pathlib import Path
from types import ModuleType

from PIL import Image


REPO_ROOT = Path(__file__).resolve().parents[2]


def _load_optimize_images() -> ModuleType:
    mod_path = REPO_ROOT / "tools" / "agent" / "optimize_images.py"
    spec = importlib.util.spec_from_file_location("optimize_images", mod_path)
    assert spec is not None and spec.loader is not None
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def test_optimize_png_to_jpeg_and_exif(tmp_path: Path) -> None:
    opt = _load_optimize_images()
    png_path = tmp_path / "bench_capture.png"
    img = Image.new("RGB", (64, 64), color=(120, 180, 220))
    img.save(png_path, format="PNG")

    orig_bytes, new_bytes = opt.optimize_single_image(png_path, quality=85, convert_png=True, dry_run=False)
    jpg_path = tmp_path / "bench_capture.jpg"
    assert jpg_path.is_file()
    assert orig_bytes > 0 and new_bytes > 0

    with Image.open(jpg_path) as out_im:
        exif = out_im.getexif()
        assert exif.get(opt.TAG_ARTIST) == "HUMIDITRON/HUMADYNE_LABS"
        assert exif.get(opt.TAG_COPYRIGHT) == "HUMIDITRON/HUMADYNE_LABS"
