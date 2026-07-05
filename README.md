# robot_lab

Embedded & robotics lab — project-based learning on ESP32.

**Background:** Experienced SaaS developer (Python, TypeScript, Go). New to electronics and firmware — docs assume you can code, not that you've never seen a terminal.

## Bắt đầu ở đâu

1. **Mốc 0:** [PlatformIO CLI](docs/setup-cli.md) — build & upload từ terminal Cursor
2. [Inventory](docs/inventory/inventory.md) — linh kiện hiện có
3. [Roadmap](docs/roadmap.md) — thứ tự milestone M0→M9
4. [Projects](docs/projects.md) — P1–P20, tick khi xong
5. [Foundations](docs/foundations.md) — tra cứu khái niệm embedded

## Cấu trúc

| Path | Nội dung |
|------|----------|
| `src/main.cpp` | Firmware đang active |
| `platformio.ini` | Board / port / monitor config |
| `docs/setup-cli.md` | CLI workflow |
| `docs/inventory/` | Parts + photos |
| `docs/roadmap.md` | Milestones |
| `docs/projects.md` | Project checklist |
| `AGENTS.md` | Context cho AI (Cursor / agents) |

## Workflow

```bash
pio run -t upload      # deploy firmware
pio device monitor     # serial output (Ctrl+C before re-upload)
```

## Nguyên tắc

- Đi đúng thứ tự project — dependency là hardware + firmware concepts, không phải syntax
- Ghi chú pin GPIO / lỗi sau mỗi project
- Không nhảy M7 (robot xe) trước khi xong servo + Wi-Fi (M3–M4)
