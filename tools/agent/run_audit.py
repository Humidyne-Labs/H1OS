#!/usr/bin/env python3
"""
H1OS Automated Safety & Architecture Audit Harness (H1OS-STD-001 Rev 2.2)
==========================================================================
Executes modular or full verification gates across firmware C/C++, Python host
tooling, 4-layer boundaries, inline waivers, lexicon policy, stack/RTC budgets,
typography widths, semantic version sync, identity sanitization, and tests.
"""

from __future__ import annotations

import argparse
import collections
import concurrent.futures
import csv
import datetime as dt
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Set, Tuple


SEMGREP_PLUGIN_DIR = (
    Path.home() / ".gemini" / "config" / "plugins" / "embedded-harness" / "rules" / "semgrep"
)
DEFAULT_CPPCHECK_EXE = Path("C:/Program Files/Cppcheck/cppcheck.exe")
ESP_CLANG_ROOT = Path("C:/Espressif/tools/esp-clang")
XTENSA_GCC_ROOT = Path("C:/Espressif/tools/xtensa-esp-elf")

WAIVER_RE = re.compile(
    r"\[H1OS-WAIVER:\s*(PIT-\d{2}-[A-Z])\s*\|\s*Class:\s*(S[0-2])\s*\|"
    r"\s*Reason:\s*([^|\]]+)\|\s*Proof:\s*([^\]]+)\]"
)
INCLUDE_RE = re.compile(
    r'^\s*#\s*include\s+"(?:h1os/)?((?:hal|sub|orch|h1os)_[^"]+\.h)"'
)
STACK_LINE_RE = re.compile(r"^(.*?):(\d+):(?:\d+:)?([^\t]+)\t(\d+)\t(.*)$")
SU_OBJDUMP_SYM_RE = re.compile(r"^([0-9a-fA-F]+)\s+<([^>]+)>:")
CALL_INSN_RE = re.compile(
    r"call(?:x)?(?:0|4|8|12)\s+([0-9a-fA-F]+)\s+<([^>]+)>"
)
L32R_INSN_RE = re.compile(r"\bl32r\s+a\d+,\s*([0-9a-fA-F]+)\b")
LABEL_TEXT_RE = re.compile(
    r'lv_label_set_text(?:_static)?\s*\([^,]+,\s*"((?:\\.|[^"\\])*)"\s*\)'
)
SET_FONT_RE = re.compile(
    r"lv_obj_set_style_text_font\s*\([^,]+,\s*(&?[A-Za-z0-9_]+)\s*,"
)

MISRA_MANDATORY_RULES: Set[str] = {
    "9.1", "12.5", "13.6", "17.3", "17.4", "17.6", "19.1",
    "21.13", "21.17", "21.18", "21.19", "21.20",
    "22.1", "22.2", "22.4", "22.5", "22.6",
}
MISRA_ADVISORY_RULES: Set[str] = {
    "1.2", "2.3", "2.4", "2.5", "2.6", "2.7", "4.2", "5.9",
    "8.7", "8.9", "8.13", "10.5", "11.4", "11.5", "12.1", "12.3", "12.4",
    "13.4", "15.1", "15.3", "15.4", "15.5", "17.8", "18.4", "19.2",
    "20.1", "20.2", "20.3", "20.4", "20.5", "20.10", "20.11", "20.12",
    "21.1", "21.2",
}


@dataclass
class GateResult:
    name: str
    status: str  # PASS | FAIL | SKIP
    summary: str
    details: List[str] = field(default_factory=list)


@dataclass(frozen=True)
class WaiverEntry:
    rel_path: str
    line: int
    pitfall: str
    severity: str
    reason: str
    proof: str


def find_repo_root() -> Path:
    cur = Path(__file__).resolve().parent
    for _ in range(6):
        if (cur / "components" / "h1os" / "include" / "h1os" / "h1os_version.h").is_file():
            return cur
        cur = cur.parent
    raise FileNotFoundError("Could not locate H1OS repository root.")


def _utf8_env() -> Dict[str, str]:
    env = dict(os.environ)
    env["PYTHONUTF8"] = "1"
    env["PYTHONIOENCODING"] = "utf-8"
    return env


def _norm_rel(path: Path, repo_root: Path) -> str:
    try:
        return path.resolve().relative_to(repo_root.resolve()).as_posix()
    except ValueError:
        return path.as_posix()


def _layer_for_stem(name: str) -> Optional[int]:
    if name.startswith("hal_"):
        return 1
    if name.startswith("sub_"):
        return 2
    if name.startswith("orch_"):
        return 3
    if name.startswith("h1os_"):
        return 4
    return None


def _base_module_id(filename: str) -> str:
    stem = Path(filename).stem
    for suffix in ("_internal", "_private"):
        if stem.endswith(suffix):
            return stem[: -len(suffix)]
    return stem


def _module_prefix(filename: str) -> str:
    stem = Path(filename).stem
    parts = stem.split("_", 2)
    return "_".join(parts[:2]) if len(parts) >= 2 else stem


def check_layers(repo_root: Path) -> GateResult:
    scan_dirs = [
        repo_root / "components" / "h1os" / "include" / "h1os",
        repo_root / "components" / "h1os" / "src",
    ]
    violations: List[str] = []
    files_scanned = 0

    for d in scan_dirs:
        if not d.is_dir():
            continue
        for fpath in sorted(d.iterdir()):
            if fpath.suffix.lower() not in {".c", ".cpp", ".h"}:
                continue
            src_layer = _layer_for_stem(fpath.name)
            if src_layer is None:
                continue
            files_scanned += 1
            src_mod = _base_module_id(fpath.name)
            src_prefix = _module_prefix(fpath.name)
            lines = fpath.read_text(encoding="utf-8", errors="replace").splitlines()
            for lineno, line in enumerate(lines, 1):
                m = INCLUDE_RE.match(line)
                if not m:
                    continue
                inc = m.group(1)
                inc_layer = _layer_for_stem(inc)
                if inc_layer is None:
                    continue
                inc_mod = _base_module_id(inc)
                inc_prefix = _module_prefix(inc)
                rel = _norm_rel(fpath, repo_root)
                if inc_layer > src_layer:
                    violations.append(
                        f"{rel}:{lineno}: Layer {src_layer} includes upper Layer {inc_layer} header '{inc}'"
                    )
                elif src_layer == 2 and inc_layer == 2 and inc_mod != src_mod and inc_prefix != src_prefix:
                    violations.append(
                        f"{rel}:{lineno}: Layer 2 cross-subsystem include '{inc}' forbidden"
                    )

    if violations:
        return GateResult(
            name="layers",
            status="FAIL",
            summary=f"{len(violations)} layer boundary violation(s) in {files_scanned} files",
            details=violations,
        )
    return GateResult(
        name="layers",
        status="PASS",
        summary=f"0 violations across {files_scanned} architectural files",
    )


