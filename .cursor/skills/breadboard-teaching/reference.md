# Breadboard teaching — reference

## ESP32 @ b2 (rows 2–16)

| Row | b (left) | i (right) |
|-----|----------|-----------|
| 2 | 3V3 | VIN |
| 3 | GND | GND |
| 4 | D15 | D13 |
| 5 | D2 | D12 |
| 6 | D4 | D14 |
| 7 | RX2 | D27 |
| 8 | TX2 | D26 |
| 9 | D5 | D25 |
| 10 | D18 | D33 |
| 11 | D19 | D32 |
| 12 | D21 | D35 |
| 13 | RX0 | D34 |
| 14 | TX0 | VN (input only) |
| 15 | D22 | VP (input only) |
| 16 | D23 | EN |

Code `LED_PIN = 2` → coord **b5**. `BUTTON_PIN = 18` → **b10**.

## MB102 connectivity

| Same node | Rule |
|-----------|------|
| `a27` = `b27` = … `e27` | Same row, left half |
| `f27` = … `j27` | Same row, right half |
| `e27` ≠ `f27` | Trench isolates |
| Resistor `d27–h27` | Bridges trench (OK) |
| Rail `−` blue | Vertical 5-hole clusters; gaps between clusters |

## 4-pin tactile button (across trench)

```
    d30 | g30     row 30   ← pins 1 | 2  (cực A — luôn thông trái↔phải hàng 30)
    d33 | g33     row 33   ← pins 3 | 4  (cực B — luôn thông trái↔phải hàng 33)
```

- **Bấm:** cực A ↔ cực B (hàng 30 ↔ hàng 33)
- **Sai:** D18 @ hàng 30 trái + GND @ hàng 30 phải → luôn SHORT qua nút
- **Đúng (P3):** GND @ hàng 30 phải (`g30`/`j30`) · D18 @ hàng 33 trái (`d33`/`a33`)

## Atomic layers (mental model for senior dev)

| Layer | Embedded | SaaS debug analog |
|-------|----------|-------------------|
| 1 | `loop()` calls | Request handler entry |
| 2 | `digitalRead`/`Write` | Syscall |
| 3 | GPIO peripheral | Driver / kernel |
| 4 | Copper wire | Network hop |
| 5 | Component physics | Downstream service |

## Jumper color convention (this lab)

| Color | Typical use in session |
|-------|------------------------|
| Cam | GND |
| Vàng | D2 / signal |
| Nâu | D18 |

Not mandatory — always confirm with student's report.
