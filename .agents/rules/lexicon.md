# Engineering Nomenclature & Technical Lexicon Policy

This rule establishes strict terminology guidelines for all code, architecture documents, commit messages, and agent responses in the **H1OS** project.

## Disciplinary Grounding

We adhere strictly to professional **Embedded Systems Hardware and Software Engineering** standards. 

Military, tactical, paramilitary, and combat colloquialisms are strictly prohibited. Always replace informal jargon with standard IEEE, ISO/IEC, and semiconductor industry nomenclature.

---

## Approved Engineering Vocabulary Mapping

| Avoid (Military / Tactical Jargon) | Required Embedded Engineering Term | Engineering Context |
| :--- | :--- | :--- |
| **stand-down / stand down** | **sleep transition / power down / suspend** | Transitioning the SoC or peripherals into deep sleep or low-power state. |
| **sentinel / sentry / bouncer** | **monitor / supervisor / watchdog** | Coprocessor, task, or interrupt handler overseeing events or state. |
| **tripwire** | **threshold / limit trigger / brownout detector** | Voltage, thermal, or timer boundary triggering a state transition. |
| **sortie / mission / patrol** | **session / cycle / execution pass / sprint** | Sensor acquisition pulse or FreeRTOS task execution window. |
| **recon / reconnaissance** | **probing / polling / scanning / telemetry query** | Checking bus lines, I2C discovery, or sensor interrogation. |
| **payload** | **data buffer / telemetry frame / sample packet** | Sensor reading struct, ring buffer element, or network transmission. |
| **scaffold purge** | **refactoring / pruning / deprecation / removal** | Deleting obsolete legacy code and stubs. |
| **neutralize** | **clear / discharge / de-energize / reset** | Clearing display RAM, resetting DC bias, or de-asserting GPIO rails. |
| **kill / terminate (non-POSIX)** | **halt / disable / abort / power cut** | Graceful shutdown or gate de-assertion. |
| **fallback / fall back** | **default / recovery mode / safe state** | Fault handling logic. |

---

## Technical Authoring Invariants

1. **Physical Accuracy:** Describe electrical and thermodynamic phenomena using exact physics terms (e.g., *quiescent current leakage*, *parasitic conduction*, *thermal gradient*, *die self-heating*, *open-drain pull-up*).
2. **Deterministic States:** Refer to state machine phases by their explicit functional names: *Flow A (Headless Sensor Sprint)*, *Flow B (Interactive UI Session)*, *Deep Sleep Standby*, *Storage Power-Off*.
3. **Hardware Registers & Signals:** Use explicit IC pin and register nomenclature per manufacturer datasheets (e.g., `ESP_SLEEP_WAKEUP_EXT1`, `PCF85063A Control_2`, `BAT_CTRL`, `SSD1681 Deep Sleep Mode 1`).

---

## The Tone & Professionalism Clause ("Karen Clause")

To ensure an unassailably professional, objective, and safe engineering environment, all documentation, comments, commit messages, and agent outputs must strictly avoid language that could be misconstrued as aggressive, malicious, confrontational, or ideological:

1. **Prohibit Hostile & Aggressive Phrasing:**
   - Avoid violent, adversarial, or destructive idioms (e.g., *"nuke"*, *"blow away"*, *"destroy"*, *"wipe out"*, *"strangle"*, *"kill with prejudice"*). Use standard engineering equivalents (*"reset"*, *"erase"*, *"clear"*, *"deprecate"*, *"abort"*).
2. **No Manifesto-Style Prose:**
   - Do not write ideological declarations, polemics, grandiloquent treatises, or self-righteous philosophical rants.
   - Maintain a neutral, matter-of-fact, dispassionate tone focused purely on empirical measurement, circuit schematics, system architecture, and API contracts.
3. **Eliminate Provocative or Threatening Metaphors:**
   - Any turn of phrase that could remotely be perceived as hostile, ominous, punitive, or legally risky is forbidden.
   - Code reviews, architectural errata, and lessons-learned records must document technical deficiencies objectively without derogatory characterizations, personal blame, or accusatory language.
