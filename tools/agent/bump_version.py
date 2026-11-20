#!/usr/bin/env python3
"""
H1OS Canonical Semantic Version & Specification Header Synchronizer
===================================================================
Atomically updates and audits H1OS semantic version strings across firmware
headers, ESP-IDF component metadata, developer tooling, README/ERRATA/AGENTS,
agent rules/skills, Doxyfile, docs/guide.md, and all docs/architecture/*.md
standardized headers, while checking CHANGELOG.md synchronization.

Usage:
  python tools/agent/bump_version.py --check
  python tools/agent/bump_version.py --set 2.4.10-dev --idf-version 6.1.1
  python tools/agent/bump_version.py --bump patch --dry-run
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, List, Optional, Tuple


SEMVER_RE = re.compile(r"^v?(\d+)\.(\d+)\.(\d+)(?:-([0-9A-Za-z.-]+))?$")
IDF_VER_RE = re.compile(r"^v?(\d+\.\d+(?:\.\d+)?(?:-[0-9A-Za-z.-]+)?)$")


@dataclass(frozen=True)
class SemVer:
    major: int
    minor: int
    patch: int
    tag: str = ""

    @property
    def version_string(self) -> str:
        base = f"{self.major}.{self.minor}.{self.patch}"
        return f"{base}-{self.tag}" if self.tag else base

    @property
    def shields_badge_token(self) -> str:
        if self.tag:
            return f"v{self.major}.{self.minor}.{self.patch}--{self.tag}"
        return f"v{self.major}.{self.minor}.{self.patch}"


@dataclass(frozen=True)
class FieldRule:
    label: str
    pattern: re.Pattern[str]
    render: Callable[[SemVer, Optional[str], re.Match[str]], str]
    extract: Callable[[re.Match[str]], str]
    expected_val: Callable[[SemVer, Optional[str]], str]


def parse_semver(raw: str) -> SemVer:
    m = SEMVER_RE.match(raw.strip())
    if not m:
        raise ValueError(f"Invalid semantic version '{raw}'. Expected X.Y.Z or X.Y.Z-tag.")
    return SemVer(
        major=int(m.group(1)),
        minor=int(m.group(2)),
        patch=int(m.group(3)),
        tag=m.group(4) or "",
    )


def find_repo_root() -> Path:
    cur = Path(__file__).resolve().parent
    for _ in range(5):
        if (cur / "components" / "h1os" / "include" / "h1os" / "h1os_version.h").is_file():
            return cur
        cur = cur.parent
    raise FileNotFoundError("Could not locate H1OS repository root from script path.")


def read_text_preserve_eol(path: Path) -> Tuple[str, str]:
    raw = path.read_bytes()
    eol = "\r\n" if b"\r\n" in raw else "\n"
    text = raw.decode("utf-8").replace("\r\n", "\n")
    return text, eol


def write_text_preserve_eol(path: Path, text: str, eol: str) -> None:
    out_text = text.replace("\n", eol) if eol != "\n" else text
    path.write_bytes(out_text.encode("utf-8"))


def read_current_version_from_header(repo_root: Path) -> SemVer:
    vh = repo_root / "components" / "h1os" / "include" / "h1os" / "h1os_version.h"
    text, _ = read_text_preserve_eol(vh)

    def _grab_int(macro: str) -> int:
        m = re.search(rf"^\s*#define\s+{macro}\s+(\d+)\b", text, re.MULTILINE)
        if not m:
            raise ValueError(f"Missing {macro} in {vh}")
        return int(m.group(1))

    def _grab_str(macro: str) -> str:
        m = re.search(rf'^\s*#define\s+{macro}\s+"([^"]*)"', text, re.MULTILINE)
        if not m:
            raise ValueError(f"Missing {macro} in {vh}")
        return m.group(1)

    major = _grab_int("H1OS_VERSION_MAJOR")
    minor = _grab_int("H1OS_VERSION_MINOR")
    patch = _grab_int("H1OS_VERSION_PATCH")
    tag = _grab_str("H1OS_VERSION_TAG")
    ver = SemVer(major=major, minor=minor, patch=patch, tag=tag)

    vstr = _grab_str("H1OS_VERSION_STRING")
    if vstr != ver.version_string:
        raise ValueError(
            f"Internal drift in {vh}: H1OS_VERSION_STRING='{vstr}' != '{ver.version_string}'"
        )
    return ver


def _format_define_padded(prefix: str, val_str: str, comment_col_target: int, suffix: str) -> str:
    cur_len = len(prefix) + len(val_str)
    pad = max(1, comment_col_target - cur_len)
    return f"{prefix}{val_str}{' ' * pad}{suffix}"


def _build_rules(repo_root: Path, include_idf: bool) -> List[Tuple[str, List[FieldRule]]]:
    def ver_rule(
        label: str,
        regex_str: str,
        value_fn: Callable[[SemVer, Optional[str]], str] = lambda v, _: v.version_string,
    ) -> FieldRule:
        pat = re.compile(regex_str, re.MULTILINE)
        return FieldRule(
            label=label,
            pattern=pat,
            render=lambda v, idf, m: f"{m.group(1)}{value_fn(v, idf)}{m.group(3)}",
            extract=lambda m: m.group(2),
            expected_val=value_fn,
        )

    rules: List[Tuple[str, List[FieldRule]]] = [
        (
            "components/h1os/include/h1os/h1os_version.h",
            [
                FieldRule(
                    label="H1OS_VERSION_MAJOR",
                    pattern=re.compile(r"^(#define\s+H1OS_VERSION_MAJOR\s+)(\d+)(\s+/\*\*<.*)$", re.MULTILINE),
                    render=lambda v, _i, m: _format_define_padded(m.group(1), str(v.major), 43, m.group(3).lstrip()),
                    extract=lambda m: m.group(2),
                    expected_val=lambda v, _i: str(v.major),
                ),
                FieldRule(
                    label="H1OS_VERSION_MINOR",
                    pattern=re.compile(r"^(#define\s+H1OS_VERSION_MINOR\s+)(\d+)(\s+/\*\*<.*)$", re.MULTILINE),
                    render=lambda v, _i, m: _format_define_padded(m.group(1), str(v.minor), 43, m.group(3).lstrip()),
                    extract=lambda m: m.group(2),
                    expected_val=lambda v, _i: str(v.minor),
                ),
                FieldRule(
                    label="H1OS_VERSION_PATCH",
                    pattern=re.compile(r"^(#define\s+H1OS_VERSION_PATCH\s+)(\d+)(\s+/\*\*<.*)$", re.MULTILINE),
                    render=lambda v, _i, m: _format_define_padded(m.group(1), str(v.patch), 43, m.group(3).lstrip()),
                    extract=lambda m: m.group(2),
                    expected_val=lambda v, _i: str(v.patch),
                ),
                FieldRule(
                    label="H1OS_VERSION_TAG",
                    pattern=re.compile(r'^(#define\s+H1OS_VERSION_TAG\s+)"([^"]*)"(\s+/\*\*<.*)$', re.MULTILINE),
                    render=lambda v, _i, m: _format_define_padded(m.group(1), f'"{v.tag}"', 43, m.group(3).lstrip()),
                    extract=lambda m: m.group(2),
                    expected_val=lambda v, _i: v.tag,
                ),
                FieldRule(
                    label="H1OS_VERSION_STRING",
                    pattern=re.compile(r'^(#define\s+H1OS_VERSION_STRING\s+)"([^"]+)"(\s+/\*\*<.*)$', re.MULTILINE),
                    render=lambda v, _i, m: _format_define_padded(m.group(1), f'"{v.version_string}"', 43, m.group(3).lstrip()),
                    extract=lambda m: m.group(2),
                    expected_val=lambda v, _i: v.version_string,
                ),
                ver_rule(
                    "Doxygen @return example",
                    r'^(\s*\*\s*@return Full version string \(e\.g\. ")([^"]+)("\)\.)',
                ),
            ],
        ),
        (
            "components/h1os/idf_component.yml",
            [ver_rule("component version", r'^(version:\s+")([^"]+)(")$')],
        ),
        (
            "README.md",
            [
                ver_rule(
                    "version badge",
                    r"^(\[!\[Version\]\(https://img\.shields\.io/badge/H1OS-)(v[0-9]+\.[0-9]+\.[0-9]+(?:--[0-9A-Za-z.-]+)?)(-brightgreen\.svg\)\]\(components/h1os/include/h1os/h1os\.h\))$",
                    lambda v, _i: v.shields_badge_token,
                ),
            ],
        ),
        (
            "Doxyfile",
            [ver_rule("PROJECT_NUMBER", r'^(PROJECT_NUMBER\s*=\s*")([^"]+)(")$')],
        ),
        (
            "ERRATA.md",
            [ver_rule("Applicable Firmware", r"^(> \*\*Applicable Firmware:\*\* H1OS `v)([^`]+)(`.*)$")],
        ),
        (
            "AGENTS.md",
            [
                ver_rule("spec header", r"^(This file constitutes .* working on \*\*H1OS\*\* \(`v)([^`]+)(\`\).*)$"),
                ver_rule("dual-core bullet", r"^(\s*-\s+\*\*Dual-Core Affinity & Parallel Execution \(`v)([^`]+)(`\):\*\*.*)$"),
                ver_rule("section 3 heading", r"^(## 3\. Application Lifecycle, Dual Execution Flows & Dual-Core Concurrency \(`v)([^`]+)(`\))$"),
                ver_rule("flow b heading", r"^(\s*-\s+Parallel Dual-Core Sequence \(`v)([^`]+)(`\s*/\s*`MANDATE-04`\):)$"),
                ver_rule("field guide item 2", r"^(2\.\s+\*\*Coordinate Core 0 I/O & Core 1 e-Paper Refresh Without Blocking \(`v)([^`]+)(`\):\*\*)$"),
                ver_rule("attribution range", r"^(\*\s+\*\*Principal Firmware Audit, .* \(`v2\.4\.4-dev` – `v)([^`]+)(`\):\*\*.*)$"),
            ],
        ),
        (
            ".agents/rules/arch.md",
            [ver_rule("arch rule header", r"^(This rule enforces .* across the \*\*H1OS\*\* \(`v)([^`]+)(`\) firmware.*)$")],
        ),
        (
            ".agents/rules/coding.md",
            [ver_rule("coding rule header", r"^(This rule governs .* in \*\*H1OS\*\* \(`v)([^`]+)(`\)\..*)$")],
        ),
        (
            ".agents/rules/docs.md",
            [
                ver_rule("docs rule header", r"^(This rule governs .* in \*\*H1OS\*\* \(`v)([^`]+)(`\)\..*)$"),
                ver_rule("docs rule attribution", r"^(-\s+\*\*Principal Firmware Audit, .* \(`v2\.4\.4-dev` – `v)([^`]+)(`\):\*\*.*)$"),
            ],
        ),
        (
            ".agents/rules/lifecycle.md",
            [
                ver_rule("lifecycle rule title", r"^(# Master Rule: H1OS Application Lifecycle & Dual-Core Concurrency Architecture \(`v)([^`]+)(`\))$"),
                ver_rule("lifecycle pattern heading", r"^(## 5\. Declarative C Implementation Pattern \(`v)([^`]+)(`\))$"),
            ],
        ),
        (
            ".agents/rules/lvgl.md",
            [
                ver_rule("lvgl rule title", r"^(# Master Rule: LVGL 9 Bilevel UI Design & E-Paper Constraints Specification \(`v)([^`]+)(`\))$"),
                ver_rule("lvgl thread heading", r"^(## 7\. Thread Safety, Dual-Core Affinity & `h1os_ui_post\(\)` Actor Queue \(`v)([^`]+)(`\))$"),
            ],
        ),
        (
            ".agents/rules/master.md",
            [ver_rule("master rule title", r"^(# Master Agent Execution Rules: H1OS & ESP32-S3 Firmware Development \(`v)([^`]+)(`\))$")],
        ),
        (
            ".agents/skills/h1os-build/SKILL.md",
            [ver_rule("h1os-build title", r"^(# H1OS & ESP32-S3 Firmware Build Guide \(`v)([^`]+)(`\))$")],
        ),
        (
            ".agents/skills/h1os-firmware-standards/SKILL.md",
            [ver_rule("firmware-standards title", r"^(# H1OS Firmware Engineering & Safety Standards Protocol \(`v)([^`]+)(`\))$")],
        ),
        (
            ".agents/skills/lvgl-ui/SKILL.md",
            [
                ver_rule("lvgl-ui title", r"^(# LVGL v9 Bilevel UI Design & E-Paper Font Validation \(`v)([^`]+)(`\))$"),
                ver_rule("lvgl-ui thread item", r"^(-\s+\*\*Thread Safety & Cross-Core Actor Queue \(`v)([^`]+)(`\):\*\*)$"),
            ],
        ),
        (
            ".agents/skills/main-merge-protocol/SKILL.md",
            [ver_rule("main-merge-protocol title", r"^(# Pre-Merge to Main Protocol & Release Execution \(`v)([^`]+)(`\))$")],
        ),
        (
            "components/h1os/tools/h1os_tool.py",
            [
                ver_rule("VERSION constant", r'^(VERSION\s*=\s*")([^"]+)(")$'),
                ver_rule("H1OS_TOOLING_VERSION constant", r'^(H1OS_TOOLING_VERSION\s*=\s*")([^"]+)(")$'),
            ],
        ),
        (
            "docs/guide.md",
            [
                ver_rule("guide Firmware Version", r"^(\*\*Firmware Version:\*\* `v)([^`]+)(`\s*)$"),
                *(
                    [
                        ver_rule(
                            "guide ESP-IDF version",
                            r"^(\*\*Supported Frameworks:\*\* ESP-IDF `v)([^`]+)(` \| LVGL .*)$",
                            lambda _v, idf: idf or "",
                        )
                    ]
                    if include_idf
                    else []
                ),
            ],
        ),
        (
            "docs/architecture/A1_master_blueprint.md",
            [
                ver_rule("A1 h1os_version.h note", r"^(-\s+\*\*`h1os_version\.h`\*\*:\s+Semantic version macros \(`)([^`]+)(`\) and inline getters\.)$"),
                *(
                    [
                        ver_rule(
                            "A1 Framework ESP-IDF",
                            r"^(-\s+\*\*Framework:\*\* ESP-IDF v)([0-9]+\.[0-9]+(?:\.[0-9]+)?)( \(Ninja.*)$",
                            lambda _v, idf: idf or "",
                        )
                    ]
                    if include_idf
                    else []
                ),
            ],
        ),
    ]

    arch_dir = repo_root / "docs" / "architecture"
    for md_path in sorted(arch_dir.glob("*.md")):
        rel = md_path.relative_to(repo_root).as_posix()
        arch_rules = [
            ver_rule(
                "arch spec Firmware Version header",
                r"^(> \*\*H1OS Architecture Specification\*\* \| \*\*Document:\*\* `[^`]+` \| \*\*Firmware Version:\*\* `v)([^`]+)(` \| \*\*ESP-IDF:\*\* `v[^`]+`\s*)$",
            )
        ]
        if include_idf:
            arch_rules.append(
                ver_rule(
                    "arch spec ESP-IDF header",
                    r"^(> \*\*H1OS Architecture Specification\*\* \| \*\*Document:\*\* `[^`]+` \| \*\*Firmware Version:\*\* `v[^`]+` \| \*\*ESP-IDF:\*\* `v)([^`]+)(`\s*)$",
                    lambda _v, idf: idf or "",
                )
            )
        rules.append((rel, arch_rules))

    return rules


def check_sync(repo_root: Path, expected_ver: SemVer, expected_idf: Optional[str]) -> int:
    rules = _build_rules(repo_root, include_idf=(expected_idf is not None))
    drifts: List[str] = []
    checked_fields = 0

    for rel, file_rules in rules:
        path = repo_root / rel
        if not path.is_file():
            drifts.append(f"{rel}: missing managed file")
            continue
        text, _ = read_text_preserve_eol(path)
        for rule in file_rules:
            checked_fields += 1
            matches = list(rule.pattern.finditer(text))
            if not matches:
                drifts.append(f"{rel} [{rule.label}]: anchor pattern not found")
                continue
            exp = rule.expected_val(expected_ver, expected_idf)
            for m in matches:
                got = rule.extract(m)
                if got != exp:
                    drifts.append(f"{rel} [{rule.label}]: found '{got}', expected '{exp}'")

    changelog_path = repo_root / "CHANGELOG.md"
    if not changelog_path.is_file():
        drifts.append("CHANGELOG.md: missing file")
    else:
        cl_text, _ = read_text_preserve_eol(changelog_path)
        cl_pat = re.compile(rf"^## \[{re.escape(expected_ver.version_string)}\] - \d{{4}}-\d{{2}}-\d{{2}}\s*$", re.MULTILINE)
        if not cl_pat.search(cl_text):
            drifts.append(
                f"CHANGELOG.md: missing release section heading '## [{expected_ver.version_string}] - YYYY-MM-DD'"
            )
        checked_fields += 1

    print(f"[*] Canonical version (h1os_version.h): {expected_ver.version_string}")
    print(f"[*] Checked {checked_fields} version anchor(s) across {len(rules) + 1} files.")
    if drifts:
        print(f"[FAIL] Detected {len(drifts)} synchronization drift(s):")
        for d in drifts:
            print(f"  - {d}")
        return 1

    print("[PASS] All managed version strings, architecture headers, and CHANGELOG.md are synchronized.")
    return 0


def apply_bump(
    repo_root: Path,
    target_ver: SemVer,
    idf_version: Optional[str],
    dry_run: bool,
) -> int:
    rules = _build_rules(repo_root, include_idf=(idf_version is not None))
    errors: List[str] = []
    modified_files: List[str] = []

    for rel, file_rules in rules:
        path = repo_root / rel
        if not path.is_file():
            errors.append(f"{rel}: missing managed file")
            continue
        orig_text, eol = read_text_preserve_eol(path)
        new_text = orig_text

        for rule in file_rules:
            def _sub_cb(m: re.Match[str], r: FieldRule = rule) -> str:
                return r.render(target_ver, idf_version, m)

            new_text, count = rule.pattern.subn(_sub_cb, new_text)
            if count == 0:
                errors.append(f"{rel} [{rule.label}]: anchor pattern matched 0 times")

        if new_text != orig_text:
            modified_files.append(rel)
            if not dry_run:
                write_text_preserve_eol(path, new_text, eol)

    if errors:
        print(f"[!] Completed with {len(errors)} anchor error(s):", file=sys.stderr)
        for err in errors:
            print(f"  - {err}", file=sys.stderr)
        return 1

    verb = "Would update" if dry_run else "Updated"
    print(f"[+] {verb} {len(modified_files)} file(s) to H1OS v{target_ver.version_string}" + (f" (ESP-IDF v{idf_version})" if idf_version else "") + ":")
    for rel in modified_files:
        print(f"  - {rel}")

    changelog_path = repo_root / "CHANGELOG.md"
    if changelog_path.is_file():
        cl_text, _ = read_text_preserve_eol(changelog_path)
        cl_pat = re.compile(rf"^## \[{re.escape(target_ver.version_string)}\] - \d{{4}}-\d{{2}}-\d{{2}}\s*$", re.MULTILINE)
        if not cl_pat.search(cl_text):
            print(f"[!] Reminder: add '## [{target_ver.version_string}] - YYYY-MM-DD' entry to CHANGELOG.md before running --check.")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(
        description="H1OS Semantic Version & Architecture Header Synchronizer"
    )
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument(
        "--set",
        metavar="X.Y.Z[-tag]",
        help="Set explicit target version (e.g. 2.4.10-dev).",
    )
    mode.add_argument(
        "--bump",
        choices=("major", "minor", "patch"),
        help="Increment major, minor, or patch version relative to h1os_version.h.",
    )
    mode.add_argument(
        "--check",
        action="store_true",
        help="Verify all managed files and CHANGELOG.md match h1os_version.h.",
    )
    parser.add_argument(
        "--tag",
        default=None,
        help="Optional pre-release tag override when using --bump (empty string clears tag).",
    )
    parser.add_argument(
        "--idf-version",
        default=None,
        help="Optional ESP-IDF version (e.g. 6.1.1) to update/verify in guide and architecture headers.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Report planned updates without modifying files on disk.",
    )
    args = parser.parse_args()

    try:
        repo_root = find_repo_root()
        current_ver = None if args.set else read_current_version_from_header(repo_root)
    except (OSError, ValueError) as exc:
        print(f"[!] Initialization error: {exc}", file=sys.stderr)
        return 1

    idf_ver: Optional[str] = None
    if args.idf_version is not None:
        m = IDF_VER_RE.match(args.idf_version.strip())
        if not m:
            print(f"[!] Invalid --idf-version '{args.idf_version}'.", file=sys.stderr)
            return 1
        idf_ver = m.group(1)

    if args.check:
        if current_ver is None:
            print("[!] Missing version header state for --check.", file=sys.stderr)
            return 1
        return check_sync(repo_root, current_ver, idf_ver)

    if args.set:
        try:
            target_ver = parse_semver(args.set)
        except ValueError as exc:
            print(f"[!] {exc}", file=sys.stderr)
            return 1
    else:
        if current_ver is None:
            print("[!] Missing version header state for --bump.", file=sys.stderr)
            return 1
        tag = current_ver.tag if args.tag is None else args.tag.strip()
        if args.bump == "major":
            target_ver = SemVer(current_ver.major + 1, 0, 0, tag)
        elif args.bump == "minor":
            target_ver = SemVer(current_ver.major, current_ver.minor + 1, 0, tag)
        else:
            target_ver = SemVer(current_ver.major, current_ver.minor, current_ver.patch + 1, tag)

    return apply_bump(repo_root, target_ver, idf_ver, dry_run=args.dry_run)


if __name__ == "__main__":
    sys.exit(main())
