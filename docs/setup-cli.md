# Mốc 0 — Cursor + PlatformIO CLI (không cần IDE riêng)

Bạn **không cần Arduino IDE**. Chỉ cần phần mềm **biên dịch + nạp firmware** vào ESP32 — gọi chung là **toolchain**.

```
Cursor                    ← sửa code (IDE duy nhất)
Terminal (pio)            ← build + upload + serial monitor
    ├── compiler          ← biên dịch C++ → firmware
    ├── esptool           ← ghi firmware vào flash ESP32
    └── arduino-esp32     ← thư viện GPIO, delay, WiFi…
```

Arduino IDE / PlatformIO extension chỉ là **giao diện** bọc sẵn các tool trên. **CLI làm đúng việc đó**, không thêm app.

---

## Cài PlatformIO CLI (1 lần)

Trong terminal Cursor (`Ctrl + \``):

```bash
pip3 install --user platformio
```

Thêm `pio` vào PATH (chạy 1 lần, hoặc dán vào `~/.zshrc`):

```bash
echo 'export PATH="$HOME/Library/Python/3.9/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

Kiểm tra:

```bash
pio --version
```

---

## Upload P1 Blink

1. Cắm ESP32 USB  
2. Trong thư mục `robot_lab`:

```bash
pio run              # biên dịch
pio run -t upload    # nạp lên board
pio device monitor   # xem log serial (Ctrl+C thoát)
```

Lần đầu `pio run` tự tải compiler + esp32 board (~ vài trăm MB). Lần sau nhanh hơn.

LED nhỏ trên board nháy = **Mốc 0 xong**.

---

## Không thấy cổng USB?

```bash
pio device list
```

Không có device → cài driver **CP210x** hoặc **CH340** (tùy chip USB trên board ESP32).

---

## Cấu trúc code trong repo

```
robot_lab/
├── platformio.ini     ← cấu hình board ESP32
├── src/main.cpp       ← code firmware (P1 Blink…)
└── sketches/          ← bản .ino tham khảo (không bắt buộc)
```

Sửa `src/main.cpp` trong Cursor → chạy `pio run -t upload` trong terminal.

---

## So sánh nhanh

| | Arduino IDE | PlatformIO CLI |
|---|---|---|
| IDE riêng | Có | **Không** — dùng Cursor |
| Cài gì | 1 app + board package | `pip install platformio` |
| Upload | Nút → | `pio run -t upload` |
| Phù hợp | Người thích GUI | **Dev quen terminal** |

**arduino-cli** cũng được (công cụ dòng lệnh chính thức của Arduino) — tương đương, khác cú pháp. Repo này dùng **PlatformIO CLI** vì đã có `platformio.ini`.

---

## Gỡ extension PlatformIO trong Cursor

Extension hay lỗi, **không cần thiết** khi dùng CLI. Có thể Disable/Uninstall cho gọn.
