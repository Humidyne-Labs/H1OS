import subprocess
from pathlib import Path

# Set to False to perform the renames
DRY_RUN = False


def is_git_tracked(file_path: Path) -> bool:
    """Returns True if Git is tracking this file."""
    result = subprocess.run(
        ["git", "ls-files", "--error-unmatch", str(file_path)],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return result.returncode == 0


def rename_two_step(src: Path, dest: Path):
    temp = src.parent / f"{src.name}.tmp_case_swap"

    if is_git_tracked(src):
        # Two-step git mv to bypass NTFS case collisions
        subprocess.run(["git", "mv", "-f", str(src), str(temp)], check=True)
        subprocess.run(["git", "mv", "-f", str(temp), str(dest)], check=True)
    else:
        # Standard filesystem two-step rename for untracked files
        src.rename(temp)
        temp.rename(dest)


def main():
    root = Path(".")
    targets = []

    # Exclude temporary swap files if any were left behind
    for path in root.rglob("*"):
        if path.is_file() and not path.name.endswith(".tmp_case_swap"):
            if path.name != path.name.lower():
                targets.append(path)

    if not targets:
        print("All files are already lowercase.")
        return

    print(f"[{'DRY RUN' if DRY_RUN else 'APPLYING'}] Processing {len(targets)} file(s):\n")

    for src in targets:
        dest = src.parent / src.name.lower()
        tracked = is_git_tracked(src)
        status = "tracked (git mv)" if tracked else "untracked (os rename)"

        print(f"  {src.relative_to(root)} -> {src.name.lower()}  [{status}]")

        if not DRY_RUN:
            rename_two_step(src, dest)

    if DRY_RUN:
        print("\nSet DRY_RUN = False to apply the renames.")
    else:
        print("\nAll files successfully normalized to lowercase.")


if __name__ == "__main__":
    main()