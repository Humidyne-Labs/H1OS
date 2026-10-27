import hashlib
import os
import re
from pathlib import Path
from PIL import Image

DRY_RUN = False
INPUT_EXTENSIONS = {".jpg", ".jpeg", ".webp", ".bmp", ".png"}

# 1. Hyphenated: 2026-10-21-21-27-07-818_002
PAT_HYPHEN = re.compile(
    r"^(?P<year>\d{4})-(?P<month>\d{2})-(?P<day>\d{2})-"
    r"(?P<hour>\d{2})-(?P<min>\d{2})-(?P<sec>\d{2})"
    r"(?:-(?P<subseq>\d+))?(?:_(?P<extra>\w+))?$"
)

# 2. Standard IMG: IMG_20261023_013334847
PAT_IMG = re.compile(
    r"^IMG_(?P<year>\d{4})(?P<month>\d{2})(?P<day>\d{2})_"
    r"(?P<hour>\d{2})(?P<min>\d{2})(?P<sec>\d{2})"
    r"(?P<subseq>\d+)?$"
)

# 3. Compact instrument IMG: IMG230600194427 (IMG + 6 digits + HHMMSS)
PAT_IMG_COMPACT = re.compile(
    r"^IMG(?P<p1>\d{2})(?P<p2>\d{2})(?P<p3>\d{2})(?P<hour>\d{2})(?P<min>\d{2})(?P<sec>\d{2})$"
)


def parse_timestamp(stem: str) -> str | None:
    # Pattern 1
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

    # Pattern 2
    m = PAT_IMG.match(stem)
    if m:
        d = m.groupdict()
        base = f"{d['year']}-{d['month']}-{d['day']}_{d['hour']}-{d['min']}-{d['sec']}"
        parts = [base]
        if d.get("subseq"):
            parts.append(d["subseq"])
        return "_".join(parts)

    # Pattern 3: Compact 12-digit (IMG DD MM YY HH MM SS or YY MM DD HH MM SS)
    m = PAT_IMG_COMPACT.match(stem)
    if m:
        d = m.groupdict()
        p1, p2, p3 = d["p1"], d["p2"], d["p3"]
        h, mn, s = d["hour"], d["min"], d["sec"]

        # Option A (DD-MM-YY -> 20YY-MM-DD): 23-06-00 -> 2000-06-23
        year = f"20{p3}"
        month = p2
        day = p1

        # Option B: If your device uses YY-MM-DD instead, uncomment this line:
        # year, month, day = f"20{p1}", p2, p3

        return f"{year}-{month}-{day}_{h}-{mn}-{s}"

    return None
    
def get_file_hash(path: Path, chunk_size: int = 65536) -> str:
    """Computes SHA-256 hash of file contents to detect exact duplicates."""
    hasher = hashlib.sha256()
    with open(path, "rb") as f:
        while chunk := f.read(chunk_size):
            hasher.update(chunk)
    return hasher.hexdigest()

    
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
        target_path = folder / f"{normalized_stem}.jpg"

        # Avoid collision if destination name already exists as a distinct file
        counter = 1
        while target_path.exists() and target_path != file_path and not DRY_RUN:
            target_path = folder / f"{normalized_stem}_{counter}.jpg"
            counter += 1

        print(f"[CONVERT & RENAME] '{file_path.name}' -> '{target_path.name}'")

        if not DRY_RUN:
            # Step 3: Convert to JPG and save
            with Image.open(file_path) as img:
                img.save(target_path, format="JPEG")

            # Remove original file if it was not already the target JPG
            if file_path.resolve() != target_path.resolve():
                file_path.unlink()

    if DRY_RUN:
        print("\nReview the output above, then set DRY_RUN = False to execute.")


if __name__ == "__main__":
    main()    