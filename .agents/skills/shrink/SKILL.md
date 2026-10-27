---
name: shrink
description: Quantizes repository documentation, PDFs (300 DPI), and photographic bench test images with all-caps HUMIDITRON/HUMADYNE_LABS EXIF attribution while backing up uncompressed originals to gitignored storage. Triggered by /shrink or /quant.
---

# /shrink & /quant: Repository Asset Optimizer & Quantizer

This skill automates the compression, EXIF attribution, and raster optimization of photographic evidence and PDF datasheets for **H1OS**.

---

## 1. Quick Reference: Commands

| Command | Purpose | Tools Involved |
| :--- | :--- | :--- |
| **`/shrink` or `/quant`** | Run full repository image & PDF shrink pass | `optimize_images.py`, `optimize_pdf.py` |
| **`python tools/agent/optimize_images.py docs/logs/`** | Progressive JPEG encode & EXIF tagging | Pillow, EXIF tags 0x013B/0x8298/0x0131/0x010E |
| **`python tools/agent/optimize_pdf.py <path> --dpi 300`** | Re-encode raster images in PDF at 300 DPI | PyMuPDF (`fitz`), Pillow LANCZOS |

---

## 2. Invariants & Rules

1. **Backup First:** Always ensure original PDFs are copied into `docs/hardware_docs/original_pdfs/` (which is covered by `.gitignore`) before running the PDF quantizer.
2. **Metadata Invariant:** EXIF tags (`Artist`, `Copyright`, `Software`, `ImageDescription`) and PDF metadata (`Author`, `Creator`, `Producer`) MUST be set to `HUMIDITRON/HUMADYNE_LABS`.
3. **Pre-Merge Requirement:** Must be run before committing, pushing, merging into `main`, or releasing new version tags.

---

## 3. Automated One-Liner Execution

Run the complete pipeline from the repository root:

```powershell
# Step 1: Backup uncompressed original PDFs (gitignored)
python -c "import os, shutil, glob; b='docs/hardware_docs/original_pdfs'; os.makedirs(b, exist_ok=True); [shutil.copy2(p, os.path.join(b, os.path.relpath(p, 'docs/hardware_docs'))) for p in glob.glob('docs/hardware_docs/**/*.pdf', recursive=True) if 'original_pdfs' not in p]"

# Step 2: Optimize and stamp test chamber photos
python tools/agent/optimize_images.py docs/logs/

# Step 3: Quantize PDF raster objects to 300 DPI
python tools/agent/optimize_pdf.py docs/hardware_docs/datasheets --dpi 300
```
