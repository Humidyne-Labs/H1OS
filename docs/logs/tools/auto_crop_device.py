#!/usr/bin/env python3
"""
auto_crop_device.py

Batch-rotates, perspective-aligns (deskews), and auto-crops photos of a
light-colored rectangular device (e.g., an e-ink unit) on a darker surface,
preserving the original pixels without re-rendering.

Dependencies:
    pip install opencv-python numpy pillow
"""

import argparse
import os
import sys
from pathlib import Path
from typing import Iterable, List, Optional, Tuple

import cv2
import numpy as np
from PIL import Image, ImageOps

SUPPORTED_EXTS = {".jpg", ".jpeg", ".png", ".webp", ".bmp", ".tif", ".tiff"}


def fit_edge_line(pts: np.ndarray) -> Tuple[float, float, float, float]:
    """Fit a line (vx, vy, x0, y0) using robust Huber distance."""
    pts = np.asarray(pts, dtype=np.float32)
    vx, vy, x0, y0 = cv2.fitLine(pts, cv2.DIST_HUBER, 0, 0.01, 0.01).flatten()
    return float(vx), float(vy), float(x0), float(y0)


def intersect_lines(
    l1: Tuple[float, float, float, float],
    l2: Tuple[float, float, float, float],
) -> Optional[Tuple[float, float]]:
    """Compute intersection point of two parametric lines."""
    vx1, vy1, x1, y1 = l1
    vx2, vy2, x2, y2 = l2
    A = np.array([[vx1, -vx2], [vy1, -vy2]], dtype=np.float64)
    b = np.array([x2 - x1, y2 - y1], dtype=np.float64)
    if abs(np.linalg.det(A)) < 1e-8:
        return None
    t, _ = np.linalg.solve(A, b)
    return (x1 + t * vx1, y1 + t * vy1)


def apply_rotation(img: np.ndarray, degrees_ccw: int) -> np.ndarray:
    """Rotate image counter-clockwise by 0, 90, 180, 270, or 360 degrees."""
    deg = degrees_ccw % 360
    if deg == 0:
        return img
    if deg == 90:
        return cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)
    if deg == 180:
        return cv2.rotate(img, cv2.ROTATE_180)
    if deg == 270:
        return cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)
    raise ValueError(f"Unsupported rotation angle: {degrees_ccw}")


def find_device_contour(img: np.ndarray, l_thresh: int = 145, chroma_thresh: int = 18) -> np.ndarray:
    """Segment the central light-colored rectangular device and return its contour."""
    h, w = img.shape[:2]
    lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
    L, A, B = cv2.split(lab)
    chroma = np.sqrt((A.astype(np.float32) - 128.0) ** 2 + (B.astype(np.float32) - 128.0) ** 2)
    mask = ((L > l_thresh) & (chroma < chroma_thresh)).astype(np.uint8) * 255

    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (15, 15))
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    if not contours:
        raise RuntimeError("No device contour detected.")

    cx_img, cy_img = w / 2.0, h / 2.0
    best_cnt = None
    best_score = -1.0
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area < 0.05 * w * h:
            continue
        M = cv2.moments(cnt)
        if M["m00"] == 0:
            continue
        cx = M["m10"] / M["m00"]
        cy = M["m01"] / M["m00"]
        dist = np.hypot(cx - cx_img, cy - cy_img)
        score = area / (1.0 + dist / 500.0)
        if score > best_score:
            best_score = score
            best_cnt = cnt

    return best_cnt if best_cnt is not None else max(contours, key=cv2.contourArea)


def order_corners(box: np.ndarray) -> Tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    """Order 4 points as (top-left, top-right, bottom-right, bottom-left)."""
    s = box.sum(axis=1)
    diff = np.diff(box, axis=1).flatten()
    tl = box[np.argmin(s)]
    br = box[np.argmax(s)]
    tr = box[np.argmin(diff)]
    bl = box[np.argmax(diff)]
    return tl, tr, br, bl


