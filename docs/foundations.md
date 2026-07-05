# Nền tảng kiến thức

12 nhóm kiến thức cơ bản — học **qua project**, không cần học hết trước khi cắm dây. Tra bảng này khi gặp khái niệm mới trong [projects.md](projects.md).

| Nhóm | Cần hiểu đến mức nào | Khái niệm | Project liên quan |
|------|----------------------|-----------|-------------------|
| Nguồn điện DC | Biết 3.3V, 5V, 12V khác nhau; không cắm nhầm nguồn vào ESP32 | Voltage, Current, GND | P1 |
| Điện trở & LED | Biết vì sao LED cần điện trở; đọc giá trị điện trở cơ bản | Resistance, Ohm's Law | P2 |
| GPIO digital | Bật/tắt chân ESP32: HIGH/LOW | GPIO, digital output | P1, P3 |
| Input / nút bấm | Đọc nút, pull-up/pull-down, chống nhiễu đơn giản | Button, input, debounce | P3 |
| PWM | "Giả lập analog" bằng bật/tắt nhanh; điều sáng/tốc độ/góc servo | PWM | P4, P7, P10, P12 |
| ADC | Đọc tín hiệu analog từ biến trở / cảm biến | ADC | P5, P6 |
| DAC | ESP32 xuất mức analog đơn giản ở vài chân | DAC | (mở rộng sau) |
| Transistor / MOSFET | Tín hiệu 3.3V điều khiển tải lớn (motor, LED strip) | Transistor, MOSFET | P13 |
| Động cơ | Khác nhau giữa DC motor, servo, stepper | DC Motor, Servo, Stepper | P7, P11, P15 |
| Feedback | Encoder là "mắt đo chuyển động" của motor | Encoder | P16, P17 |
| Nguồn pin | Li-ion/LiPo nguy hiểm nếu sạc sai; BMS bảo vệ pin | Pin Li-ion, BMS | P18 |
| Nguồn switching | Buck converter hạ 12V/7.4V xuống 5V/3.3V | Switching regulator | P18 |

## Cách dùng tài liệu này

1. Làm project → gặp khái niệm lạ → quay lại dòng tương ứng.
2. Không cần thuộc lòng — chỉ cần **giải thích lại được bằng lời** sau khi làm xong project.
3. Nhóm DAC, MOSFET, Encoder, PID sẽ tự "ngấm" khi tới mốc motor & robot — chưa cần học sớm.

---

## Breadboard MB102

Breadboard = bảng cắm tạm: **không hàn**, cắm dây/linh kiện vào lỗ. Bên dưới mỗi lỗ có clip kim loại — clip nối các lỗ với nhau theo quy tắc cố định (bạn không nhìn thấy, phải học hoặc đo continuity).

Ảnh board trong kit: [breadboard-mb102.jpg](inventory/photos/breadboard-mb102.jpg)

### Cấu trúc (nhìn từ trên — đúng với MB102 của bạn)

```
  bus TRÁI (+/−)     vùng giữa (cột 1…60)        bus PHẢI (+/−)
 ┌─ + ─ + ─┐    a b c d e ║ f g h i j    ┌─ + ─ + ─┐
 │ đỏ  xanh│    ●●●●● 10  ║  ●●●●● 10     │ đỏ  xanh│
 │         │    (a10↔e10 nối) ║ (f10↔j10)  │         │
 └─ − ─ − ─┘    ↑ cùng cột ↑  rãnh         └─ − ─ − ─┘
                      (a–e không nối f–j)
```

| Vùng trên board | Quy tắc nối (ẩn bên trong) |
|-----------------|----------------------------|
| **Hàng `+` / `−`** (sát mép trên & dưới) | Mỗi **hàng ngang** dài nối liền — ví dụ cả hàng `+` bên trái là một rail |
| **Cột giữa** (số 1–60, chữ a–e hoặc f–j) | **5 lỗ cùng cột** trong nửa a–e nối nhau: `a10`–`e10` = 1 điểm; `f10`–`j10` = 1 điểm khác |
| **Rãnh giữa** (khe ngang) | Tách nửa a–e khỏi f–j — dùng khi cắm IC dạng DIP hai hàng chân |

**Gotcha MB102:** hàng nguồn `+`/`−` thường **bị đứt ở giữa** (quanh cột ~30 — vạch đỏ/xanh không chạy xuyên suốt). Nửa trái và nửa phải **không** tự nối — nếu cần GND/3.3V cả hai bên, cắm thêm **dây nối** giữa hai nửa rail.

**ESP32 DevKit:** thường **đặt cạnh** breadboard, nối bằng **dây jumper** (đầu cá/s đực) — không cắm cả board ESP32 xuống lỗ (board rộng, chân sát nhau).

**SaaS analogy:** mỗi cột a10–e10 ≈ một “socket” nội bộ; rail `+`/`−` ≈ bus nguồn — nhưng nhớ rail có thể **đứt đôi** ở giữa.

