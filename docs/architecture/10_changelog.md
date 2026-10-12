# Document 10: Changelog Policy & SemVer Management

This document defines the release cadence, versioning policy, and modification tracking standard for **H1OS**.

---

## 1. Authoritative Changelog Location

To maintain a single source of truth and eliminate fractured records, all official release notes, code changes, breaking architectural modifications, and bug fixes are maintained exclusively in the repository root:

👉 **[`CHANGELOG.md`](../../CHANGELOG.md)**

---

## 2. Versioning Strategy

H1OS strictly adheres to [Semantic Versioning 2.0.0](https://semver.org/):

$$\text{Version} = \text{MAJOR}.\text{MINOR}.\text{PATCH}$$

- **MAJOR (vX.0.0):** Incompatible API changes, Layer 1–4 boundary reorganizations, or hardware breaking alterations.
- **MINOR (vx.Y.0):** Backward-compatible feature additions, new subsystem capabilities, or non-breaking API extensions.
- **PATCH (vx.y.Z):** Backward-compatible bug fixes, driver timing patches, or documentation corrections.

---

## 3. Modification Categorization Standards

Every release entry in [`CHANGELOG.md`](../../CHANGELOG.md) must categorize changes under standard Keep-a-Changelog headings:
- `Added` for new features and drivers.
- `Changed` for changes in existing functionality.
- `Deprecated` for soon-to-be-removed features.
- `Removed` for now-removed features.
- `Fixed` for bug fixes.
- `Security` in case of vulnerabilities.
