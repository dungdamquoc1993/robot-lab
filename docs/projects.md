# Danh sách project

Học lý thưởng như hiệu ứng phụ — mỗi project dạy một (hoặc vài) khái niệm trong [foundations.md](foundations.md).

Guide HTML có ảnh linh kiện và các bước làm: [project-guides/index.html](project-guides/index.html)

**Trạng thái:** `[ ]` chưa làm · `[x]` hoàn thành · `[~]` đang làm

---

## Mốc 1 — GPIO & điện cơ bản

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P1 | [x] | Blink LED | ESP32 làm LED nháy | ESP32 *(LED onboard)* | GPIO, HIGH/LOW, 3.3V, GND |
| P2 | [ ] | LED + điện trở | Thử 220Ω, 330Ω, 1K — so sánh độ sáng | LED, set 600 điện trở | Resistance, dòng điện, Ohm |
| P3 | [ ] | Nút bật/tắt LED | Bấm nút → LED đổi trạng thái | Nút 12×12, LED, 220Ω | Input, pull-up, debounce |

---

## Mốc 2 — Analog I/O

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P4 | [x] | Breathing LED | LED sáng/tối mượt | LED, 220Ω | PWM |
| P5 | [~] | Biến trở → LED | Xoay núm → độ sáng thay đổi | Biến trở 10K, LED | ADC + PWM |
| P6 | [ ] | Cảm biến ánh sáng | Che/mở LDR, đọc giá trị Serial Monitor | Module quang trở | Voltage divider, ADC |

---

## Mốc 3 — Servo

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P7 | [~] | Servo + biến trở | Xoay núm → servo quay theo góc | SG90 ×1, biến trở 10K | PWM, servo control |
| P7b | [~] | Hai servo độc lập | Điều khiển 2 SG90 (2 chân PWM) | SG90 ×2 | Nguồn 5V, dòng tải |

> **P7b** là bài mở rộng tự đề xuất — dùng hết 2 servo đang có.

---

## Mốc 4 — Kết nối & hiển thị

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P8 | [x] | Web server | Điều khiển LED/servo từ điện thoại qua Wi-Fi | ESP32 | Wi-Fi, HTTP, IoT |
| P9 | [x] | OLED + sensor | Hiển thị nhiệt độ/ánh sáng lên OLED | OLED, DHT11 hoặc LDR | I2C, sensor data |
| P10 | [x] | Buzzer | Phát tiếng bíp / tone đơn giản | Buzzer thụ động hoặc hoạt động | PWM frequency |
| P14 | [ ] | Relay | ESP32 bật/tắt relay (nghe "tạch") | Module relay 2 kênh | Relay, isolation |

### Bài bổ sung (cùng mốc, dùng kit)

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần |
|----|------------|---------|----------|---------------|
| P4b | [ ] | PIR báo động | Phát hiện chuyển động → bật LED *(cần mua PIR)* | PIR HC-SR501, LED |
| P4c | [x] | LM393 phát hiện vật | Đọc module LM393, log khoảng cách/vật cản | Module LM393 |

---

## Mốc 5 — Motor & driver *(cần mua thêm)*

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P11 | [ ] | DC motor + driver | Motor chạy/dừng/đổi chiều | DC motor, L298N/TB6612 | Motor driver, dòng lớn |
| P12 | [ ] | PWM điều tốc motor | Slider web đổi tốc độ motor | DC motor, driver, ESP32 | PWM công suất |
| P13 | [ ] | MOSFET tải ngoài | ESP32 điều khiển LED strip / motor nhỏ | MOSFET module | Transistor, switching |

---

## Mốc 6 — Điều khiển chuyển động nâng cao *(cần mua thêm)*

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P15 | [ ] | Stepper motor | Quay chính xác 90°, 180° | Stepper + driver | Stepper, sequence |
| P16 | [ ] | Encoder | Đo tốc độ motor quay | Motor + encoder | Interrupt, feedback |
| P17 | [ ] | PID giữ tốc độ | Motor tự bù khi bị cản | Motor + encoder | Control loop, PID |

---

