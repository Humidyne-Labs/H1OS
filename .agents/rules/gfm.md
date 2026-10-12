# Markdown and GFM Formatting Rules

All documentation (`.md`) across this repository must strictly adhere to the GitHub Flavored Markdown (GFM) specification.

Refer to the skill [`.agents/skills/gfm/SKILL.md`](../skills/gfm/SKILL.md) for full reference.

## Mandatory Rules

1. **MathJax Block Math (`$$`):**
   - MUST be isolated on separate lines starting strictly at **column 0** (zero leading spaces, even when following a bulleted or numbered list item). GitHub's `cmark-gfm` parser breaks indented `  $$` blocks inside lists into plain text!
   - MUST be preceded and followed by an empty blank line.
   - NEVER format block math on a single line (`$$formula$$` is forbidden).

2. **MathJax Inline & Block Subscripts (`$` / `$$`):**
   - No whitespace between the opening/closing `$` and the expression (`$x$` is valid, `$ x $` breaks MathJax).
   - **NEVER use `\_` inside `\text{...}` or math expressions:** GitHub's Markdown preprocessor strips the backslash from `\_` before passing the expression to MathJax, causing a fatal `'_' allowed only in math mode` error. Use single-word subscripts (`T_{\text{floor}}`), hyphens (`T_{\text{amb-floor}}`), or parentheses (`V_{\text{bat(mV)}}`).
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
