---
name: gfm-markdown-formatting
description: >-
  Strict GitHub Flavored Markdown (GFM) formatting guidelines, MathJax equation syntax,
  and Mermaid diagram specifications. Use whenever authoring, updating, validating, or refactoring
  Markdown documentation, architecture specifications, errata, or tables.
---

# GitHub Flavored Markdown (GFM) Specification & Authoring Guide

This skill governs the authoring, formatting, and structural validation of all documentation in the repository. It enforces strict compliance with the GitHub Flavored Markdown (GFM) specification, CommonMark, MathJax rendering engine rules, and GitHub's Mermaid diagram parser.

---

## 1. LaTeX Mathematical Expressions (MathJax)

GitHub parses mathematical expressions using MathJax. Syntax errors cause equations to render as raw broken text.

### 1.1 Block / Display Math (`$$`)
Block equations **must** be written as dedicated multi-line blocks isolated by blank lines above and below.

#### Required Format:
```markdown
Text preceding the equation.

$$
RH = \frac{e}{e_s(T)} \times 100\%
$$

Text proceeding the equation.
```

#### Formatting Invariants:
1. **Never write single-line display math:** `$$formula$$` is brittle across differing GitHub renderers.
2. **Surround with empty newlines:** There **must** be a blank newline before the opening `$$` and after the closing `$$`.
3. **Indented block math:** When placing block equations inside bulleted lists, indent the opening `$$`, the equation content, and the closing `$$` by 2 or 4 spaces to match the list level, and keep empty lines between them.

```markdown
- **Vapor Pressure ($e$):**

  $$
  e = \frac{RH}{100} \cdot e_s(T) \quad [\text{hPa}]
  $$

- **True Dew Point ($T_{\text{dew}}$):**
```

### 1.2 Inline Math (`$...$`)
Inline math renders formulas within a sentence.

#### Required Format:
```markdown
The sensor completes sampling in $<10\text{ ms}$ with quiescent leakage $\le 15\ \mu\text{A}$.
```

#### Formatting Invariants:
1. **No Interior Whitespace:** The opening `$` must NOT be followed immediately by a space, and the closing `$` must NOT be preceded by a space.
   - ✅ Correct: `$x$` or `$T_{\text{dew}} = 12.5^\circ\text{C}$`
   - ❌ Invalid: `$ x $` or `$ T_{\text{dew}} $` (Breaks MathJax rendering)
2. **Escaping Literal Dollar Signs:** To display literal currency or shell symbols, escape with `\$` or wrap in backticks (`$HOME`).
3. **Units in Math:** Use `\text{...}` for engineering units, e.g., `$\mu\text{A}$`, `\text{mV}`, `\text{hPa}`, `\Omega`.

---

## 2. Mermaid Diagrams

Diagrams render automatically inside fenced code blocks tagged with `mermaid`. GitHub's parser is sensitive to reserved keywords, quotes, and punctuation.

### 2.1 Subgraphs & Node Identifiers
1. **Valid Alphanumeric Subgraph IDs:** Always declare subgraphs with a clean alphanumeric ID and put the human-readable title inside square brackets with quotes:
   - ✅ Correct: `subgraph Power_Rails ["Power Distribution Rails"]`
   - ❌ Invalid: `subgraph "Power Distribution Rails"`
2. **No Reserved Keyword Collisions:** Do not name nodes or subgraphs using Mermaid keywords (`end`, `subgraph`, `graph`, `style`, `click`) or duplicate an identifier between a node and a subgraph.
3. **Escaped Labels:** Whenever a node label contains parentheses, colons, arrows, or brackets, wrap the entire label in double quotes:
   - ✅ Correct: `CORE0["Core 0: Networking / OS (IO47 SDA)"]`
   - ❌ Invalid: `CORE0[Core 0: Networking / OS (IO47 SDA)]`
4. **Sanitize Quotation Marks:** Never use raw double quotes or nested unmatched single quotes (such as `1.54''`) inside node labels. Use `1.54in` or explicit HTML entities (`&quot;`).

### 2.2 Standard Mermaid Skeleton Examples

#### Flowchart (`flowchart TD`)
```mermaid
flowchart TD
    StartNode["1. Boot Hardware"] --> CheckVbat{Vbat < 3.25V?}
    CheckVbat -- "YES" --> SleepMode["Enter Low Power Sleep"]
    CheckVbat -- "NO" --> ActiveMode["Launch FreeRTOS Tasks"]
```

#### Sequence Diagram (`sequenceDiagram`)
```mermaid
sequenceDiagram
    autonumber
    participant App as Orchestrator
    participant Sensor as SHTC3 (I2C)
    participant EPD as SSD1681 (SPI)

    App->>Sensor: Wake & Sample Raw Telemetry
    Sensor-->>App: Return 16-bit Temp & RH + CRC
    App->>EPD: Blit Buffer to Screen RAM
```

---

## 3. Alerts (Callouts)

Alerts render styled admonition blockquotes with icons and colors.

```markdown
> [!NOTE]
> Highlights useful information or passive contextual notes.

> [!TIP]
> Helpful advice, optimizations, or shortcuts.

> [!IMPORTANT]
> Key information required to proceed or avoid common pitfalls.

> [!WARNING]
> Urgent info advising against risky behavior or broken states.

> [!CAUTION]
> Negative consequences of an action, such as data loss or irreversible commands.
```

### Formatting Invariants:
1. The opening line must strictly start with `> [!TYPE]` with **no spaces before the `>`** and exactly one space before `[!`.
2. Subsequent lines in the callout must begin with `> `.

---

## 4. Tables & Alignment

Tables require header dividers using pipes `|` and hyphens `-`. Colons indicate column alignment:

```markdown
| Peripheral | Bus / Protocol | Pin / Address | Mode / Clock |
| :--------- | :------------: | ------------: | ------------ |
| SSD1681    | SPI2 Master    |       GPIO 10 | 20 MHz       |
| SHTC3      | I2C0           |          0x70 | 400 kHz      |
| PCF85063A  | I2C0           |          0x51 | 400 kHz      |
```

- `:---` left aligns.
- `:---:` center aligns.
- `---:` right aligns.

---

## 5. Collapsible HTML Blocks (`<details>`)

When embedding collapsible blocks, standard HTML `<details>` and `<summary>` tags must be followed by a blank line before Markdown parsing can occur:

```markdown
<details>
<summary>Click to expand technical register table</summary>

A blank line **must** follow the `</summary>` tag for internal markdown to parse.

| Register | Address | Default |
|---|---|---|
| `CTRL_1` | `0x00`  | `0x00`  |

</details>
```

---

## 6. Pre-Commit Verification Checklist

Whenever editing or adding Markdown files, verify:
- [ ] No single-line `$$formula$$` block equations exist; all display math blocks are multi-line with blank line padding.
- [ ] No `$ formula $` exists with interior space adjacent to `$`.
- [ ] All Mermaid subgraphs have explicit alphanumeric IDs: `subgraph ID ["Label"]`.
- [ ] All Mermaid node labels with special characters are wrapped in double quotes `["..."]`.
- [ ] All callouts use canonical `> [!TYPE]` headers.
- [ ] Blank lines exist after all closing `</summary>` or `</div>` tags before Markdown resumes.
