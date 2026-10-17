# Plan: Add -B Build Directory Flag to inspect_size.py

## 1. Objective
Enhance `examples/H1OS/inspect_size.py` to accept the standard ESP-IDF build directory flag (`-B <dir>` or `--build-dir <dir>`), allowing direct invocation like:
```powershell
python inspect_size.py -B build_prod
python inspect_size.py -B build_dev
```
While preserving backwards-compatible automatic detection when no argument is passed.

---

## 2. Technical Scope

### A. Argument Parsing (`examples/H1OS/inspect_size.py`)
- Integrate `argparse` to support:
  - `-B <dir>` or `--build-dir <dir>` (explicit build directory path or name).
  - Optional positional `build_dir` (e.g. `python inspect_size.py build_prod`).
- Validation:
  - If the specified `-B <dir>` does not exist or does not contain build artifacts (`.bin` or `.map`), print a clear diagnostic error and exit cleanly (`sys.exit(1)`).
- Smarter Fallback Detection (`find_active_build_dir`):
  - When no `-B` argument is passed, inspect candidate folders (`build_prod`, `build_dev`, `build`, etc.) and automatically select the **most recently modified** active build directory rather than following a static list order.

### B. Command Execution
- Construct the `idf.py -B <dir> ...` commands dynamically using the verified build directory.
- Execute:
  1. `idf.py -B <dir> size`
  2. `idf.py -B <dir> size-components`
  3. `idf.py -B <dir> size-files`
  4. `python -m esptool image-info <bin_path>`
  5. Executive Size Metrics Summary table.

### C. Build Skill Documentation
- Update `.agents/skills/h1os-build/SKILL.md` to document the `-B` usage for `inspect_size.py`.

---

## 3. Execution Checklist
- [x] Implement `argparse` and mtime-sorted fallback in `examples/H1OS/inspect_size.py`.
- [x] Maintain synchronized reusable copy in project root `tools/inspect_size.py`.
- [x] Test `python inspect_size.py -B build_prod`.
- [x] Test `python inspect_size.py` (auto-detection).
- [x] Document in `.agents/skills/h1os-build/SKILL.md`.

