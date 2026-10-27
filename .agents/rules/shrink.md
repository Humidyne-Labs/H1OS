# Asset Optimization & Metadata Harmonization Invariants

This rule defines mandatory repository hygiene policies for binary assets, images, datasheets, and PDF documentation in **H1OS**.

---

## 1. Slash Commands & Triggers

* **Trigger Commands:** `/shrink` or `/quant`
* **Trigger Workflow:** Executes automated image EXIF stamping, progressive JPEG optimization, and lossless PDF metadata stamping across documentation and test benches.

---

## 2. Core Directives & Quality Safeguards

1. **Pre-Merge Invariant (Shrink Before Release):**
   - The agent **MUST** execute the image optimization and PDF metadata harmonization pass before any release commit, push, merge to `main`, or tag creation.
   - Prevents unoptimized digital camera photos from accumulating in permanent Git history.

2. **Zero-Degradation PDF Policy (Metadata Only):**
   - PDFs are an inherently compressed container format. The agent **MUST NEVER** re-compress, downsample, or modify embedded PDF object streams or images.
   - `tools/agent/optimize_pdf.py` operates **strictly losslessly** to harmonize document metadata (`Author`, `Creator`, `Producer`).

3. **All-Caps Attribution Invariant:**
   - All processed photographic images and PDF documents must be stamped with project ownership metadata:
     - **EXIF Tags** (`Artist`, `Copyright`, `Software`, `ImageDescription`): `HUMIDITRON/HUMADYNE_LABS`
     - **PDF Metadata** (`Author`, `Creator`, `Producer`): `HUMIDITRON/HUMADYNE_LABS`

---

## 3. Standard Execution Commands

### Full Repository Asset Shrink & Harmonization Pass:
```powershell
# 1. Quantize & stamp test bench photos with HUMIDITRON/HUMADYNE_LABS EXIF
python tools/agent/optimize_images.py docs/logs/

# 2. Losslessly harmonize PDF metadata
python tools/agent/optimize_pdf.py docs/hardware_docs/datasheets
```