### Làm quen — 10 phút, chỉ cần dây jumper + đồng hồ

Không cần ESP32. Mục tiêu: mắt nhìn lỗ ↔ biết điểm nào nối điểm nào.

| # | Làm | Continuity kêu? | Học được |
|---|-----|-----------------|----------|
| 1 | Cắm 2 dây: `c10` và `e10` (cùng cột 10) | Có | Cùng cột a–e = nối |
| 2 | Giữ một dây ở `c10`, dời dây kia sang `c11` | Không | Khác cột = node khác |
| 3 | Một dây `c10`, dây kia `f10` (cùng số cột, qua rãnh) | Không | Rãnh tách a–e / f–j |
| 4 | Hai dây cùng hàng `−` xanh bên trái, xa nhau | Có | Rail ngang nối dọc theo hàng |
| 5 | Một dây rail `−` trái cột 5, dây kia rail `−` trái cột 35 | Thường **không** | Rail đứt giữa — cần jumper nếu muốn nối |

Xong bảng trên → tick M0 “Hiểu breadboard” trong [roadmap.md](roadmap.md).

### Cắm mạch P2 — LED ngoài (sau khi làm quen)

ESP32 đặt bàn; dây jumper từ board sang breadboard:

```
ESP32                    breadboard
GPIO (vd 4) ──dây──►  cột 10 (a10 hoặc b10… đều được)
                           │
                      [220Ω] giữa cột 10 ↔ cột 15
                           │
                      LED chân dài (+) cột 15
                      LED chân ngắn (−) cột 20 ──dây──► rail − (GND)
GND ESP32 ──dây──► rail − (cùng rail với LED)
```

- **Chân dài LED (+)** qua điện trở về GPIO; **chân ngắn (−)** về GND.
- **GND ESP32** và **rail `−`** phải nối chung.
- GPIO: **3.3V logic** — không cấp 5V vào chân GPIO.

---

## Đồng hồ vạn năng DT9205A

Đồng hồ trong kit: **ANENG DT9205A**. Luôn bắt đầu bằng **tắt nguồn mạch / rút USB** khi đo Ω hoặc continuity (tránh đo nhầm mạch đang cấp điện).

### Que đo

| Ổ cắm | Màu dây thường gặp | Dùng khi |
|-------|-------------------|----------|
| **COM** | Đen | Mọi chế độ |
| **VΩmA** | Đỏ | Đo V, Ω, continuity (dòng nhỏ) |

### Ba chế độ cần trước P3

| Chế độ (vặn núm) | Ký hiệu | Dùng để |
|------------------|---------|---------|
| **Continuity** | 🔊 / diode | Kiểm tra 2 điểm có nối không — **kêu** = dẫn |
| **Resistance** | **Ω** (200 / 2k / …) | Đo giá trị điện trở (220Ω, 330Ω, …) |
| **DC Voltage** | **V⎓** (20V) | Đo áp DC: pin, chân 3.3V ESP32 |

Chọn dải đo **lớn hơn** giá trị kỳ vọng (đo 3.3V → dải 20V DC; đo 220Ω → dải 200Ω hoặc 2kΩ).

### Luyện tay (theo thứ tự)

**1. Continuity — breadboard (ESP32 rút USB)**

- Que COM + VΩm chạm hai lỗ cùng hàng → kêu.
- Chạm hai hàng khác số → im.
- Mục tiêu: mắt nhìn breadboard khớp với “node nào nối node nào”.

**2. Đo Ω — điện trở rời (ESP32 rút USB)**

- Chạm hai chân điện trở **220Ω** (không cần breadboard).
- Kit 600 chiếc thường ±5% — đọc ~210–230 là bình thường.
- Thử 330Ω, 1kΩ — số lớn hơn → dòng qua LED nhỏ hơn (P2).

**3. Đo V DC — ESP32 cắm USB, chưa cắm LED**

- COM → **GND** board; đỏ → chân **3V3** (hoặc 3.3V).
- Kỳ vọng ~3.2–3.4 V — xác nhận rail nguồn trước khi cắm linh kiện.

**4. Đo V khi Blink (tuỳ chọn, nâng cao)**

- Firmware P1 đang nháy GPIO 2: đo GPIO 2 ↔ GND.
- HIGH ≈ 3.3 V, LOW ≈ 0 V — thấy nhảy số = `digitalWrite` thật sự kéo chân.
- Que đo chạm **chân GPIO**, không chạm LED onboard (LED onboard nối nội bộ, khó tách đo).

### An toàn nhanh

- **Không** đo Ω / continuity trên mạch đang bật.
- **Không** đo AC / socket 220V — chưa cần cho robot_lab.
- Pin cạn → thay; đo sai dải → đổi sang 200Ω / 20V DC.

Xong bài 1–3 → tick M0 “Biết dùng DT9205A” trong [roadmap.md](roadmap.md).