## Mốc 7 — Robot xe

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P18 | [ ] | Xe 2 bánh Wi-Fi | Điều khiển xe bằng điện thoại | Khung xe, 2× motor, driver, pin, buck | Power, motor, control |

---

## Mốc 8 — Robot tự hành

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P19 | [ ] | Tránh vật cản | Xe tự né vật | P18 + HC-SR04 hoặc LM393 | Sensor + decision |

---

## Mốc 9 — Robot + backend

| ID | Trạng thái | Project | Mục tiêu | Linh kiện cần | Khái niệm |
|----|------------|---------|----------|---------------|-----------|
| P20 | [ ] | Não Python / AI | ESP32 nhận lệnh từ server Python | P18/P19 + máy tính/server | Embedded + backend |

---

## Ghi chú sau mỗi project

Sao chép template này vào cuối file (hoặc tạo `docs/notes/`) khi hoàn thành:

```markdown
### P?. [Tên project] — [ngày]
- Chân GPIO: ...
- Thư viện Arduino: ...
- Lỗi gặp phải: ...
- Cách sửa: ...
- Điều muốn thử tiếp: ...
```

---

### P1 Blink LED — 2026-07-04
- Chân GPIO: **2** (LED onboard ESP32 DevKit)
- Thư viện Arduino: không (chỉ `Arduino.h`)
- Firmware: `digitalWrite` HIGH/LOW, `delay(2000)` — nháy 2 giây
- Lệnh: `pio run -t upload`
- Ghi chú: chưa dùng breadboard / LED ngoài — phần đó gộp vào **P2**
- Điều muốn thử tiếp: cắm LED + 220Ω trên breadboard; đo Ω và V bằng DT9205A

### P8 Web server — 2026-07-12
- Chân GPIO: **2** (LED onboard ESP32 DevKit); **18** chỉ là servo tùy chọn, lazy-init khi dùng slider.
- Thư viện Arduino: `WiFi.h`, `WebServer.h`.
- Firmware: AP mode `RobotLab-P8` / `robotlab8`, web UI tại `http://192.168.4.1`, route `/api/led` bật/tắt LED onboard.
- Lệnh: `pio run`, `pio run -t upload`.
- Ghi chú: breadboard trắng hoàn toàn; ESP32 rời breadboard, chỉ cắm USB. Điện thoại vào được Wi-Fi của ESP32 và mở được webserver.
- Điều muốn thử tiếp: P9 OLED + sensor, bắt đầu học I2C và hiển thị dữ liệu.

### P9 OLED + sensor — 2026-07-12
- Chân GPIO: **21** (SDA), **22** (SCK/SCL), **34** (LDR AO ADC input-only).
- Thư viện Arduino: `Wire.h`, `Adafruit_SSD1306.h`.
- Firmware: scan OLED I2C `0x3C/0x3D`, hiển thị `I2C`, `ADC`, `%` lên OLED; Serial vẫn log nếu OLED lỗi.
- Lệnh: `pio run`, `pio run -t upload`.
- Ghi chú: OLED address ổn định ở **0x3C**. LDR hở sáng khoảng **55%**, che hết lên **4095 / 100%**; module này cho ADC cao hơn khi tối.
- Điều muốn thử tiếp: P10 buzzer hoặc đảo cách hiển thị thành `% tối` / `% sáng` cho trực quan hơn.

### P10 Buzzer — 2026-07-12
- Chân GPIO: **25** (PWM tone output qua điện trở 220Ω).
- Thư viện Arduino: không thêm; dùng LEDC PWM của ESP32.
- Firmware: pattern 440Hz → 660Hz → 880Hz rồi nghỉ, lặp lại; Serial log từng tone.
- Lệnh: `pio run`, `pio run -t upload`.
- Ghi chú: breadboard bắt đầu trắng; ESP32 rời breadboard, buzzer đặt tại `e15/e20`, điện trở 220Ω `d10 → d15`. Buzzer kêu pattern “Bò / Be / Bíp” lặp lại đúng firmware.
- Điều muốn thử tiếp: đổi `PATTERN` thành melody ngắn hoặc dùng P8 webserver bật/tắt buzzer từ điện thoại.
