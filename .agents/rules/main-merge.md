# Pre-Merge to Main Governance & Release Invariants

This rule governs the mandatory release and merge checklist required before ANY branch, feature, or bug fix is merged into the `main` branch of **H1OS**.

---

## 1. The Pre-Merge Contract ("No Dirty Main")

The `main` branch represents production-grade, verifiable, and historical stability. Direct commits to `main` without completing the pre-merge checklist are strictly prohibited.

Before executing a merge into `main`, the developer or autonomous agent **MUST** satisfy all invariants in the following order:

```mermaid
graph TD;
    A0["0a. Identity & Name Audit<br/>(python tools/agent/sanitize.py --check --include-dist)"] --> A0b["0b. Asset Shrink & Quantization<br/>(/shrink: optimize_images + optimize_pdf)"];
    A0b --> A0c["0c. Full Audit Harness Gate<br/>(python tools/agent/run_audit.py --all)"];
    A0c --> A["1. Code & Build Verification<br/>(eim run idf.py dev/prod/examples: 0 warnings, 0 errors)"];
    A --> B["2. Rev Semantic Version Strings<br/>(h1os_version.h, idf_component.yml, README.md)"];
    B --> C["3. Regenerate docs/api.md<br/>(doxygen Doxyfile + moxygen)"];
    C --> D["4. Touch & Update CHANGELOG.md<br/>(Keep a Changelog format with timestamp)"];
    D --> E["5. Atomic Commit & Push to Feature Branch"];
    E --> F["6. Checkout main & Merge Feature Branch"];
    F --> G["7. Push main & Create Annotated Tag<br/>(vX.Y.Z-tag)"];
```

---

## 2. Invariant 1: Semantic Version Synchronization

Version strings must never drift across documentation, packaging metadata, and compiled binaries. Whenever merging to `main`, synchronize the version across all managed targets via `tools/agent/bump_version.py`:

```powershell
python tools/agent/bump_version.py --set X.Y.Z-tag --idf-version 6.1.1
python tools/agent/bump_version.py --check
```

This keeps `components/h1os/include/h1os/h1os_version.h`, `components/h1os/idf_component.yml`, `README.md`, `Doxyfile`, `ERRATA.md`, `AGENTS.md`, `.agents/`, `components/h1os/tools/h1os_tool.py`, `docs/guide.md`, and all `docs/architecture/*.md` headers synchronized alongside the `## [X.Y.Z-tag] - YYYY-MM-DD` section in `CHANGELOG.md`.

---

## 3. Invariant 2: API Documentation Regeneration (`docs/api.md`)

Whenever public headers in `components/h1os/include/h1os/` or internal subsystem interfaces are modified:
- Automated API markdown documentation **MUST** be regenerated from source Doxygen annotations.
- The generated `docs/api.md` must be committed in the same pre-merge commit.
- Intermediate Doxygen artifacts (`docs/doxygen/`) must remain excluded from Git via `.gitignore`.

**Generation Command:**
```powershell
doxygen Doxyfile; if ($LASTEXITCODE -eq 0 -or $?) { moxygen --flavor github -a -o docs/api.md docs/doxygen/xml }
```

---

## 4. Invariant 3: Living Changelog Discipline (`CHANGELOG.md`)

Every merge to `main` must touch `CHANGELOG.md` adhering to the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard:

1. Add a new dated section at the top of the ledger:
   ```markdown
   ## [X.Y.Z-tag] - YYYY-MM-DD
   ```
2. Group changes under standard descriptive subheadings:
   - `### 🚀 Added` for new features, drivers, or capabilities.
   - `### 🔄 Changed` for architectural refactors or behavioral changes.
   - `### 🛡️ Fixed & Hardened` for bug fixes, safety invariant patches, or memory reliefs.
   - `### 🗑️ Removed` for deprecated code or pruned orphans.
3. Explicitly reference modified source files (`components/...`) and architectural rationale.

---

## 5. Invariant 4: Verified Clean Build, Audit Harness & Memory Profiling

Before merging:
1. Compile all showcase/example targets via `eim run` (ESP-IDF `v6.1.1`):
   ```powershell
   eim run 'idf.py -C examples/H1OS -B examples/H1OS/build_dev --preset dev build; exit $LASTEXITCODE' v6.1.1
   eim run 'idf.py -C examples/H1OS -B examples/H1OS/build_prod --preset prod build; exit $LASTEXITCODE' v6.1.1
   ```
2. Build must exit with code 0 and ZERO warnings or `-Werror` breaks.
3. Run the unified verification harness (`H1OS-STD-001 Rev 2.2`):
   ```powershell
   python tools/agent/run_audit.py --all
   ```
4. Verify memory budgets using `murdock_memory_budget` (`embedded-ops`) to confirm DIRAM, RTC Slow, and Flash app partition headroom remain within design limits.

---

## 6. Invariant 5: Identity & Workstation Hygiene Audit

Before committing or merging:
1. Run the identity & name sanitizer:
   ```powershell
   python tools/agent/sanitize.py --check
   ```
2. The audit must exit with code 0 (ZERO personal names, workstation paths, or archive ownership leaks).
3. If leaks are detected, resolve with `python tools/agent/sanitize.py --fix` and re-verify.

---

## 7. Invariant 6: Asset Optimization & Shrink Gate (/shrink)

Before staging, committing, or merging to `main`:
1. Run `/shrink` (or `python tools/agent/optimize_images.py docs/logs/` and `python tools/agent/optimize_pdf.py docs/hardware_docs/datasheets`) to guarantee all images have `HUMIDITRON/HUMADYNE_LABS` EXIF attribution and PDF metadata is losslessly harmonized without modifying compressed streams.

---

## 8. Git Branching & Tagging Lifecycle

1. **Commit to Feature Branch:** Commit all staged code, updated version strings, regenerated `docs/api.md`, and `CHANGELOG.md`.
2. **Push Feature Branch:** Push to `origin/<branch_name>`.
3. **Merge into Main:** Checkout `main`, execute `git merge <branch_name> -m "Merge branch '<branch_name>' into main (vX.Y.Z-tag)"`, and push `origin/main`.
4. **Annotated Tagging:** Create an annotated release tag:
   ```bash
   git tag -a vX.Y.Z-tag -m "Release vX.Y.Z-tag: <Summary of changes>"
   git push origin vX.Y.Z-tag
   ```
5. **Branch Hygiene:** Return active working branch back to the development branch.
