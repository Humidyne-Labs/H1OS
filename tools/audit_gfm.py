import os
import re
import sys

def audit_markdown():
    in_scope_files = []

    # Audit root markdown files
    for f in os.listdir("."):
        if f.endswith(".md"):
            in_scope_files.append(os.path.abspath(f))

    # Audit docs/ public folders
    docs_dir = os.path.abspath("docs")
    if os.path.exists(docs_dir):
        for root, dirs, files in os.walk(docs_dir):
            # Explicitly exclude internal agent notes and logs
            if any(exempt in root.replace("\\", "/") for exempt in ["docs/agent_notes", "docs/logs"]):
                continue
            for f in files:
                if f.endswith(".md"):
                    in_scope_files.append(os.path.join(root, f))

    # Audit .agents/ rules and skills
    agents_dir = os.path.abspath(".agents")
    if os.path.exists(agents_dir):
        for root, dirs, files in os.walk(agents_dir):
            for f in files:
                if f.endswith(".md"):
                    in_scope_files.append(os.path.join(root, f))

    print(f"Total public documentation files in scope: {len(in_scope_files)}")
    issues = []

    for filepath in in_scope_files:
        rel_path = os.path.relpath(filepath, ".")
        with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
            lines = f.readlines()

        in_mermaid = False
        in_code_block = False
        for i, line in enumerate(lines):
            line_num = i + 1
            stripped = line.strip()

            if stripped.startswith("```"):
                if not in_code_block:
                    in_code_block = True
                    if "mermaid" in stripped.lower():
                        in_mermaid = True
                else:
                    in_code_block = False
                    in_mermaid = False
                continue

            if in_code_block and not in_mermaid:
                continue

            if in_mermaid:
                if "<br" in line:
                    issues.append((rel_path, line_num, "Mermaid: raw <br> tag found in diagram (use hyphen/newline)"))
                if "&" in line and not "&amp;" in line and not re.search(r"-->|==>|-.->", line):
                    if re.search(r"\[.*&.*\]|\(.*\b&\b.*\)", line):
                        issues.append((rel_path, line_num, "Mermaid: raw & symbol in node label (use 'and')"))
                if re.search(r'subgraph\s+"[^"]+"', line):
                    issues.append((rel_path, line_num, "Mermaid: subgraph missing alphanumeric ID (use: subgraph ID [\"Label\"])"))
                continue

            # Column 0 rule for $$:
            if "$$" in line:
                # If $$ is wrapped in backticks (e.g. `$$`), it is inline code referring to the syntax, not a block equation
                cleaned_line = re.sub(r"`[^`]*`", "", line)
                if "$$" in cleaned_line:
                    if (line.startswith(" ") or line.startswith("\t")) and "$$" in cleaned_line:
                        issues.append((rel_path, line_num, "GFM: Indented $$ block (must start at column 0)"))

            # Single line $$...$$ check:
            cleaned_line = re.sub(r"`[^`]*`", "", line)
            m = re.search(r"\$\$[^\$\n]+\$\$", cleaned_line)
            if m:
                issues.append((rel_path, line_num, f"GFM: Single-line display math {m.group(0)} (must be multiline)"))

            # Check for \_ inside math
            if re.search(r"\$[^$\n]*\\_[^$\n]*\$", line):
                issues.append((rel_path, line_num, "GFM: \\_ used in math mode (causes '_ allowed only in math mode')"))

            # Check for callout formatting
            if re.search(r"^\s+>\s*\[!", line):
                issues.append((rel_path, line_num, "GFM: Alert has leading spaces before >"))
            if re.search(r"^>\s*\[!(NOTE|TIP|IMPORTANT|WARNING|CAUTION)\]", line):
                if not line.startswith("> [!"):
                    issues.append((rel_path, line_num, "GFM: Alert format not canonical '> [!TYPE]'"))

    print(f"\nAudit complete. Total public documentation issues detected: {len(issues)}\n")
    for filepath, line_num, desc in issues:
        print(f"{filepath}:{line_num}: {desc}")

if __name__ == "__main__":
    audit_markdown()
