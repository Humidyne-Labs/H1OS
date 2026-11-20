"""Offline host C11 compilation & execution tests for H1OS math, OCV, and flow slicing."""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
HOST_TESTS_DIR = REPO_ROOT / "tests" / "firmware_host"
DEFAULT_CLANG = Path("C:/clang+llvm-18.1.8/bin/clang.exe")


def _resolve_clang() -> str:
    if DEFAULT_CLANG.is_file():
        return str(DEFAULT_CLANG)
    found = shutil.which("clang")
    assert found is not None, "clang compiler not found for host C11 verification"
    return found


def test_orch_math_host_c11(tmp_path: Path) -> None:
    clang = _resolve_clang()
    exe_ext = ".exe" if os.name == "nt" else ""
    out_bin = tmp_path / f"test_orch_math{exe_ext}"
    cmd = [
        clang,
        "-std=c11",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wdouble-promotion",
        f"-I{HOST_TESTS_DIR / 'stubs'}",
        f"-I{REPO_ROOT / 'components' / 'h1os' / 'include'}",
        str(HOST_TESTS_DIR / "test_orch_math.c"),
        str(REPO_ROOT / "components" / "h1os" / "src" / "orch_math.c"),
        "-o",
        str(out_bin),
    ]
    if os.name != "nt":
        cmd.append("-lm")
    comp = subprocess.run(cmd, capture_output=True, text=True, check=False)
    assert comp.returncode == 0, comp.stdout + "\n" + comp.stderr
    run = subprocess.run([str(out_bin)], capture_output=True, text=True, check=False)
    assert run.returncode == 0, run.stdout + "\n" + run.stderr


def test_flow_and_ocv_host_c11(tmp_path: Path) -> None:
    clang = _resolve_clang()
    exe_ext = ".exe" if os.name == "nt" else ""
    out_bin = tmp_path / f"test_flow_and_ocv{exe_ext}"
    cmd = [
        clang,
        "-std=c11",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wdouble-promotion",
        str(HOST_TESTS_DIR / "test_flow_and_ocv.c"),
        "-o",
        str(out_bin),
    ]
    comp = subprocess.run(cmd, capture_output=True, text=True, check=False)
    assert comp.returncode == 0, comp.stdout + "\n" + comp.stderr
    run = subprocess.run([str(out_bin)], capture_output=True, text=True, check=False)
    assert run.returncode == 0, run.stdout + "\n" + run.stderr
