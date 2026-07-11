# Board maps — tọa độ breadboard theo project

**Hợp đồng tác chiến:** mỗi project P1–P20 có file `pNN.md` ở đây + section **Board map** trong `pNN-*.html` tương ứng.

Sơ đồ MB102 chung (grid trống): [breadboard-diagram.html](../breadboard-diagram.html).

## Quy ước tọa độ

- Cột: `a`–`e` (trái rãnh) · `f`–`j` (phải rãnh)
- Hàng: **1–65** (vùng giữa MB102)
- ESP32 cố định: **3V3 @ b2**, USB hướng lên; chân trái `b`, phải **`j`**, hàng 2–16. Jumper tới GPIO phải → **cột j** (cột `i` bị board che).
- Ghi jumper: `màu từ → đến` (vd `vàng b5 → a27`)

## Files

| Project | Board spec (text) | HTML (sơ đồ tương tác) |
|---------|-------------------|--------------------------|
| P6 | [p06.md](p06.md) | [p06-cam-bien-anh-sang.html](../p06-cam-bien-anh-sang.html#board-map) |
| P5 | [p05.md](p05.md) | [p05-bien-tro-led.html](../p05-bien-tro-led.html#board-map) |
| P4c | [p04c.md](p04c.md) | [p04c-lm393-phat-hien-vat.html](../p04c-lm393-phat-hien-vat.html#board-map) |
| P4b | [p04b.md](p04b.md) | [p04b-pir-bao-dong.html](../p04b-pir-bao-dong.html#board-map) |
| P4 | [p04.md](p04.md) | [p04-breathing-led.html](../p04-breathing-led.html#board-map) |
| P3 | [p03.md](p03.md) | [p03-nut-bat-tat-led.html](../p03-nut-bat-tat-led.html#board-map) |
| P2 | *(TODO)* | — |

## Template project mới

1. Copy [p03.md](p03.md) → `pNN.md`, cập nhật tọa độ.
2. Trong `pNN-*.html`: thêm section **Board map**, gọi `RobotLabBreadboard.render()` với `espPins` + `wiring` (xem P3).
3. Widget dùng chung: `breadboard-widget.js` + `breadboard-widget.css`.

Skill agent: `.cursor/skills/breadboard-teaching/SKILL.md`
