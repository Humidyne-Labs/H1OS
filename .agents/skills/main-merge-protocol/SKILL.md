---
name: main-merge-protocol
description: Operational reference, validation checklists, and execution commands for merging code into main. Enforces the pre-merge protocol: touching CHANGELOG.md, regenerating docs/api.md with Doxygen & Moxygen, synchronizing semantic version strings across 4 files, verifying zero-warning ESP-IDF builds, and tagging releases.
---

# Pre-Merge to Main Protocol & Release Execution

This skill provides step-by-step procedures, one-liner automation commands, and validation scripts for preparing, merging, and releasing code into the `main` branch of **H1OS**.

---

## 1. Quick Reference: Pre-Merge Checklist

| Step | Action | Tools / Files Involved | Verification |
| :--- | :--- | :--- | :--- |
| **1. Invariant Check** | Firmware Safety Audit | `.agents/rules/coding.md`, `.agents/skills/h1os-firmware-standards` | 10 Safety Invariants validated |
| **2. Clean Build** | Compile firmware | `idf.py -B build_dev build` via ESP-IDF v6.1 profile | Exit code 0, 0 warnings/errors |
| **3. Memory Audit** | Profile memory regions | `murdock_memory_budget` (`embedded-ops`) | DIRAM $\le 85\%$, RTC Slow $\le 4\text{ KB}$ |
| **4. Rev Version** | Bump semantic version | `h1os_version.h`, `idf_component.yml`, `README.md` | All 4 files synchronized |
| **5. Regen API Docs** | Doxygen + Moxygen | `doxygen Doxyfile`, `moxygen` $\rightarrow$ `docs/api.md` | `docs/api.md` updated |
| **6. Update Changelog**| Document modifications | `CHANGELOG.md` | Keep a Changelog entry with date |
| **7. Git Commit & Push**| Push feature branch | `git commit`, `git push origin <branch>` | Branch clean on remote |
| **8. Merge & Tag** | Merge to main & tag | `git checkout main`, `git merge`, `git tag -a` | Main and tag pushed to remote |

---

## 2. Step-by-Step Execution Guide

### Step 1: Rev Semantic Version Strings (4 Locations)

When bumping version (e.g., from `2.3.2-dev` to `2.3.3-dev`):

1. **`components/h1os/include/h1os/h1os_version.h`**:
   Update `H1OS_VERSION_MAJOR`, `H1OS_VERSION_MINOR`, `H1OS_VERSION_PATCH`, and `H1OS_VERSION_STRING`.
2. **`components/h1os/idf_component.yml`**:
   Update `version: "X.Y.Z-tag"`.
3. **`README.md`**:
   Update version badge URL:
   `[![Version](https://img.shields.io/badge/H1OS-vX.Y.Z--tag-brightgreen.svg)](components/h1os/include/h1os/h1os.h)`
4. **`CHANGELOG.md`**:
   Add release section header: `## [X.Y.Z-tag] - YYYY-MM-DD`.

---

### Step 2: Regenerate `docs/api.md`

Execute Doxygen XML generation followed by Moxygen markdown conversion from the repository root:

```powershell
doxygen Doxyfile; if ($LASTEXITCODE -eq 0 -or $?) { moxygen --flavor github -a -o docs/api.md docs/doxygen/xml }
```

*Notes:*
- `Doxyfile` processes all public headers in `components/h1os/include/h1os/*.h` and component sources.
- Generated output is placed at `docs/api.md`.
- Ensure intermediate XML output in `docs/doxygen/` is excluded from git.

---

### Step 3: Touch & Update `CHANGELOG.md`

Insert the new release ledger block directly above the previous release in `CHANGELOG.md`:

```markdown
## [X.Y.Z-tag] - YYYY-MM-DD

### 🚀 Added
* **Feature Name** (`path/to/file.c`): Brief description of new functionality.

### 🔄 Changed
* **Architectural Refactor** (`path/to/file.c`): Description of behavior change.

### 🛡️ Fixed & Hardened
* **Bug Fix / Safety Invariant** (`path/to/file.c`): Specific resolution details.
```

---

### Step 4: Verify Compilation & Memory Headroom

Run incremental build via canonical profile:

```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; Set-Location "c:\Users\Matt\Documents\GitHub\H1OS\examples\H1OS"; idf.py -B build_dev build
```

Then query MCP memory profiling tool:
```json
// Tool: murdock_memory_budget (Server: embedded-ops)
{
  "elf_path": "C:\\Users\\Matt\\Documents\\GitHub\\H1OS\\examples\\H1OS\\build_dev\\h1os.elf"
}
```

Verify that:
- DIRAM usage is $\le 85\%$ ($> 200\text{ KB}$ free).
- RTC Slow SRAM is $\le 4,096\text{ B}$ ($> 3\text{ KB}$ free).
- Flash application partition headroom is $\ge 70\%$.

---

### Step 5: Git Branch Commit, Push, Merge, and Tag

Run the following sequential Git commands:

```bash
# 1. Stage and commit all changes to active feature branch
git add CHANGELOG.md README.md docs/api.md components/h1os/idf_component.yml components/h1os/include/h1os/h1os_version.h
git add -u
git commit -m "chore(release): rev vX.Y.Z-tag, update docs/api.md, and touch changelog"

# 2. Push active feature branch
git push origin <branch_name>

# 3. Switch to main and merge
git checkout main
git merge <branch_name> -m "Merge branch '<branch_name>' into main (vX.Y.Z-tag)"
git push origin main

# 4. Create annotated tag and push
git tag -a vX.Y.Z-tag -m "Release vX.Y.Z-tag: <Summary of changes>"
git push origin vX.Y.Z-tag

# 5. Return to development branch
git checkout <branch_name>
```
