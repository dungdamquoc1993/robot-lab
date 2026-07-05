# AGENTS.md — robot_lab

Context for AI assistants working in this repo (equivalent to CLAUDE.md).

## Owner profile

| Area | Level |
|------|--------|
| Software (Python, TypeScript, Go) | ~5 years, SaaS |
| Embedded / electronics / robotics | Beginner |
| C++ firmware | Beginner (Arduino-style via PlatformIO) |

**Implication:** Explain hardware, MCU constraints, and embedded idioms. Do **not** explain programming basics, CLI, git, HTTP, or "what is a variable."

## Communication style

- Concise, accurate, assume senior-dev literacy
- Diagrams / pin tables for wiring; spec sheets over hand-waving
- When introducing embedded concepts, one clear sentence + optional SaaS analogy
- Vietnamese is fine for docs and chat if the user writes in Vietnamese

## Teaching contract (professor ↔ student)

**Shared truth:** breadboard coordinates + atomic traces — not chat-only memory.

| Deliverable | Location |
|-------------|----------|
| Per-project board map | `docs/project-guides/boards/pNN.md` |
| Interactive grid | Section **Board map** in `docs/project-guides/pNN-*.html` (widget: `breadboard-widget.js`) |
| MB102 sample (empty grid) | `docs/project-guides/breadboard-diagram.html` |
| Agent skill | `.cursor/skills/breadboard-teaching/SKILL.md` |

**When teaching or debugging P1–P20:**

1. Maintain/update board map with exact coords (`b5`, `j33`, jumper colors).
2. Explain **atomically:** code line → GPIO → coord → current path → component (like tracing a Python request through layers).
3. Student reports coords + symptoms; agent validates topology before blaming code.

**ESP32 fixed on board:** 3V3 @ **b2**, left pins column **b**, right column **i**, rows 2–16 (see `boards/README.md`).

## Toolchain

- **Editor:** Cursor only — no separate IDE
- **Build / upload:** PlatformIO CLI (`pio run`, `pio run -t upload`, `pio device monitor`)
- **Do not recommend:** Arduino IDE, PlatformIO VS Code/Cursor extension (unreliable in Cursor)
- Board: ESP32 DevKit V1 (CP2102 USB-UART)
- Port example: `/dev/cu.usbserial-0001` (auto-detect usually works)

## Repo layout

```
robot_lab/
├── AGENTS.md           ← this file
├── platformio.ini      ← board config
├── src/main.cpp        ← active firmware
├── docs/
│   ├── roadmap.md      ← milestones M0–M9 (no time estimates)
│   ├── projects.md     ← P1–P20 checklist
│   ├── foundations.md  ← embedded concepts reference
│   ├── setup-cli.md    ← PlatformIO CLI setup
│   ├── project-guides/ ← HTML guides + breadboard-diagram.html
│   │   └── boards/     ← pNN.md coordinate maps per project
│   └── inventory/      ← parts list + photos
```

## Learning model

- **Project-based:** P1 Blink → … → P20 robot + backend
- **Milestone gates** in `docs/roadmap.md` — don't skip GPIO/PWM/servo before robot chassis
- M4 is last milestone completable with current parts inventory

## Code conventions

- Firmware in `src/main.cpp` (PlatformIO Arduino framework)
- Prefer minimal diffs; no over-engineering
- Comments only for non-obvious hardware timing / pin choices
- After each project: note GPIO pins, libraries, gotchas (template in `docs/projects.md`)

## Hardware safety (always mention when wiring)

- ESP32 GPIO: **3.3V logic** — do not drive 5V into pins
- Servo SG90: **5V power**, shared GND with ESP32; don't power 2 servos from board 3.3V rail
- LED: always series resistor (220Ω typical from kit)

## Current status

- M0: done (PIO, Blink upload, breadboard, DT9205A)
- P1 Blink: onboard LED (GPIO 2) — done (2026-07-04)
- P2 LED + điện trở: breadboard — done
- P3 Nút bật/tắt LED: in progress / wiring validated (board map: `boards/p03.md`)
