---
name: breadboard-teaching
description: >-
  Teach robot_lab embedded projects using MB102 coordinate maps (a–j rows 1–65),
  ESP32 @ b2, atomic current/code traces, and per-project board files. Use when
  wiring, debugging circuits, explaining firmware, completing P1–P20, updating
  project guides, or when the user mentions breadboard coordinates, sơ đồ board,
  or wants tường tận / nguyên tử understanding.
---

# Breadboard-coordinated teaching (robot_lab)

## Collaboration contract

| Role | Responsibility |
|------|----------------|
| **Student** | Reports exact coordinates (`a5`, `j33`, jumper colors), symptoms, photos |
| **Professor (agent)** | Maintains board map, validates topology, explains atomically, updates `boards/pNN.md` |

**Shared source of truth:** `docs/project-guides/boards/pNN.md` + section **Board map** in `pNN-*.html` — not chat memory alone. MB102 structure sample: `breadboard-diagram.html`.

## When starting or continuing any project P1–P20

1. Read `docs/project-guides/boards/pNN.md` (create if missing from template).
2. Open or update section **Board map** in `docs/project-guides/pNN-*.html` (call `RobotLabBreadboard.render()` with project `wiring`).
3. Cross-check `src/main.cpp` GPIO numbers vs board coordinates (`b5` = D2, `b10` = D18).
4. On wiring changes, update board file **before** declaring "done".

## Board coordinate system (fixed for this repo)

- **ESP32 DevKit V1 (30 pin)** straddles trench: left pins @ column **`b`**, right @ **`i`**, rows **2–16**, **3V3 @ b2**, USB up.
- **Main grid:** 65 rows × `a–e` | rãnh | `f–j`.
- **Rails:** vertical clusters 10×(5 holes), red `+` / blue `−` on both sides — disconnected between clusters.
- **Same row + same half** (a–e or f–j) = electrically connected.

Pin map: see [reference.md](reference.md).

## Per-project board file template

Create `docs/project-guides/boards/pNN-short-name.md`:

```markdown
# PNN — [title]

## Parts on board
| Part | Coordinates | Notes |
|------|-------------|-------|

## Jumpers
| Color | From | To | Signal |
|-------|------|-----|--------|

## Atomic path (current when active)
1. ...

## Firmware ↔ hardware
| Code symbol | GPIO | Board coord | Effect |

## Gotchas
- ...
```

## Teaching: atomic trace (required for code + hardware)

Explain like debugging a request through layers — one causal chain, no hand-waving.

**Order:** code line → GPIO register → voltage at coord → current path → component behavior.

### Template (use in chat)

```
## Atomic trace — [action, e.g. "button press → LED on"]

1. **Code:** `digitalRead(18)` in loop — CPU asks GPIO18 input latch
2. **GPIO:** D18 @ b10 — internal pull-up holds ~3.3V (HIGH) when open
3. **Wire:** nâu b10 → … → d33 (nút cực 3–4, hàng 33 trái)
4. **Button:** bấm nối cực hàng 30 ↔ cực hàng 33 → d33 kéo về GND (LOW)
5. **Code:** debounce 40ms → `buttonState == LOW` → `ledOn = !ledOn`
6. **Code:** `digitalWrite(2, HIGH)` — GPIO2 output driver ON
7. **GPIO:** D2 @ b5 → vàng → a27 → d27 → [R] → h27 → LED+ j27
8. **Current:** 3.3V → R → LED → GND (cam → j30) — dòng ~5–10mA, LED sáng
```

SaaS analogy only when it clarifies: `GPIO` ≈ file descriptor; `pinMode` ≈ bind socket; `loop()` ≈ single-threaded poll loop.

## Wiring validation checklist

Before closing a wiring issue:

- [ ] Every signal has **both** origin coord and destination coord
- [ ] **GND common** between ESP32, LED, button, sensors
- [ ] LED has **series resistor** (not parallel)
- [ ] **4-pin button:** never D18 + GND on same row left/right (d30+g30 short internally); use **opposite terminals** (e.g. GND hàng 30 phải, D18 hàng 33 trái)
- [ ] Continuity test described: không bấm / có bấm

## Updating the HTML diagram

- Widget: `breadboard-widget.js` + `breadboard-widget.css`
- Sample grid (no wiring): `breadboard-diagram.html`
- Per project: section **Board map** in `pNN-*.html` — `wiring` keys `"rowCol"` lowercase (`"33d"`)
- Color classes: `w-cam`, `w-vang`, `w-nau`, `part-r`, `part-led`, `part-btn`, `problem`
- Link `boards/pNN.md` from project guide; link `breadboard-diagram.html` for MB102 structure only

## Do not

- Debug wiring from prose only when user has coords — always map to grid
- Suggest GPIO 23 if repo standard is D2 @ b5 unless student explicitly moves wire
- Explain variables/loops/git — owner is senior dev (see AGENTS.md)

## Additional resources

- [reference.md](reference.md) — ESP32 row map, button internal topology, MB102 rules
