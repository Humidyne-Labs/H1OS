# Markdown and GFM Formatting Rules

All documentation (`.md`) across this repository must strictly adhere to the GitHub Flavored Markdown (GFM) specification.

Refer to the skill [`.agents/skills/gfm/SKILL.md`](../skills/gfm/SKILL.md) for full reference.

## Mandatory Rules

1. **MathJax Block Math (`$$`):**
   - MUST be isolated on separate lines.
   - MUST be preceded and followed by an empty blank line.
   - NEVER format block math on a single line (`$$formula$$` is forbidden).
   - Indent `$$` and its content to match list nesting levels.

2. **MathJax Inline Math (`$`):**
   - No whitespace between the opening/closing `$` and the expression (`$x$` is valid, `$ x $` breaks MathJax).
   - Use `\text{...}` for units: `$\mu\text{A}$`, `\text{ms}`, `^\circ\text{C}`.
   - Escape literal dollar signs with `\$` or wrap in backticks.

3. **Mermaid Diagrams:**
   - Always declare subgraphs with alphanumeric identifiers: `subgraph ID ["Label"]`.
   - Wrap node text containing punctuation, parentheses, brackets, colons, or arrows in double quotes `["..."]`.
   - Never use reserved keywords (`end`, `subgraph`, `graph`, `style`) as node or subgraph IDs.
   - Avoid duplicate IDs between nodes and subgraphs.

4. **Alerts & Callouts:**
   - Use strictly `> [!NOTE]`, `> [!TIP]`, `> [!IMPORTANT]`, `> [!WARNING]`, or `> [!CAUTION]`.
   - No leading spaces before the `>`.

5. **HTML and Markdown Interleaving:**
   - Always insert an empty newline after `</summary>` or closing HTML tags before writing Markdown.
