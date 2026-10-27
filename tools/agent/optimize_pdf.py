#!/usr/bin/env python3
"""
optimize_pdf.py
===============
Raster Image Quantizer & PDF Optimizer for H1OS.

Features:
- Preserves 100% of vector drawings, schematic nets, fonts, and text layout.
- Downsamples oversized embedded raster scans to user-selected DPI (default: 300 DPI).
- Re-encodes raster images with Pillow LANCZOS and JPEG compression.
- Sets PDF author / producer metadata to "humiditron/humadyne_labs".
- Deflates object streams and removes dead unreferenced objects (garbage=4).

Usage:
  python tools/agent/optimize_pdf.py path/to/datasheet.pdf --dpi 300
  python tools/agent/optimize_pdf.py docs/hardware_docs/datasheets/ --dpi 300
"""

import os
import sys
import io
import argparse
from pathlib import Path
import fitz  # PyMuPDF
from PIL import Image

METADATA_CREATOR = "HUMIDITRON/HUMADYNE_LABS"

def optimize_pdf_file(pdf_path: Path, target_dpi: int = 300, quality: int = 85) -> tuple[int, int]:
    """Optimize a single PDF file in place. Returns (orig_bytes, new_bytes)."""
    orig_bytes = pdf_path.stat().st_size

    try:
        doc = fitz.open(pdf_path)
    except Exception as e:
        print(f"[!] Failed to open {pdf_path}: {e}")
        return orig_bytes, orig_bytes

    # Max pixel dimension based on target DPI (assuming 8.5x11 inch page)
    max_dim = int(8.5 * target_dpi)
    replaced_images = 0

    try:
        for page in doc:
            for img_info in page.get_images(full=True):
                xref = img_info[0]
                try:
                    base_img = doc.extract_image(xref)
                    img_bytes = base_img["image"]
                    im = Image.open(io.BytesIO(img_bytes))
                    w, h = im.size

                    # Only process raster images larger than target DPI envelope or oversized
                    if max(w, h) > max_dim:
                        scale = max_dim / max(w, h)
                        new_w = max(1, int(w * scale))
                        new_h = max(1, int(h * scale))
                        im = im.resize((new_w, new_h), Image.Resampling.LANCZOS)
                        if im.mode != "RGB":
                            im = im.convert("RGB")

                        buf = io.BytesIO()
                        im.save(buf, format="JPEG", quality=quality, optimize=True)
                        new_bytes = buf.getvalue()

                        if len(new_bytes) < len(img_bytes):
                            page.replace_image(xref, stream=new_bytes)
                            replaced_images += 1
                except Exception:
                    pass

        # Apply metadata
        meta = doc.metadata
        if not meta:
            meta = {}
        meta["author"] = METADATA_CREATOR
        meta["creator"] = METADATA_CREATOR
        meta["producer"] = METADATA_CREATOR
        doc.set_metadata(meta)

        # Write to temporary file first
        tmp_out = pdf_path.with_suffix(".tmp.pdf")
        doc.save(str(tmp_out), garbage=4, deflate=True, clean=True)
        doc.close()

        new_bytes = tmp_out.stat().st_size
        if new_bytes < orig_bytes:
            tmp_out.replace(pdf_path)
            return orig_bytes, new_bytes
        else:
            tmp_out.unlink()
            return orig_bytes, orig_bytes

    except Exception as e:
        print(f"[!] Error processing {pdf_path}: {e}")
        return orig_bytes, orig_bytes

def main():
    parser = argparse.ArgumentParser(description="H1OS PDF Raster Quantizer & Stream Optimizer")
    parser.add_argument("target", help="PDF file or directory containing PDFs")
    parser.add_argument("--dpi", type=int, default=300, help="Target raster DPI cutoff (default: 300)")
    parser.add_argument("--quality", "-q", type=int, default=85, help="JPEG quality 1-100 (default: 85)")
    args = parser.parse_args()

    target_path = Path(args.target).resolve()
    if not target_path.exists():
        print(f"[!] Target not found: {target_path}")
        sys.exit(1)

    files = [target_path] if target_path.is_file() else list(target_path.rglob("*.pdf"))
    print(f"[*] Processing {len(files)} PDF file(s) with target DPI={args.dpi}, Quality={args.quality}...")

    total_orig = 0
    total_new = 0

    for f in files:
        orig, new = optimize_pdf_file(f, target_dpi=args.dpi, quality=args.quality)
        total_orig += orig
        total_new += new
        if new < orig:
            saved_kb = (orig - new) / 1024
            print(f"  ✓ {f.name}: {orig/1024:.1f} KB -> {new/1024:.1f} KB (saved {saved_kb:.1f} KB, -{(1-new/orig)*100:.1f}%)")

    saved_mb = (total_orig - total_new) / (1024 * 1024)
    print(f"\n[+] PDF optimization pass complete.")
    print(f"    Payload before   : {total_orig / (1024*1024):.2f} MB")
    print(f"    Payload after    : {total_new / (1024*1024):.2f} MB")
    print(f"    Total space saved: {saved_mb:.2f} MB" if total_orig else "")

if __name__ == "__main__":
    main()
