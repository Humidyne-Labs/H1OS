import hashlib
import os
import re
from pathlib import Path
from PIL import Image

# Set to False to apply deduplication, conversion, and renaming
DRY_RUN = False

# Target formats to process
INPUT_EXTENSIONS = {".jpg", ".jpeg", ".webp", ".bmp", ".png"}

# Timestamp regex patterns
PAT_HYPHEN = re.compile(
    r"^(?P<year>\d{4})-(?P<month>\d{2})-(?P<day>\d{2})-"
    r"(?P<hour>\d{2})-(?P<min>\d{2})-(?P<sec>\d{2})"
    r"(?:-(?P<subseq>\d+))?(?:_(?P<extra>\w+))?$"
)

PAT_IMG = re.compile(
    r"^IMG_(?P<year>\d{4})(?P<month>\d{2})(?P<day>\d{2})_"
    r"(?P<hour>\d{2})(?P<min>\d{2})(?P<sec>\d{2})"
    r"(?P<subseq>\d+)?$"
)


def get_file_hash(path: Path, chunk_size: int = 65536) -> str:
    """Computes SHA-256 hash of file contents to detect exact duplicates."""
    hasher = hashlib.sha256()
    with open(path, "rb") as f:
        while chunk := f.read(chunk_size):
            hasher.update(chunk)
    return hasher.hexdigest()


def parse_timestamp(stem: str) -> str | None:
    m = PAT_HYPHEN.match(stem)
    if m:
        d = m.groupdict()
        base = f"{d['year']}-{d['month']}-{d['day']}_{d['hour']}-{d['min']}-{d['sec']}"
        parts = [base]
        if d.get("subseq"):
            parts.append(d["subseq"])
        if d.get("extra"):
            parts.append(d["extra"])
        return "_".join(parts)

    m = PAT_IMG.match(stem)
    if m:
        d = m.groupdict()
        base = f"{d['year']}-{d['month']}-{d['day']}_{d['hour']}-{d['min']}-{d['sec']}"
        parts = [base]
        if d.get("subseq"):
            parts.append(d["subseq"])
        return "_".join(parts)

    return None


def main():
    folder = Path(".")
    seen_hashes = {}
    files_to_process = []

    # Gather matching files sorted alphabetically
    for p in sorted(folder.iterdir()):
        if p.is_file() and p.suffix.lower() in INPUT_EXTENSIONS:
            files_to_process.append(p)

    print(f"[{'DRY RUN' if DRY_RUN else 'APPLYING'}] Processing {len(files_to_process)} image(s)...\n")

    for file_path in files_to_process:
        # Step 1: Duplicate detection
        file_hash = get_file_hash(file_path)
        if file_hash in seen_hashes:
            orig = seen_hashes[file_hash]
            print(f"[DUPLICATE REMOVED] '{file_path.name}' is identical to '{orig}'")
            if not DRY_RUN:
                file_path.unlink()
            continue

        seen_hashes[file_hash] = file_path.name

        # Step 2: Determine normalized base name
        normalized_stem = parse_timestamp(file_path.stem) or file_path.stem
        target_path = folder / f"{normalized_stem}.png"

        # Avoid collision if destination name already exists as a distinct file
        counter = 1
        while target_path.exists() and target_path != file_path and not DRY_RUN:
            target_path = folder / f"{normalized_stem}_{counter}.png"
            counter += 1

        print(f"[CONVERT & RENAME] '{file_path.name}' -> '{target_path.name}'")

        if not DRY_RUN:
            # Step 3: Convert to PNG and save
            with Image.open(file_path) as img:
                img.save(target_path, format="PNG")

            # Remove original file if it was not already the target PNG
            if file_path.resolve() != target_path.resolve():
                file_path.unlink()

    if DRY_RUN:
        print("\nReview the output above, then set DRY_RUN = False to execute.")


if __name__ == "__main__":
    main()