def scan_waivers(repo_root: Path) -> Tuple[GateResult, Dict[str, Dict[int, WaiverEntry]]]:
    roots = [
        repo_root / "components" / "h1os" / "include",
        repo_root / "components" / "h1os" / "src",
        repo_root / "examples",
    ]
    valid: Dict[str, Dict[int, WaiverEntry]] = {}
    errors: List[str] = []
    total_valid = 0

    for root in roots:
        if not root.is_dir():
            continue
        for fpath in sorted(root.rglob("*")):
            if not fpath.is_file() or fpath.suffix.lower() not in {".c", ".cpp", ".h"}:
                continue
            rel = _norm_rel(fpath, repo_root)
            if "/build" in f"/{rel}" or "/managed_components/" in f"/{rel}" or "/tools/fonts/" in f"/{rel}":
                continue
            lines = fpath.read_text(encoding="utf-8", errors="replace").splitlines()
            for lineno, line in enumerate(lines, 1):
                if "[H1OS-WAIVER" not in line:
                    continue
                m = WAIVER_RE.search(line)
                if not m:
                    errors.append(f"{rel}:{lineno}: Malformed [H1OS-WAIVER] annotation")
                    continue
                pitfall, sev, reason, proof = (
                    m.group(1).strip(),
                    m.group(2).strip(),
                    m.group(3).strip(),
                    m.group(4).strip(),
                )
                if sev == "S0":
                    errors.append(f"{rel}:{lineno}: Class S0 hazards cannot be waived ({pitfall})")
                    continue
                if not reason or not proof:
                    errors.append(f"{rel}:{lineno}: Waiver missing non-empty Reason or Proof ({pitfall})")
                    continue
                entry = WaiverEntry(rel, lineno, pitfall, sev, reason, proof)
                valid.setdefault(rel, {})[lineno] = entry
                total_valid += 1

    if errors:
        return (
            GateResult("waivers", "FAIL", f"{len(errors)} invalid waiver(s) ({total_valid} valid)", errors),
            valid,
        )
    return (
        GateResult("waivers", "PASS", f"{total_valid} valid waiver(s), 0 malformed/S0"),
        valid,
    )


def _find_semgrep() -> Optional[str]:
    direct = shutil.which("semgrep")
    if direct:
        return direct
    candidate = Path.home() / ".local" / "bin" / ("semgrep.exe" if os.name == "nt" else "semgrep")
    if candidate.is_file():
        return str(candidate)
    return None


