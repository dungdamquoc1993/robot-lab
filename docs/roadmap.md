# Lộ trình theo mốc

Đi **tuần tự từ Mốc 1 → 9**. Mỗi mốc có điều kiện hoàn thành — chỉ chuyển mốc khi đạt.

Chi tiết từng project: [projects.md](projects.md)  
Linh kiện hiện có: [inventory.md](inventory/inventory.md)

---

## Tổng quan

```
M1 GPIO & điện     →  M2 Analog I/O    →  M3 Servo
        ↓                                        ↓
M4 Kết nối & hiển thị  ←─────────────────────────┘
        ↓
M5 Motor & driver  →  M6 Điều khiển nâng cao
        ↓                        ↓
              M7 Robot xe  →  M8 Tự hành  →  M9 + AI
```

---

## Mốc 0 — Chuẩn bị môi trường

**Mục tiêu:** Nạp được code lên ESP32 và đo được mạch cơ bản.

| Việc cần làm | Xong? |
|--------------|-------|
| Cài **PlatformIO CLI** — xem [setup-cli.md](setup-cli.md) | [x] |
| `pio run -t upload` Blink thành công | [x] |
| Biết dùng DT9205A: continuity, đo Ω, đo V DC — xem [foundations.md § Đồng hồ](foundations.md#đồng-hồ-vạn-năng-dt9205a) | [x] |
| Hiểu breadboard: bus nguồn, hàng nối — xem [foundations.md § Breadboard](foundations.md#breadboard-mb102) | [x] |

**Điều kiện sang Mốc 1:** Nạp Blink mẫu thành công (hoặc tương đương).

---

## Mốc 1 — GPIO & điện cơ bản

**Mục tiêu:** Bật/tắt LED bằng code; hiểu điện trở và nút bấm.

| Project | |
|---------|---|
| P1 Blink LED | [x] |
| P2 LED + điện trở | [ ] |
| P3 Nút bật/tắt LED | [ ] |

**Điều kiện sang Mốc 2:**
- LED nháy và đổi trạng thái bằng nút ổn định
- Giải thích được vì sao LED cần điện trở

---

## Mốc 2 — Analog I/O

**Mục tiêu:** Đọc giá trị analog; xuất PWM mượt.

| Project | |
|---------|---|
| P4 Breathing LED | [x] |
| P5 Biến trở → LED | [~] |
| P6 Cảm biến ánh sáng | [ ] |

**Điều kiện sang Mốc 3:**
- Biến trở điều khiển độ sáng LED mượt
- Serial Monitor in giá trị LDR thay đổi khi che/sáng

---

## Mốc 3 — Servo

**Mục tiêu:** Điều khiển góc servo; hiểu nguồn 5V riêng.

| Project | |
|---------|---|
| P7 Servo + biến trở | [~] |
| P7b Hai servo độc lập | [~] |

**Điều kiện sang Mốc 4:**
- 1 servo quay theo biến trở không bị giật/reset board
- 2 servo chạy đồng thời với nguồn 5V phù hợp

---

## Mốc 4 — Kết nối & hiển thị

**Mục tiêu:** ESP32 nói chuyện Wi-Fi; hiển thị dữ liệu; actuator phụ (buzzer, relay).

| Project | Bắt buộc | Tuỳ chọn |
|---------|----------|----------|
| P8 Web server | [x] | |
| P9 OLED + sensor | [x] | |
| P10 Buzzer | [ ] | |
| P14 Relay | [ ] | |
| P4b PIR | | [ ] |
| P4c LM393 | | [x] |

**Điều kiện sang Mốc 5:**
- Điều khiển ít nhất 1 actuator (LED hoặc servo) từ trình duyệt điện thoại (P8)
- OLED hiển thị ít nhất 1 giá trị sensor (P9)

> **Mốc 4 là mốc cuối có thể hoàn thành 100% với linh kiện hiện tại.**

---

## Mốc 5 — Motor & driver

**Mục tiêu:** ESP32 điều khiển motor DC qua driver — không nối motor thẳng vào GPIO.

**Cần mua:** DC motor, motor driver (L298N/TB6612), nguồn phù hợp. Xem [inventory.md](inventory/inventory.md).

| Project | |
|---------|---|
| P11 DC motor + driver | [ ] |
| P12 PWM điều tốc | [ ] |
| P13 MOSFET *(tuỳ chọn)* | [ ] |

**Điều kiện sang Mốc 6:** Motor chạy/dừng/đổi chiều an toàn qua driver.

---

## Mốc 6 — Điều khiển chuyển động nâng cao

**Mục tiêu:** Quay chính xác, đo tốc độ, vòng lặp PID cơ bản.

**Cần mua:** Stepper + driver, encoder.

| Project | |
|---------|---|
| P15 Stepper | [ ] |
| P16 Encoder | [ ] |
| P17 PID | [ ] |

**Điều kiện sang Mốc 7:** Đo được tốc độ motor bằng encoder (P16).

> Có thể **bỏ qua Mốc 6** tạm thời và nhảy Mốc 5 → Mốc 7 nếu mục tiêu chính là robot xe, quay lại sau.

---

## Mốc 7 — Robot xe 2 bánh

**Mục tiêu:** Xe di chuyển, điều khiển qua Wi-Fi.

**Cần mua:** Khung xe, 2× motor, driver, pin Li-ion/LiPo, buck converter, sạc.

| Project | |
|---------|---|
| P18 Xe Wi-Fi | [ ] |

**Điều kiện sang Mốc 8:** Xe đi được 4 hướng (tiến, lùi, trái, phải) từ điện thoại.

---

## Mốc 8 — Robot tự hành

**Mục tiêu:** Xe tự quyết định né vật cản.

| Project | |
|---------|---|
| P19 Tránh vật cản | [ ] |

**Điều kiện sang Mốc 9:** Xe tự dừng hoặc rẽ khi phát hiện vật (LM393 hoặc HC-SR04).

---

## Mốc 9 — Robot + backend / AI

**Mục tiêu:** ESP32 nhận lệnh từ máy tính hoặc server Python.

| Project | |
|---------|---|
| P20 Não Python / AI | [ ] |

**Hoàn thành lộ trình:** Robot nhận lệnh từ backend, thực thi trên phần cứng P18/P19.

---

## Project tiếp theo (với linh kiện hiện tại)

```
M0 (breadboard + đồng hồ) → P2 → P3 → … → P7 → P8 → P9
```

> P1 (Blink onboard GPIO 2) đã xong. **Tiếp theo:** làm P2 trên breadboard — vừa cắm mạch vừa luyện đồng hồ theo [foundations.md](foundations.md).

Cập nhật checkbox trong [projects.md](projects.md) mỗi khi hoàn thành một project.
