# Asset Optimization, Quantization & Backup Invariants

This rule defines mandatory repository hygiene policies for binary assets, images, datasheets, and PDF documentation in **H1OS**.

---

## 1. Slash Commands & Triggers

* **Trigger Commands:** `/shrink` or `/quant`
* **Trigger Workflow:** Executes automated image EXIF stamping, raster quantization (300 DPI), and uncompressed archive pruning across documentation and test benches.

---

## 2. Core Directives & Quality Safeguards

1. **Pre-Merge Invariant (Shrink Before Release):**
   - The agent **MUST** execute the image and PDF optimization pass before any release commit, push, merge to `main`, or tag creation.
   - Prevents multi-megabyte digital camera photos and raw PDF object streams from accumulating in permanent Git history.

2. **Mandatory Gitignored Backup Invariant:**
   - Prior to modifying or quantizing any vendor PDF or board documentation, the agent **MUST** guarantee an uncompressed original is preserved in the local gitignored backup path:
     `docs/hardware_docs/original_pdfs/`
   - Gitignore patterns `docs/hardware_docs/original_pdfs/`, `*.orig.pdf`, and `*.original.pdf` ensure original uncompressed documents remain accessible locally to the developer without polluting the remote repository.

3. **Instrument-Grade Resolution Policy (300 DPI Minimum):**
   - Pure vector schematics (`esp32_s3_touch_epaper_1.54_schematic.pdf`) must never be rasterized or downsampled.
   - Datasheets with embedded raster curves, oscillograms, and pin tables are quantized to **300 DPI** (`--dpi 300`, LANCZOS filter) to maintain 100% legibility of pin labels and traces.

4. **All-Caps Attribution Invariant:**
   - All processed photographic images and PDF documents must be stamped with project ownership metadata:
     - **EXIF Tags** (`Artist`, `Copyright`, `Software`, `ImageDescription`): `HUMIDITRON/HUMADYNE_LABS`
     - **PDF Metadata** (`Author`, `Creator`, `Producer`): `HUMIDITRON/HUMADYNE_LABS`

---

## 3. Standard Execution Commands

### Full Repository Asset Shrink Pass:
```powershell
# 1. Backup original PDFs to gitignored directory
python -c "import os, shutil, glob; os.makedirs('docs/hardware_docs/original_pdfs', exist_ok=True); [shutil.copy2(p, os.path.join('docs/hardware_docs/original_pdfs', os.path.relpath(p, 'docs/hardware_docs'))) for p in glob.glob('docs/hardware_docs/**/*.pdf', recursive=True) if 'original_pdfs' not in p]"

# 2. Quantize & stamp test bench photos with HUMIDITRON/HUMADYNE_LABS EXIF
python tools/agent/optimize_images.py docs/logs/

# 3. Quantize vendor PDFs to 300 DPI and stamp metadata
python tools/agent/optimize_pdf.py docs/hardware_docs/datasheets --dpi 300
```