def process_image(
    input_path: Path,
    output_path: Path,
    rotate_deg: int = 90,
    padding: int = 12,
    quality: int = 95,
    deskew: bool = True,
) -> Tuple[Tuple[int, int], float]:
    """Load, rotate, align, and auto-crop a single image."""
    pil_im = Image.open(input_path)
    pil_im = ImageOps.exif_transpose(pil_im)
    img = cv2.cvtColor(np.array(pil_im), cv2.COLOR_RGB2BGR)

    img = apply_rotation(img, rotate_deg)
    cnt = find_device_contour(img)

    if not deskew:
        x, y, bw, bh = cv2.boundingRect(cnt)
        x0 = max(0, x - padding)
        y0 = max(0, y - padding)
        x1 = min(img.shape[1], x + bw + padding)
        y1 = min(img.shape[0], y + bh + padding)
        cropped = img[y0:y1, x0:x1]
        cv2.imwrite(str(output_path), cropped, [cv2.IMWRITE_JPEG_QUALITY, quality])
        return (cropped.shape[1], cropped.shape[0]), 0.0

    rect = cv2.minAreaRect(cnt)
    tl, tr, br, bl = order_corners(cv2.boxPoints(rect))

    pts = cnt.reshape(-1, 2).astype(np.float32)
    u_vec = tr - tl
    u_len = float(np.linalg.norm(u_vec))
    u_hat = u_vec / u_len
    v_vec = bl - tl
    v_len = float(np.linalg.norm(v_vec))
    v_hat = v_vec / v_len

    rel = pts - tl
    u_coord = rel @ u_hat
    v_coord = rel @ v_hat

    tol = 25.0
    top_pts = pts[(v_coord < tol) & (u_coord > 0.2 * u_len) & (u_coord < 0.8 * u_len)]
    bot_pts = pts[(v_coord > v_len - tol) & (u_coord > 0.2 * u_len) & (u_coord < 0.8 * u_len)]
    left_pts = pts[(u_coord < tol) & (v_coord > 0.2 * v_len) & (v_coord < 0.8 * v_len)]
    right_pts = pts[(u_coord > u_len - tol) & (v_coord > 0.2 * v_len) & (v_coord < 0.8 * v_len)]

    src_corners = np.array([tl, tr, br, bl], dtype=np.float32)
    if min(len(top_pts), len(bot_pts), len(left_pts), len(right_pts)) >= 20:
        c_tl = intersect_lines(fit_edge_line(top_pts), fit_edge_line(left_pts))
        c_tr = intersect_lines(fit_edge_line(top_pts), fit_edge_line(right_pts))
        c_br = intersect_lines(fit_edge_line(bot_pts), fit_edge_line(right_pts))
        c_bl = intersect_lines(fit_edge_line(bot_pts), fit_edge_line(left_pts))
        if all(c is not None for c in (c_tl, c_tr, c_br, c_bl)):
            src_corners = np.array([c_tl, c_tr, c_br, c_bl], dtype=np.float32)

    out_w = int(round(max(np.linalg.norm(src_corners[1] - src_corners[0]),
                          np.linalg.norm(src_corners[2] - src_corners[3]))))
    out_h = int(round(max(np.linalg.norm(src_corners[3] - src_corners[0]),
                          np.linalg.norm(src_corners[2] - src_corners[1]))))

    dst_corners = np.array([
        [padding, padding],
        [padding + out_w - 1, padding],
        [padding + out_w - 1, padding + out_h - 1],
        [padding, padding + out_h - 1],
    ], dtype=np.float32)

    M_persp = cv2.getPerspectiveTransform(src_corners, dst_corners)
    warped = cv2.warpPerspective(
        img,
        M_persp,
        (out_w + 2 * padding, out_h + 2 * padding),
        flags=cv2.INTER_LANCZOS4,
        borderMode=cv2.BORDER_REPLICATE,
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    ext = output_path.suffix.lower()
    if ext in {".jpg", ".jpeg"}:
        cv2.imwrite(str(output_path), warped, [cv2.IMWRITE_JPEG_QUALITY, quality])
    else:
        cv2.imwrite(str(output_path), warped)

    tilt_deg = float(np.degrees(np.arctan2(
        src_corners[1][1] - src_corners[0][1],
        src_corners[1][0] - src_corners[0][0],
    )))
    return (warped.shape[1], warped.shape[0]), tilt_deg


def collect_inputs(paths: Iterable[str]) -> List[Path]:
    collected: List[Path] = []
    for raw in paths:
        p = Path(raw)
        if p.is_dir():
            collected.extend(
                sorted(f for f in p.iterdir() if f.is_file() and f.suffix.lower() in SUPPORTED_EXTS)
            )
        elif p.is_file() and p.suffix.lower() in SUPPORTED_EXTS:
            collected.append(p)
        else:
            print(f"Skipping unsupported or missing path: {p}", file=sys.stderr)
    return collected


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Rotate, perspective-align, and auto-crop device photos."
    )
    parser.add_argument(
        "inputs",
        nargs="+",
        help="Input image file(s) or directory of images.",
    )
    parser.add_argument(
        "-o", "--output",
        default="cropped_output",
        help="Output directory (default: ./cropped_output).",
    )
    parser.add_argument(
        "-r", "--rotate",
        type=int,
        choices=[90, 180, 270, 360],
        default=90,
        help="Counter-clockwise rotation in degrees before alignment/crop (90, 180, 270, or 360; default: 90).",
    )
    parser.add_argument(
        "-p", "--padding",
        type=int,
        default=12,
        help="Margin in pixels around the detected device edges (default: 12).",
    )
    parser.add_argument(
        "-q", "--quality",
        type=int,
        default=95,
        help="JPEG output quality 1-100 (default: 95).",
    )
    parser.add_argument(
        "--no-deskew",
        action="store_true",
        help="Disable perspective/tilt alignment and perform a simple bounding-box crop.",
    )
    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()

    files = collect_inputs(args.inputs)
    if not files:
        print("No valid image files found.", file=sys.stderr)
        return 1

    out_dir = Path(args.output)
    out_dir.mkdir(parents=True, exist_ok=True)

    for src in files:
        dst = out_dir / src.name
        try:
            (w, h), tilt = process_image(
                src,
                dst,
                rotate_deg=args.rotate,
                padding=args.padding,
                quality=args.quality,
                deskew=not args.no_deskew,
            )
            print(f"{src.name} -> {dst} ({w}x{h}, tilt={tilt:.2f} deg)")
        except Exception as exc:
            print(f"Error processing {src.name}: {exc}", file=sys.stderr)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())