def check_semgrep(
    repo_root: Path, waivers_by_file: Dict[str, Dict[int, WaiverEntry]]
) -> GateResult:
    sg_exe = _find_semgrep()
    if sg_exe is None:
        return GateResult("semgrep", "FAIL", "semgrep binary not found on PATH or ~/.local/bin")

    configs: List[str] = []
    for yml in (
        SEMGREP_PLUGIN_DIR / "esp32s3_embedded.yml",
        SEMGREP_PLUGIN_DIR / "python_build_tooling.yml",
        repo_root / "tools" / "audit" / "semgrep_h1os.yml",
    ):
        if yml.is_file():
            configs.extend(["--config", str(yml)])
    for pack in ("p/c", "p/python", "p/security-audit", "p/secrets"):
        configs.extend(["--config", pack])

    cmd = [sg_exe, "scan", *configs, "--json", "--quiet"]
    proc = subprocess.run(
        cmd,
        cwd=str(repo_root),
        env=_utf8_env(),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    if proc.returncode not in (0, 1) and not proc.stdout.strip():
        return GateResult(
            "semgrep",
            "FAIL",
            f"semgrep scan exited {proc.returncode}",
            [proc.stderr.strip()[:400]],
        )

    try:
        payload = json.loads(proc.stdout)
    except json.JSONDecodeError as exc:
        return GateResult("semgrep", "FAIL", f"Failed to parse semgrep JSON output: {exc}")

    results = payload.get("results", [])
    blocking: List[str] = []
    warnings: List[str] = []
    waived: List[str] = []

    for r in results:
        raw_path = str(r.get("path", "")).replace("\\", "/")
        line = int(r.get("start", {}).get("line", 0))
        check_id = str(r.get("check_id", "unknown"))
        severity = str(r.get("extra", {}).get("severity", "WARNING")).upper()
        file_waivers = waivers_by_file.get(raw_path, {})
        matched_waiver: Optional[WaiverEntry] = None
        for w_line, w_entry in file_waivers.items():
            if line - 3 <= w_line <= line:
                matched_waiver = w_entry
                break

        if matched_waiver is not None:
            waived.append(
                f"{raw_path}:{line} [{check_id}] waived by {matched_waiver.pitfall} ({matched_waiver.severity})"
            )
        elif severity == "ERROR":
            blocking.append(f"{raw_path}:{line} [ERROR] {check_id}")
        else:
            warnings.append(f"{raw_path}:{line} [{severity}] {check_id}")

    if blocking:
        return GateResult(
            "semgrep",
            "FAIL",
            f"{len(blocking)} blocking ERROR(s), {len(warnings)} warning(s), {len(waived)} waived",
            blocking + warnings + waived,
        )
    return GateResult(
        "semgrep",
        "PASS",
        f"0 blocking ERRORs, {len(warnings)} advisory warning(s), {len(waived)} waived",
        warnings + waived,
    )


def _find_tool_recursive(root: Path, filename: str) -> Optional[Path]:
    if not root.is_dir():
        return None
    matches = sorted(root.rglob(filename))
    return matches[0] if matches else None


def _is_target_tu(file_path: str) -> bool:
    norm = file_path.replace("\\", "/")
    return (
        "/components/h1os/src/" in norm
        or "/examples/H1OS/main/" in norm
        or "/examples/boilerplate/main/" in norm
    )


def _expand_rsp_tokens(cmd: str) -> List[str]:
    toks = shlex.split(cmd.replace("\\", "/"), posix=True)
    out: List[str] = []
    for t in toks:
        if t.startswith("@"):
            p = Path(t[1:])
            if p.is_file():
                out.extend(shlex.split(p.read_text(encoding="utf-8").replace("\\", "/"), posix=True))
        else:
            out.append(t)
    return out


def check_clang_tidy(repo_root: Path, build_dir: Path) -> GateResult:
    ct_path = _find_tool_recursive(ESP_CLANG_ROOT, "clang-tidy.exe")
    if ct_path is None:
        direct = shutil.which("clang-tidy")
        ct_path = Path(direct) if direct else None
    if ct_path is None or not ct_path.is_file():
        return GateResult("clang-tidy", "FAIL", "esp-clang clang-tidy.exe not found")

    cc_src_path = build_dir / "compile_commands.json"
    if not cc_src_path.is_file():
        return GateResult("clang-tidy", "FAIL", f"Missing {cc_src_path}")

    pico_stdlib = _find_tool_recursive(XTENSA_GCC_ROOT, "picolibc/include/stdlib.h")
    cpp_cstdlib = _find_tool_recursive(XTENSA_GCC_ROOT, "cstdlib")
    if pico_stdlib is None:
        return GateResult("clang-tidy", "FAIL", "Could not locate xtensa picolibc/include/stdlib.h")
    pico_inc = pico_stdlib.parent.as_posix()
    cpp_inc = cpp_cstdlib.parent.as_posix() if cpp_cstdlib else ""

    raw_entries = json.loads(cc_src_path.read_text(encoding="utf-8"))
    targets = [e for e in raw_entries if _is_target_tu(e.get("file", ""))]

    drop_exact = {
        "-mlongcalls",
        "-fstrict-volatile-bitfields",
        "-fno-tree-switch-conversion",
        "-fno-jump-tables",
        "-fno-shrink-wrap",
        "-fuse-cxa-atexit",
        "-fno-malloc-dce",
        "-mdisable-hardware-atomics",
        "-Wno-old-style-declaration",
    }
    drop_prefixes = (
        "-specs=",
        "-fzero-init-padding-bits",
        "-fstack-usage",
        "-Wduplicated-",
        "-Wlogical-op",
        "-fmacro-prefix-map",
    )

    sanitized_entries: List[Dict[str, str]] = []
    for e in targets:
        toks = _expand_rsp_tokens(e["command"])
        res: List[str] = []
        is_cpp = False
        for i, t in enumerate(toks):
            if i == 0:
                is_cpp = t.endswith(("g++.exe", "g++", "clang++.exe", "clang++"))
                res.append("clang++" if is_cpp else "clang")
                res.extend(["--target=xtensa-esp-elf", "-mcpu=esp32s3", "-isystem", pico_inc])
                if is_cpp and cpp_inc:
                    res.extend(["-isystem", cpp_inc, "-isystem", f"{cpp_inc}/xtensa-esp-elf"])
                continue
            if t in drop_exact or any(t.startswith(p) for p in drop_prefixes):
                continue
            if t == "-std=gnu++26":
                res.append("-std=gnu++23")
                continue
            res.append(t)
        sanitized_entries.append(
            {
                "directory": e["directory"].replace("\\", "/"),
                "file": e["file"].replace("\\", "/"),
                "command": subprocess.list2cmdline(res),
            }
        )

    errors: List[str] = []
    warnings: List[str] = []

    with tempfile.TemporaryDirectory() as td:
        cc_dir = Path(td)
        (cc_dir / "compile_commands.json").write_text(
            json.dumps(sanitized_entries, indent=2), encoding="utf-8"
        )

        def _run_one(entry: Dict[str, str]) -> Tuple[int, str]:
            proc = subprocess.run(
                [str(ct_path), "-p", str(cc_dir), "--quiet", entry["file"]],
                cwd=str(repo_root),
                capture_output=True,
                text=True,
                encoding="utf-8",
                errors="replace",
                check=False,
            )
            return proc.returncode, (proc.stdout + "\n" + proc.stderr)

        with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
            for rc, output in pool.map(_run_one, sanitized_entries):
                for line in output.splitlines():
                    s = line.strip()
                    if not s:
                        continue
                    if ": error:" in s or "clang-diagnostic-error" in s:
                        errors.append(s)
                    elif ": warning:" in s and ("components/h1os/" in s or "/examples/" in s):
                        warnings.append(s)
                if rc != 0 and not any(": error:" in ln or "clang-diagnostic-error" in ln for ln in output.splitlines()):
                    errors.append(f"clang-tidy exited {rc}: {output.strip()[:200]}")

    if errors:
        return GateResult(
            "clang-tidy",
            "FAIL",
            f"{len(errors)} error(s), {len(warnings)} warning(s) across {len(sanitized_entries)} TUs",
            errors[:15] + warnings[:10],
        )
    return GateResult(
        "clang-tidy",
        "PASS",
        f"0 errors, {len(warnings)} advisory warning(s) across {len(sanitized_entries)} TUs",
        warnings[:15],
    )


def _classify_misra_rule(rule_id: str) -> str:
    num = rule_id.replace("misra-c2012-", "").replace("misra-config", "").strip()
    if num in MISRA_MANDATORY_RULES:
        return "Mandatory"
    if num in MISRA_ADVISORY_RULES:
        return "Advisory"
    return "Required"


def run_cppcheck_and_misra(
    repo_root: Path, build_dir: Path, run_misra: bool
) -> Tuple[GateResult, Optional[GateResult]]:
    cpp_exe = Path(shutil.which("cppcheck") or DEFAULT_CPPCHECK_EXE)
    if not cpp_exe.is_file():
        fail = GateResult("cppcheck", "FAIL", f"cppcheck binary not found ({cpp_exe})")
        return fail, (GateResult("misra", "FAIL", fail.summary) if run_misra else None)

    cc_src_path = build_dir / "compile_commands.json"
    if not cc_src_path.is_file():
        fail = GateResult("cppcheck", "FAIL", f"Missing {cc_src_path}")
        return fail, (GateResult("misra", "FAIL", fail.summary) if run_misra else None)

    raw_entries = json.loads(cc_src_path.read_text(encoding="utf-8"))
    targets = [e for e in raw_entries if _is_target_tu(e.get("file", ""))]

    drop_prefixes = (
        "-specs=",
        "-fzero-init-padding-bits",
        "-mlongcalls",
        "-fstrict-volatile-bitfields",
        "-fno-tree-switch-conversion",
        "-fno-jump-tables",
        "-fno-shrink-wrap",
        "-fuse-cxa-atexit",
        "-fdiagnostics-color",
        "-gdwarf",
        "-ggdb",
        "-fmacro-prefix-map",
        "-fstack-usage",
        "-W",
    )

    entries: List[Dict[str, str]] = []
    for e in targets:
        toks = _expand_rsp_tokens(e["command"])
        cleaned: List[str] = []
        i = 0
        while i < len(toks):
            t = toks[i]
            if t == "-isystem" and i + 1 < len(toks):
                cleaned.append("-I" + toks[i + 1])
                i += 2
                continue
            if not any(t.startswith(p) for p in drop_prefixes):
                cleaned.append(t)
            i += 1
        cleaned.insert(1, "-Dasm(x)=")
        f_rel = _norm_rel(Path(e["file"]), repo_root)
        entries.append(
            {
                "directory": repo_root.resolve().as_posix(),
                "file": f_rel,
                "command": subprocess.list2cmdline(cleaned),
            }
        )

    jobs = str(min(os.cpu_count() or 4, 8))
    with tempfile.TemporaryDirectory() as td:
        td_path = Path(td)
        cc_out = td_path / "compile_commands.json"
        cc_out.write_text(json.dumps(entries, indent=2), encoding="utf-8")
        cpp_bdir = td_path / "cppcheck_build"
        cpp_bdir.mkdir()

        cmd = [
            str(cpp_exe),
            f"--project={cc_out}",
            f"--cppcheck-build-dir={cpp_bdir}",
            "-j",
            jobs,
            "--enable=warning,style,performance,portability",
            "--inline-suppr",
            f"--suppressions-list={repo_root / 'tools' / 'audit' / 'cppcheck_suppressions.txt'}",
            "--suppress=*:*esp-idf*",
            "--suppress=*:*managed_components*",
            "--suppress=*:*tools/fonts*",
            "--addon=threadsafety",
        ]
        if run_misra:
            cmd.append("--addon=misra")
        cmd.extend(["--quiet", "--template={file}:{line}: [{severity}] {id}: {message}"])

        proc = subprocess.run(
            cmd,
            cwd=str(repo_root),
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            check=False,
        )

    all_lines = [ln.strip() for ln in (proc.stdout + "\n" + proc.stderr).splitlines() if ln.strip()]
    repo_key = repo_root.name.lower()
    h1os_lines = [
        ln
        for ln in all_lines
        if (
            "components/h1os/" in ln.replace("\\", "/")
            or "examples/" in ln.replace("\\", "/")
            or repo_key in ln.lower()
        )
        and "managed_components" not in ln
        and "tools\\fonts" not in ln
        and "tools/fonts" not in ln
    ]

    non_misra_blocking: List[str] = []
    non_misra_obs: List[str] = []
    misra_lines: List[str] = []

    for ln in h1os_lines:
        if "misra-" in ln:
            misra_lines.append(ln)
            continue
        if ": [error] " in ln or ": [warning] " in ln:
            non_misra_blocking.append(ln)
        else:
            non_misra_obs.append(ln)

    if proc.returncode != 0 and not non_misra_blocking:
        non_misra_blocking.append(f"cppcheck exited with code {proc.returncode}")

    if non_misra_blocking:
        cpp_res = GateResult(
            "cppcheck",
            "FAIL",
            f"{len(non_misra_blocking)} blocking error/warning(s), {len(non_misra_obs)} style note(s)",
            non_misra_blocking + non_misra_obs[:10],
        )
    else:
        cpp_res = GateResult(
            "cppcheck",
            "PASS",
            f"0 blocking error/warning(s), {len(non_misra_obs)} observational style note(s) ({len(entries)} TUs)",
            non_misra_obs[:12],
        )

    if not run_misra:
        return cpp_res, None

    cat_counts: collections.Counter[str] = collections.Counter()
    rule_counts: collections.Counter[str] = collections.Counter()
    mandatory_locs: List[str] = []

    for ln in misra_lines:
        m = re.search(r"\b(misra-c2012-[\d.]+|misra-config)\b", ln)
        rule_id = m.group(1) if m else "misra-other"
        rule_counts[rule_id] += 1
        cat = _classify_misra_rule(rule_id)
        cat_counts[cat] += 1
        if cat == "Mandatory" and len(mandatory_locs) < 10:
            mandatory_locs.append(ln)

    misra_details = [f"top {rule}: {cnt}" for rule, cnt in rule_counts.most_common(15)]
    if mandatory_locs:
        misra_details.extend([f"Mandatory sample: {loc}" for loc in mandatory_locs])

    misra_res = GateResult(
        "misra",
        "PASS",
        (
            f"Observational total={len(misra_lines)} "
            f"(Mandatory={cat_counts['Mandatory']}, "
            f"Required={cat_counts['Required']}, "
            f"Advisory={cat_counts['Advisory']})"
        ),
        misra_details,
    )
    return cpp_res, misra_res


def check_python_qa(repo_root: Path) -> GateResult:
    uvx = shutil.which("uvx")
    if not uvx:
        return GateResult("python", "FAIL", "uvx executable not found on PATH")

    targets = ["components/h1os/idf_ext.py", "components/h1os/tools", "tools/agent"]
    if (repo_root / "tests" / "tools").is_dir():
        targets.append("tests/tools")

    details: List[str] = []
    failed = False

    ruff_proc = subprocess.run(
        [uvx, "ruff", "check", "--output-format=concise", *targets],
        cwd=str(repo_root),
        env=_utf8_env(),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    if ruff_proc.returncode != 0:
        failed = True
        details.extend([ln for ln in (ruff_proc.stdout + "\n" + ruff_proc.stderr).splitlines() if ln.strip()][:20])

    mypy_proc = subprocess.run(
        [uvx, "mypy", *targets, "--exclude", "components/h1os/tools/fonts"],
        cwd=str(repo_root),
        env=_utf8_env(),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    if mypy_proc.returncode != 0:
        failed = True
        details.extend([ln for ln in (mypy_proc.stdout + "\n" + mypy_proc.stderr).splitlines() if ln.strip()][:20])

    flasher_ps1 = (repo_root / "components" / "h1os" / "tools" / "pack_build" / "flasher.ps1").resolve()
    ps_escaped = str(flasher_ps1).replace("'", "''")
    ps_script = (
        "$e=$null; [System.Management.Automation.Language.Parser]::ParseFile("
        f"'{ps_escaped}', [ref]$null, [ref]$e) > $null; "
        "if ($e) { foreach ($x in $e) { Write-Error $x }; exit 1 }"
    )
    ps_proc = subprocess.run(
        ["powershell", "-NoProfile", "-Command", ps_script],
        cwd=str(repo_root),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    if ps_proc.returncode != 0:
        failed = True
        details.append(f"flasher.ps1 AST check failed: {ps_proc.stderr.strip()}")

    if failed:
        return GateResult("python", "FAIL", "ruff, mypy, or flasher.ps1 AST check failed", details)
    return GateResult(
        "python",
        "PASS",
        "ruff=0 errors, mypy=0 issues, flasher.ps1 AST=0 parse errors",
    )


def check_stack_budget(build_dir: Path, stack_limit: int) -> GateResult:
    if not build_dir.is_dir():
        return GateResult("stack", "FAIL", f"Build directory not found: {build_dir}")

    su_files = sorted(build_dir.rglob("*.su"))
    if not su_files:
        return GateResult("stack", "FAIL", f"No .su stack-usage files found under {build_dir}")

    project_su: List[Path] = []
    for p in su_files:
        norm = p.as_posix()
        if "/esp-idf/h1os/" in norm or "/esp-idf/main/" in norm:
            project_su.append(p)
    scan_files = project_su if project_su else su_files

    max_bytes = 0
    max_entry = ""
    func_count = 0
    dynamic_frames: List[str] = []
    over_limit: List[str] = []

    for su in scan_files:
        for line in su.read_text(encoding="utf-8", errors="replace").splitlines():
            m = STACK_LINE_RE.match(line.strip())
            if not m:
                continue
            src, ln_no, func, bytes_s, kind = m.groups()
            b = int(bytes_s)
            func_count += 1
            if "dynamic" in kind:
                dynamic_frames.append(f"{Path(src).name}:{ln_no} {func} ({b} B, {kind})")
            if b > stack_limit:
                over_limit.append(f"{Path(src).name}:{ln_no} {func} ({b} B > {stack_limit} B)")
            if b > max_bytes:
                max_bytes = b
                max_entry = f"{Path(src).name}:{func}"

    if dynamic_frames or over_limit:
        return GateResult(
            "stack",
            "FAIL",
            f"max={max_bytes} B ({max_entry}), dynamic={len(dynamic_frames)}, over={len(over_limit)}",
            dynamic_frames + over_limit,
        )
    return GateResult(
        "stack",
        "PASS",
        f"{func_count} H1OS functions across {len(scan_files)} .su files, max={max_bytes} B ({max_entry}), dynamic=0",
    )


def check_rtc_sections(build_dir: Path) -> GateResult:
    elf = build_dir / "h1os.elf"
    if not elf.is_file():
        return GateResult("rtc-sections", "FAIL", f"Missing ELF: {elf}")

    objdump = _find_tool_recursive(XTENSA_GCC_ROOT, "xtensa-esp32s3-elf-objdump.exe")
    if objdump is None:
        return GateResult("rtc-sections", "FAIL", "Xtensa objdump tool not found")

    hdr_proc = subprocess.run(
        [str(objdump), "-h", str(elf)],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    od_proc = subprocess.run(
        [str(objdump), "-d", "-j", ".rtc.text", str(elf)],
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    if hdr_proc.returncode != 0 or od_proc.returncode != 0:
        return GateResult("rtc-sections", "FAIL", "objdump execution failed")

    sections: List[Tuple[str, int, int]] = []
    for line in hdr_proc.stdout.splitlines():
        hm = re.match(r"^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+", line)
        if hm:
            sec_name = hm.group(1)
            sec_size = int(hm.group(2), 16)
            sec_vma = int(hm.group(3), 16)
            if sec_size > 0:
                sections.append((sec_name, sec_vma, sec_vma + sec_size))

    def _classify(addr: int) -> str:
        if 0x40000000 <= addr < 0x40060000:
            return "ESP32S3_ROM"
        for s_name, s_start, s_end in sections:
            if s_start <= addr < s_end:
                return s_name
        return "UNKNOWN"

    unsafe_sections = {
        ".flash.text",
        ".flash.rodata",
        ".flash.tdata",
        ".flash.appdesc",
        ".iram0.text",
        ".dram0.data",
        ".dram0.bss",
    }

    lit_ranges: List[Tuple[int, int]] = []
    l32r_full_re = re.compile(
        r"^\s*([0-9a-fA-F]+):\s+[0-9a-fA-F ]+\s+l32r\s+\S+,\s+([0-9a-fA-F]+)"
        r"\s+<[^>]+>(?:\s+\(([0-9a-fA-F]+)\s+<([^>]+)>\))?"
    )
    branch_re = re.compile(
        r"^\s*([0-9a-fA-F]+):\s+[0-9a-fA-F ]+\s+(call0|call4|call8|call12|j)\s+"
        r"([0-9a-fA-F]+)\s+<([^>]+)>"
    )

    rtc_syms: Set[str] = set()
    seen_edges: Set[Tuple[str, str, str]] = set()
    violations: List[str] = []
    verified_calls = 0
    cur_func = "<unknown>"
    dis_lines = od_proc.stdout.splitlines()

    for line in dis_lines:
        sm = SU_OBJDUMP_SYM_RE.match(line.strip())
        if sm:
            cur_func = sm.group(2)
            rtc_syms.add(cur_func)
            continue
        lm = l32r_full_re.match(line)
        if lm:
            lit_addr = int(lm.group(2), 16)
            lit_ranges.append((lit_addr, lit_addr + 4))
            if lm.group(3):
                val_addr = int(lm.group(3), 16)
                val_sec = _classify(val_addr)
                if val_sec in unsafe_sections:
                    tgt_label = lm.group(4) or f"0x{val_addr:08x}"
                    edge = (cur_func, f"l32r:{tgt_label}", val_sec)
                    if edge not in seen_edges:
                        seen_edges.add(edge)
                        violations.append(
                            f"{cur_func}: l32r literal references {val_sec} ({tgt_label} @ 0x{val_addr:08x})"
                        )

    cur_func = "<unknown>"
    for line in dis_lines:
        sm = SU_OBJDUMP_SYM_RE.match(line.strip())
        if sm:
            cur_func = sm.group(2)
            continue
        bm = branch_re.match(line)
        if not bm:
            continue
        insn_addr = int(bm.group(1), 16)
        if any(start <= insn_addr < end for start, end in lit_ranges):
            continue
        tgt_addr = int(bm.group(3), 16)
        tgt_sym = bm.group(4).split("+")[0]
        tgt_sec = _classify(tgt_addr)
        edge = (cur_func, tgt_sym, tgt_sec)
        if edge in seen_edges:
            continue
        seen_edges.add(edge)
        if tgt_sec == "ESP32S3_ROM" or tgt_sec.startswith(".rtc"):
            verified_calls += 1
        elif tgt_sec in unsafe_sections:
            violations.append(
                f"{cur_func}: non-RTC branch/call to {tgt_sym} in {tgt_sec} (0x{tgt_addr:08x})"
            )

    if violations:
        return GateResult("rtc-sections", "FAIL", f"{len(violations)} RTC wake-stub violation(s)", violations)
    return GateResult(
        "rtc-sections",
        "PASS",
        f"0 Flash/DRAM leaks across {len(rtc_syms)} RTC symbols and {verified_calls} RTC/ROM calls",
    )


def _build_lexicon_patterns() -> List[Tuple[str, re.Pattern[str]]]:
    specs = [
        ("stand-down", r"\b" + "stand" + r"[- ]down\b"),
        ("sentinel", r"\b" + "sen" + r"tinel\b"),
        ("sentry", r"\b" + "sen" + r"try\b"),
        ("bouncer", r"\b" + "boun" + r"cer\b"),
        ("tripwire", r"\b" + "trip" + r"wire\b"),
        ("sortie", r"\b" + "sor" + r"tie\b"),
        ("reconnaissance", r"\b" + "recon" + r"naissance\b"),
        ("scaffold purge", r"\b" + "scaffold" + r"\s+purge\b"),
        ("neutralize", r"\b" + "neutral" + r"iz(?:e|ed|ing)\b"),
        ("doctrine", r"\b" + "doc" + r"trine\b"),
        ("dogma", r"\b" + "dog" + r"ma\b"),
        ("cadence", r"\b" + "ca" + r"dence\b"),
        ("nuke", r"\b" + "nu" + r"ke\b"),
        ("pixie dust", r"\b" + "pixie" + r"\s+dust\b"),
        ("fallback/fall back", r"\b(?:" + "fall" + r"back|" + "fall" + r"\s+back)\b"),
    ]
    return [(label, re.compile(pat, re.IGNORECASE)) for label, pat in specs]


def check_lexicon(repo_root: Path) -> GateResult:
    excluded_exact = {
        "AGENTS.md",
        ".agents/rules/lexicon.md",
        "docs/architecture/D0_std_audit_framework.md",
        "docs/architecture/C4_changelog_policy.md",
        ".agents/rules/docs.md",
        "tools/agent/run_audit.py",
        "docs/api.md",
        "CHANGELOG.md",
    }
    excluded_prefixes = (
        "tests/",
        "components/h1os/tools/fonts/",
        "docs/hardware_docs/",
        "docs/logs/",
        "examples/riscv_test/docs/",
        "build/",
        "managed_components/",
    )
    allowed_exts = {".c", ".cpp", ".h", ".py", ".md", ".yml", ".yaml"}
    patterns = _build_lexicon_patterns()

    proc = subprocess.run(
        ["git", "ls-files"],
        cwd=str(repo_root),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    files = (
        proc.stdout.splitlines()
        if proc.returncode == 0
        else [_norm_rel(p, repo_root) for p in repo_root.rglob("*") if p.is_file()]
    )

    hits: List[str] = []
    scanned = 0
    for rel in sorted(files):
        rel = rel.replace("\\", "/")
        if rel in excluded_exact or any(rel.startswith(px) for px in excluded_prefixes):
            continue
        p = repo_root / rel
        if not p.is_file() or p.suffix.lower() not in allowed_exts:
            continue
        scanned += 1
        lines = p.read_text(encoding="utf-8", errors="replace").splitlines()
        for lineno, line in enumerate(lines, 1):
            for label, rx in patterns:
                if not rx.search(line):
                    continue
                if label.startswith("fallback"):
                    if any(
                        ok in line
                        for ok in (
                            "lv_font_t.fallback",
                            "->fallback",
                            ".fallback",
                            ".scheme.json",
                            '"fallback"',
                            "ConfigParser",
                            "fallback=",
                            "SUB_POWER_VBAT_NOMINAL_FALLBACK_MV",
                        )
                    ):
                        continue
                hits.append(f"{rel}:{lineno} [{label}]: {line.strip()[:100]}")

    if hits:
        return GateResult("lexicon", "FAIL", f"{len(hits)} prohibited jargon hit(s) in {scanned} files", hits)
    return GateResult("lexicon", "PASS", f"0 prohibited jargon hits across {scanned} tracked files")


def _load_font_metrics(metrics_dir: Path, font_name: str) -> Optional[Tuple[Dict[int, int], Dict[Tuple[int, int], int]]]:
    cw_path = metrics_dir / f"char_widths_{font_name}.csv"
    kp_path = metrics_dir / f"kern_pairs_{font_name}.csv"
    if not cw_path.is_file():
        return None
    widths: Dict[int, int] = {}
    with cw_path.open("r", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            widths[int(row["unicode_dec"])] = int(row["adv_w_raw"])
    kerns: Dict[Tuple[int, int], int] = {}
    if kp_path.is_file():
        with kp_path.open("r", encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                kerns[(int(row["left_code"]), int(row["right_code"]))] = int(row["kern_raw_16th"])
    return widths, kerns


def _measure_string_px(
    text: str, widths: Dict[int, int], kerns: Dict[Tuple[int, int], int]
) -> float:
    decoded = text.replace("\\n", "\n").replace('\\"', '"').split("\n")[0]
    if not decoded:
        return 0.0
    total_fp4 = 0
    prev_cp: Optional[int] = None
    default_adv = widths.get(32, 64)
    for ch in decoded:
        cp = ord(ch)
        adv = widths.get(cp, default_adv)
        kern = kerns.get((prev_cp, cp), 0) if prev_cp is not None else 0
        total_fp4 += adv + kern
        prev_cp = cp
    return total_fp4 / 16.0


def check_typography(repo_root: Path) -> GateResult:
    fonts_root = repo_root / "components" / "h1os" / "tools" / "fonts"
    metrics_dir = fonts_root / "metrics"
    scheme_path = fonts_root / "schemes" / "h1os_full.scheme.json"
    if not scheme_path.is_file() or not metrics_dir.is_dir():
        return GateResult("typography", "FAIL", "Missing epd-font scheme or metrics directory")

    scheme = json.loads(scheme_path.read_text(encoding="utf-8"))
    roles: Dict[str, str] = scheme.get("output_branding", {}).get("semantic_roles", {})
    roles["LV_FONT_DEFAULT"] = "humid1_font_plex_sans_normal_14"

    cache: Dict[str, Tuple[Dict[int, int], Dict[Tuple[int, int], int]]] = {}
    ui_roots = [repo_root / "examples" / "H1OS" / "main" / "screens", repo_root / "examples" / "boilerplate" / "main"]
    violations: List[str] = []
    strings_checked = 0
    max_width_px = 0.0
    max_info = ""

    for ui_dir in ui_roots:
        if not ui_dir.is_dir():
            continue
        for c_file in sorted(ui_dir.rglob("*.c")):
            rel = _norm_rel(c_file, repo_root)
            lines = c_file.read_text(encoding="utf-8", errors="replace").splitlines()
            for lineno, line in enumerate(lines, 1):
                if re.search(r"humid1_font_[a-z0-9_]+_12\b|H1OS_FONT_(?:BOLD_|MONO_)?12\b", line):
                    violations.append(f"{rel}:{lineno}: Sub-14px font reference prohibited on SSD1681: {line.strip()}")
                m = LABEL_TEXT_RE.search(line)
                if not m:
                    continue
                literal = m.group(1)
                if "%" in literal:
                    continue
                font_name = "humid1_font_plex_sans_normal_14"
                window = "\n".join(lines[max(0, lineno - 3) : min(len(lines), lineno + 3)])
                fm = SET_FONT_RE.search(window)
                if fm:
                    tok = fm.group(1).lstrip("&")
                    font_name = roles.get(tok, tok)
                if font_name not in cache:
                    loaded = _load_font_metrics(metrics_dir, font_name)
                    if loaded is None:
                        continue
                    cache[font_name] = loaded
                widths, kerns = cache[font_name]
                w_px = _measure_string_px(literal, widths, kerns)
                strings_checked += 1
                if w_px > max_width_px:
                    max_width_px = w_px
                    max_info = f"{rel}:{lineno} '{literal}' ({font_name})"
                if w_px > 188.0:
                    violations.append(
                        f"{rel}:{lineno}: Static string '{literal}' = {w_px:.1f} px > 188.0 px ({font_name})"
                    )

    if violations:
        return GateResult("typography", "FAIL", f"{len(violations)} typography violation(s)", violations)
    return GateResult(
        "typography",
        "PASS",
        f"{strings_checked} static UI strings checked, max={max_width_px:.1f} px <= 188.0 px ({max_info})",
    )


def _run_subprocess_gate(
    repo_root: Path, name: str, cmd: Sequence[str], ok_msg: str
) -> GateResult:
    proc = subprocess.run(
        list(cmd),
        cwd=str(repo_root),
        env=_utf8_env(),
        capture_output=True,
        text=True,
        encoding="utf-8",
        errors="replace",
        check=False,
    )
    lines = [ln.strip() for ln in (proc.stdout + "\n" + proc.stderr).splitlines() if ln.strip()]
    if proc.returncode != 0:
        return GateResult(name, "FAIL", f"Exited {proc.returncode}: {lines[-1] if lines else ''}", lines[-20:])
    return GateResult(name, "PASS", lines[-1] if lines else ok_msg)


def _write_reports(
    results: Sequence[GateResult],
    md_out: Optional[Path],
    json_out: Optional[Path],
) -> None:
    if json_out is not None:
        json_out.parent.mkdir(parents=True, exist_ok=True)
        payload = {
            "generated_utc": dt.datetime.now(dt.UTC).isoformat(),
            "gates": [asdict(r) for r in results],
        }
        json_out.write_text(json.dumps(payload, indent=2), encoding="utf-8")

    if md_out is not None:
        md_out.parent.mkdir(parents=True, exist_ok=True)
        rows = [
            f"| `{r.name}` | **{r.status}** | {r.summary} |"
            for r in results
        ]
        md = [
            "# H1OS Audit Summary (`H1OS-STD-001 Rev 2.2`)",
            "",
            "| Gate | Status | Summary |",
            "| :--- | :--- | :--- |",
            *rows,
            "",
        ]
        md_out.write_text("\n".join(md), encoding="utf-8")


def parse_args(argv: Optional[Sequence[str]] = None) -> argparse.Namespace:
    p = argparse.ArgumentParser(description="H1OS Safety & Architecture Audit Harness Runner")
    p.add_argument("--all", action="store_true", help="Run all audit gates")
    p.add_argument("--layers", action="store_true", help="Check 4-layer unidirectional include hierarchy")
    p.add_argument("--waivers", action="store_true", help="Validate [H1OS-WAIVER] annotations")
    p.add_argument("--semgrep", action="store_true", help="Run custom & curated Semgrep scans")
    p.add_argument("--clang-tidy", action="store_true", help="Run read-only esp-clang clang-tidy on compile_commands")
    p.add_argument("--cppcheck", action="store_true", help="Run Cppcheck static & threadsafety analysis")
    p.add_argument("--misra", action="store_true", help="Include observational Cppcheck MISRA C:2012 summary")
    p.add_argument("--python", action="store_true", help="Run ruff, mypy, and flasher.ps1 AST checks")
    p.add_argument("--stack", action="store_true", help="Check .su static frame limits")
    p.add_argument("--rtc-sections", action="store_true", help="Audit .rtc.text wake stub ELF sections & calls")
    p.add_argument("--lexicon", action="store_true", help="Check AGENTS.md section 2 engineering nomenclature")
    p.add_argument("--typography", action="store_true", help="Validate LVGL static label widths <= 188 px & >= 14 px")
    p.add_argument("--version", action="store_true", help="Run bump_version.py --check --idf-version 6.1.1")
    p.add_argument("--sanitize", action="store_true", help="Run sanitize.py --check --include-dist")
    p.add_argument("--tests", action="store_true", help="Run pytest tools & firmware host C11 regression suites")
    p.add_argument("--build-dir", default="examples/H1OS/build_dev", help="ESP-IDF build directory")
    p.add_argument("--stack-limit", type=int, default=1024, help="Max per-function stack frame in bytes")
    p.add_argument("--markdown-out", default=None, help="Optional Markdown report output path")
    p.add_argument("--json-out", default=None, help="Optional JSON report output path")
    return p.parse_args(argv)


def main(argv: Optional[Sequence[str]] = None) -> int:
    args = parse_args(argv)
    gate_flags = (
        args.layers,
        args.waivers,
        args.semgrep,
        args.clang_tidy,
        args.cppcheck,
        args.misra,
        args.python,
        args.stack,
        args.rtc_sections,
        args.lexicon,
        args.typography,
        args.version,
        args.sanitize,
        args.tests,
    )
    run_all = args.all or not any(gate_flags)

    repo_root = find_repo_root()
    build_dir = Path(args.build_dir)
    if not build_dir.is_absolute():
        build_dir = repo_root / build_dir

    results: List[GateResult] = []
    waivers_by_file: Dict[str, Dict[int, WaiverEntry]] = {}

    if run_all or args.layers:
        results.append(check_layers(repo_root))

    if run_all or args.waivers or args.semgrep:
        waiver_res, waivers_by_file = scan_waivers(repo_root)
        if run_all or args.waivers:
            results.append(waiver_res)

    if run_all or args.semgrep:
        results.append(check_semgrep(repo_root, waivers_by_file))

    if run_all or args.clang_tidy:
        results.append(check_clang_tidy(repo_root, build_dir))

    if run_all or args.cppcheck or args.misra:
        want_misra = bool(run_all or args.misra)
        cpp_res, misra_res = run_cppcheck_and_misra(repo_root, build_dir, want_misra)
        if run_all or args.cppcheck:
            results.append(cpp_res)
        if misra_res is not None:
            results.append(misra_res)

    if run_all or args.python:
        results.append(check_python_qa(repo_root))

    if run_all or args.stack:
        results.append(check_stack_budget(build_dir, args.stack_limit))

    if run_all or args.rtc_sections:
        results.append(check_rtc_sections(build_dir))

    if run_all or args.lexicon:
        results.append(check_lexicon(repo_root))

    if run_all or args.typography:
        results.append(check_typography(repo_root))

    if run_all or args.version:
        results.append(
            _run_subprocess_gate(
                repo_root,
                "version",
                [sys.executable, "tools/agent/bump_version.py", "--check", "--idf-version", "6.1.1"],
                "Version strings synchronized",
            )
        )

    if run_all or args.sanitize:
        results.append(
            _run_subprocess_gate(
                repo_root,
                "sanitize",
                [sys.executable, "tools/agent/sanitize.py", "--check", "--include-dist"],
                "Zero personal identity leaks",
            )
        )

    if run_all or args.tests:
        uvx = shutil.which("uvx")
        if not uvx:
            results.append(GateResult("tests", "FAIL", "uvx not found on PATH"))
        else:
            results.append(
                _run_subprocess_gate(
                    repo_root,
                    "tests",
                    [uvx, "--with", "pytest", "--with", "pillow", "--with", "pypdf", "pytest", "tests/tools", "-q"],
                    "All pytest suites passed",
                )
            )

    _write_reports(
        results,
        Path(args.markdown_out) if args.markdown_out else None,
        Path(args.json_out) if args.json_out else None,
    )

    print("\nH1OS Audit Harness Summary:")
    print("-" * 78)
    failures = 0
    for r in results:
        print(f"[{r.status:4s}] {r.name:<13s} | {r.summary}")
        if r.status == "FAIL":
            failures += 1
        for d in r.details[:10]:
            print(f"       -> {d}")
    print("-" * 78)
    print(f"Completed {len(results)} gate(s): {len(results) - failures} PASS, {failures} FAIL")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
