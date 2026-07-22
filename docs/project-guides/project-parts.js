(() => {
  "use strict";

  const PHOTO = "../inventory/photos/";

  const catalog = {
    esp32: { name: "ESP32 DevKit V1", spec: "Board 30 chân, logic GPIO 3.3V", state: "owned", photo: "board-esp32-devkit-v1.jpg" },
    usb: { name: "Cáp USB Micro", spec: "Cáp có truyền dữ liệu, không chỉ sạc", state: "owned", photo: "cap-usb-micro.jpg" },
    breadboard: { name: "Breadboard MB102", spec: "Breadboard full-size", state: "owned", photo: "breadboard-mb102.jpg" },
    mb102Power: { name: "Module nguồn breadboard MB102", spec: "Đầu ra 5V/3.3V; không dùng cấp motor", state: "owned", photo: "module-nguon-breadboard-mb102.jpg" },
    multimeter: { name: "Đồng hồ DT9205A", spec: "Đo V DC, điện trở và continuity", state: "owned", photo: "multimeter-dt9205a.jpg" },
    led: { name: "LED 5mm", spec: "Đỏ/vàng/xanh, 2 chân", state: "owned", photo: "led-5mm-do-vang-xanh.jpg" },
    ledRgb: { name: "LED RGB 5mm", spec: "4 chân", state: "owned", photo: "led-rgb-5mm.jpg" },
    r220: { name: "Điện trở 220Ω", spec: "1/4W, nối tiếp LED/buzzer", state: "owned", photo: "set-dien-tro-600-metal-film.jpg" },
    r330: { name: "Điện trở 330Ω", spec: "1/4W", state: "owned", photo: "set-dien-tro-600-metal-film.jpg" },
    r1k: { name: "Điện trở 1KΩ", spec: "1/4W", state: "owned", photo: "set-dien-tro-600-metal-film.jpg" },
    r10k: { name: "Điện trở 10KΩ", spec: "1/4W", state: "owned", photo: "set-dien-tro-600-metal-film.jpg" },
    r20k: { name: "Điện trở 20KΩ", spec: "1/4W", state: "owned", photo: "set-dien-tro-600-metal-film.jpg" },
    button: { name: "Nút nhấn 12×12mm", spec: "Nút 4 chân kèm nắp", state: "owned", photo: "nut-bam-12x12-bien-tro-10k.jpg" },
    pot10k: { name: "Biến trở 10K", spec: "3 chân, trục xoay", state: "owned", photo: "bien-tro-10k.jpg" },
    ldr: { name: "Module quang trở LDR", spec: "VCC, GND, DO, AO", state: "owned", photo: "module-quang-tro-ldr.jpg" },
    dht11: { name: "Module DHT11", spec: "Cảm biến nhiệt độ/độ ẩm", state: "owned", photo: "module-dht11.jpg" },
    oled: { name: "OLED 0.96 inch I2C", spec: "GND, VDD, SCK, SDA", state: "owned", photo: "oled-096-inch-i2c.jpg" },
    buzzer: { name: "Buzzer thụ động", spec: "2 chân, điều khiển bằng PWM", state: "owned", photo: "buzzer-thu-dong-2chan.jpg" },
    relay: { name: "Module relay 2 kênh 5V", spec: "SONGLE SRD-05VDC-SL-C", state: "owned", photo: "module-relay-2-kenh-5v.jpg" },
    servo: { name: "Servo SG90", spec: "Nguồn 5V, signal PWM 3.3V", state: "owned", photo: "servo-sg90.jpg" },
    obstacleIr: { name: "Module tránh vật cản LM393 IR", spec: "VCC, GND, OUT", state: "owned", photo: "module-lm393-tranh-vat-can.jpg" },
    jumperMM: { name: "Dây jumper đực–đực", spec: "Dùng giữa các điểm breadboard", state: "owned", photo: "jumper-wires.jpg" },
    jumperMF: { name: "Dây jumper đực–cái", spec: "ESP32/module tới breadboard", state: "owned", photo: "jumper-wires.jpg" },
    jumperFF: { name: "Dây jumper cái–cái", spec: "Nối hai header đực", state: "owned", photo: "jumper-wires.jpg" },
    phone: { name: "Điện thoại có Wi‑Fi", spec: "Trình duyệt web cùng mạng/AP với ESP32", state: "owned" },
    computer: { name: "Máy tính", spec: "PlatformIO CLI và Python 3", state: "owned" },

    pir: { name: "PIR HC-SR501", spec: "Module 3 chân VCC/OUT/GND", state: "buy", search: "PIR HC-SR501" },
    chassisCombo: { name: "Combo khung xe 2WD motor TT", spec: "1 khung + 2 motor TT vàng 3–6V hai trục + 2 bánh + 1 caster + ốc", state: "buy", search: "combo khung xe robot 2WD motor TT 2 trục" },
    ttMotor: { name: "Motor TT giảm tốc 3–6V hai trục", spec: "Đã nằm trong combo khung; không mua rời nếu combo đủ", state: "included", search: "motor TT vàng 3V 6V hai trục" },
    tb6612: { name: "Module TB6612FNG", spec: "Breakout điều khiển 2 motor; VCC logic 3.3V", state: "buy", search: "module TB6612FNG điều khiển 2 động cơ" },
    encoderTt: { name: "Bộ encoder khe cho motor TT", spec: "Module cảm biến khe + đĩa encoder vừa trục sau motor TT", state: "buy", search: "encoder đo tốc độ motor TT đĩa khe LM393" },
    battery2s: { name: "Pack pin Li-ion 2S 7.4V", spec: "Đóng sẵn, có BMS; 2200mAh trở lên; dòng xả liên tục ≥5A", state: "buy", search: "pin lithium 2S 7.4V có BMS 2200mAh" },
    charger2s: { name: "Sạc Li-ion 2S 8.4V 1A", spec: "Đúng cực và đúng jack của pack pin", state: "buy", search: "sạc pin lithium 2S 8.4V 1A" },
    buckMotor: { name: "Buck XL4015 5A", spec: "Loại chỉnh áp có tản nhiệt; rail motor đặt 5.5–6.0V", state: "buy", search: "mạch hạ áp XL4015 5A có tản nhiệt" },
    buckLogic: { name: "Buck LM2596 3A", spec: "Loại chỉnh áp; rail ESP32 đặt 5.0V", state: "buy", search: "mạch hạ áp LM2596 3A điều chỉnh" },
    powerSwitch: { name: "Công tắc nguồn DC", spec: "ON/OFF 2 chân, chịu dòng tối thiểu 5A", state: "buy", search: "công tắc nguồn DC 2 chân 5A" },
    fuse: { name: "Đế cầu chì + cầu chì 5A", spec: "Loại mắc nối tiếp dây dương pack pin", state: "buy", search: "đế cầu chì dây 5A" },
    wire22: { name: "Dây điện silicone 22AWG", spec: "Tối thiểu 2m đỏ + 2m đen; không dẫn dòng motor qua Dupont", state: "buy", search: "dây điện silicone 22AWG đỏ đen" },
    terminal: { name: "Domino cầu đấu 2P 5.08mm", spec: "Đầu bắt vít phân phối nguồn", state: "buy", search: "domino cầu đấu 2P 5.08mm" },
    cap100n: { name: "Tụ gốm 100nF", spec: "Mã 104, ≥25V; gắn sát hai cực motor", state: "buy", search: "tụ gốm 104 100nF 50V" },
    cap470: { name: "Tụ hóa 470µF", spec: "Điện áp chịu đựng ≥16V", state: "buy", search: "tụ hóa 470uF 16V" },
    cap1000: { name: "Tụ hóa 1000µF", spec: "Điện áp chịu đựng ≥16V", state: "buy", search: "tụ hóa 1000uF 16V" },
    heatshrink: { name: "Ống co nhiệt", spec: "Bộ nhiều kích thước cho mối hàn nguồn/motor", state: "buy", search: "ống co nhiệt nhiều kích thước" },
    standoff: { name: "Bộ cọc đỡ nylon M3", spec: "Cọc, vít và đai ốc để cố định board", state: "buy", search: "bộ cọc đỡ nylon M3" },
    zipTie: { name: "Dây rút nhựa mini", spec: "Dài 100–150mm", state: "buy", search: "dây rút nhựa mini 100mm" },
    dupontSet: { name: "Bộ dây Dupont 3 loại", spec: "40 sợi mỗi loại đực–đực, đực–cái, cái–cái", state: "buy", search: "bộ dây Dupont 3 loại 40 sợi" },
    hcSr04: { name: "Cảm biến siêu âm HC-SR04", spec: "Bản 4 chân VCC/Trig/Echo/GND", state: "buy", search: "cảm biến siêu âm HC-SR04" },
    ultrasonicBracket: { name: "Giá đỡ HC-SR04 + SG90", spec: "Bộ gá tương thích servo SG90 hiện có", state: "buy", search: "giá đỡ HC-SR04 servo SG90" },
    stepperCombo: { name: "Combo stepper 28BYJ-48 5V + ULN2003", spec: "Đúng bản motor 5V; combo gồm motor và board driver", state: "buy", search: "28BYJ-48 5V kèm ULN2003" },
    mosfet: { name: "Module MOSFET D4184", spec: "Phải ghi rõ nhận trigger 3.3V", state: "buy", search: "module MOSFET D4184 trigger 3.3V" },
    diode: { name: "Diode Schottky 1N5819", spec: "Diode flyback nếu điều khiển tải cảm ứng và module chưa tích hợp", state: "buy", search: "diode 1N5819" },
    ledStrip: { name: "LED strip 5V", spec: "30 LED/m, đoạn 0.5–1m, loại thường không addressable", state: "buy", search: "LED dây 5V 30 LED mét" },
    soldering: { name: "Bộ dụng cụ hàn", spec: "Mỏ hàn chỉnh nhiệt, thiếc có flux, hút thiếc, kìm cắt/tuốt", state: "buy", search: "bộ mỏ hàn điều chỉnh nhiệt 60W" }
  };

  const P = (id, qty, note = "", state = "") => ({ id, qty, note, state });

  const projects = {
    "p01-blink-led.html": { summary: "ESP32 ×1 · cáp USB ×1", items: [P("esp32", 1), P("usb", 1), P("computer", 1)] },
    "p02-led-dien-tro.html": { summary: "LED ×1 · điện trở ×3 giá trị · jumper ×2", items: [P("esp32", 1), P("breadboard", 1), P("led", 1), P("r220", 1), P("r330", 1), P("r1k", 1), P("jumperMF", 2), P("usb", 1), P("multimeter", 1)] },
    "p03-nut-bat-tat-led.html": { summary: "Nút ×1 · LED ×1 · 220Ω ×1 · jumper ×4", items: [P("esp32", 1), P("breadboard", 1), P("button", 1), P("led", 1), P("r220", 1), P("jumperMF", 4), P("usb", 1), P("multimeter", 1)] },
    "p04-breathing-led.html": { summary: "LED ×1 · 220Ω ×1 · jumper ×2", items: [P("esp32", 1), P("breadboard", 1), P("led", 1), P("r220", 1), P("jumperMF", 2), P("usb", 1)] },
    "p04b-pir-bao-dong.html": { summary: "PIR ×1 · LED ×1 · 220Ω ×1 · jumper ×5", items: [P("esp32", 1), P("breadboard", 1), P("pir", 1), P("led", 1), P("r220", 1), P("jumperMF", 5), P("usb", 1)] },
    "p04c-lm393-phat-hien-vat.html": { summary: "LM393 IR ×1 · LED ×1 · 220Ω ×1 · jumper ×5", items: [P("esp32", 1), P("breadboard", 1), P("obstacleIr", 1), P("led", 1), P("r220", 1), P("jumperMF", 5), P("usb", 1)] },
    "p05-bien-tro-led.html": { summary: "Biến trở ×1 · LED ×1 · 220Ω ×1 · jumper ×5", items: [P("esp32", 1), P("breadboard", 1), P("pot10k", 1), P("led", 1), P("r220", 1), P("jumperMF", 5), P("usb", 1)] },
    "p06-cam-bien-anh-sang.html": { summary: "LDR module ×1 · jumper ×3", items: [P("esp32", 1), P("breadboard", 1), P("ldr", 1), P("jumperMF", 3), P("usb", 1), P("computer", 1)] },
    "p07-servo-bien-tro.html": { summary: "SG90 ×1 · biến trở ×1 · nguồn 5V · jumper ×7", items: [P("esp32", 1), P("breadboard", 1), P("servo", 1), P("pot10k", 1), P("mb102Power", 1), P("jumperMF", 7), P("usb", 1)] },
    "p07b-hai-servo.html": { summary: "SG90 ×2 · nguồn 5V riêng · jumper ×8", items: [P("esp32", 1), P("breadboard", 1), P("servo", 2), P("mb102Power", 1), P("jumperMF", 8), P("usb", 1)] },
    "p08-web-server.html": { summary: "ESP32 ×1 · cáp USB ×1 · điện thoại ×1", items: [P("esp32", 1), P("usb", 1), P("phone", 1), P("computer", 1), P("servo", 1, "Tùy chọn nếu điều khiển servo", "optional")] },
    "p09-oled-sensor.html": { summary: "OLED ×1 · LDR/DHT11 ×1 · jumper ×7", items: [P("esp32", 1), P("breadboard", 1), P("oled", 1), P("ldr", 1, "Chọn LDR hoặc DHT11"), P("dht11", 1, "Có thể thay cho LDR", "optional"), P("jumperMF", 7), P("usb", 1)] },
    "p10-buzzer.html": { summary: "Buzzer ×1 · 220Ω ×1 · jumper ×2", items: [P("esp32", 1), P("breadboard", 1), P("buzzer", 1), P("r220", 1), P("jumperMF", 2), P("usb", 1)] },
    "p14-relay.html": { summary: "Relay 2 kênh ×1 · jumper ×4 · nguồn USB 5V", items: [P("esp32", 1), P("breadboard", 1), P("relay", 1), P("jumperMF", 4), P("usb", 1), P("multimeter", 1)] },

    "p11-dc-motor-driver.html": { summary: "Motor TT ×1/2 · TB6612 ×1 · nguồn motor · tụ chống nhiễu", items: [P("esp32", 1), P("ttMotor", 1, "Lấy một motor trong combo 2WD"), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("powerSwitch", 1), P("fuse", 1), P("wire22", "~1m"), P("cap100n", 1), P("cap470", 1), P("terminal", 2), P("jumperMF", 6), P("multimeter", 1)] },
    "p12-pwm-dieu-toc-motor.html": { summary: "Dùng lại P11 · thêm dây PWM; không mua motor/driver lần hai", items: [P("esp32", 1), P("ttMotor", 1), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("wire22", "~1m"), P("cap100n", 1), P("cap470", 1), P("jumperMF", 7), P("phone", 1, "Nếu điều khiển bằng web slider") ] },
    "p13-mosfet-tai-ngoai.html": { summary: "MOSFET 3.3V ×1 · LED strip ×1 · diode ×1 · nguồn 5V", items: [P("esp32", 1), P("mosfet", 1), P("ledStrip", "0.5–1m"), P("diode", 1, "Chỉ bắt buộc với motor/tải cảm ứng"), P("battery2s", 1), P("buckLogic", 1), P("wire22", "~1m"), P("terminal", 2), P("jumperMF", 3), P("multimeter", 1)] },
    "p15-stepper-motor.html": { summary: "Combo 28BYJ-48 5V + ULN2003 ×1 · nguồn 5V · jumper ×6", items: [P("esp32", 1), P("stepperCombo", 1), P("battery2s", 1), P("buckLogic", 1), P("powerSwitch", 1), P("fuse", 1), P("cap470", 1), P("jumperMF", 6), P("wire22", "~0.5m"), P("multimeter", 1)] },
    "p16-encoder.html": { summary: "Encoder khe ×1 · đĩa ×1 · motor TT ×1 · TB6612 ×1", items: [P("esp32", 1), P("encoderTt", 1), P("ttMotor", 1), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("cap100n", 1), P("cap470", 1), P("jumperMF", 8), P("wire22", "~1m"), P("multimeter", 1)] },
    "p17-pid-giu-toc-do.html": { summary: "Dùng lại motor + TB6612 + encoder; không mua bộ thứ hai", items: [P("esp32", 1), P("encoderTt", 1), P("ttMotor", 1), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("cap100n", 1), P("cap470", 1), P("jumperMF", 8), P("wire22", "~1m"), P("multimeter", 1)] },
    "p18-xe-2-banh-wifi.html": { summary: "1 combo 2WD · TB6612 ×1 · pin+sạc · 2 buck · dây/ốc/tụ", items: [P("esp32", 1), P("chassisCombo", 1), P("ttMotor", 2), P("tb6612", 1), P("battery2s", 1), P("charger2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("powerSwitch", 1), P("fuse", 1), P("wire22", "2m đỏ + 2m đen"), P("cap100n", 2), P("cap470", 1), P("cap1000", 1), P("terminal", 5), P("heatshrink", 1), P("standoff", 1), P("zipTie", 1), P("dupontSet", 1), P("phone", 1), P("multimeter", 1)] },
    "p19-tranh-vat-can.html": { summary: "Dùng lại xe P18 · HC-SR04 ×1 · cầu chia áp · gá SG90", items: [P("esp32", 1), P("chassisCombo", 1), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("hcSr04", 1), P("ultrasonicBracket", 1), P("servo", 1), P("r10k", 1), P("r20k", 1), P("jumperMF", 8), P("wire22", "~1m"), P("standoff", 1), P("zipTie", 1)] },
    "p20-nao-python-ai.html": { summary: "Dùng lại xe P18/P19 · máy tính Python · Wi‑Fi; không cần Raspberry Pi", items: [P("esp32", 1), P("chassisCombo", 1), P("tb6612", 1), P("battery2s", 1), P("buckMotor", 1), P("buckLogic", 1), P("hcSr04", 1, "Nếu dùng cấu hình P19"), P("computer", 1), P("phone", 1, "Dùng kiểm thử/giao diện điều khiển", "optional"), P("usb", 1)] }
  };

  const robotBom = [
    { group: "Cơ khí & truyền động", id: "chassisCombo", qty: 1, note: "Combo đã gồm 2 motor; không đặt thêm motor rời." },
    { group: "Cơ khí & truyền động", id: "encoderTt", qty: 2, note: "Mỗi bánh một bộ; chọn đúng loại vừa trục sau motor TT." },
    { group: "Điều khiển công suất", id: "tb6612", qty: 1 },
    { group: "Điều khiển công suất", id: "mosfet", qty: 1 },
    { group: "Điều khiển công suất", id: "diode", qty: 5, note: "Thường bán theo túi; dùng khi tải là motor/coil." },
    { group: "Nguồn", id: "battery2s", qty: 1 },
    { group: "Nguồn", id: "charger2s", qty: 1 },
    { group: "Nguồn", id: "buckMotor", qty: 1 },
    { group: "Nguồn", id: "buckLogic", qty: 1 },
    { group: "Nguồn", id: "powerSwitch", qty: 1 },
    { group: "Nguồn", id: "fuse", qty: 1 },
    { group: "Cảm biến & cơ cấu", id: "stepperCombo", qty: 1 },
    { group: "Cảm biến & cơ cấu", id: "hcSr04", qty: 1 },
    { group: "Cảm biến & cơ cấu", id: "ultrasonicBracket", qty: 1 },
    { group: "Tải thử", id: "ledStrip", qty: "0.5–1m" },
    { group: "Dây & kết nối", id: "wire22", qty: "2m đỏ + 2m đen" },
    { group: "Dây & kết nối", id: "dupontSet", qty: 1 },
    { group: "Dây & kết nối", id: "terminal", qty: 5 },
    { group: "Dây & kết nối", id: "heatshrink", qty: 1 },
    { group: "Chống nhiễu", id: "cap100n", qty: 10 },
    { group: "Chống nhiễu", id: "cap470", qty: 2 },
    { group: "Chống nhiễu", id: "cap1000", qty: 1 },
    { group: "Lắp ráp", id: "standoff", qty: 1 },
    { group: "Lắp ráp", id: "zipTie", qty: 1 },
    { group: "Lắp ráp", id: "soldering", qty: 1, note: "Chỉ mua nếu chưa có bộ hàn." }
  ];

  const stateLabels = {
    owned: "Đang có",
    buy: "Cần mua",
    included: "Nằm trong combo",
    optional: "Tùy chọn"
  };

  function escapeHtml(value) {
    return String(value).replace(/[&<>"]/g, (character) => ({
      "&": "&amp;",
      "<": "&lt;",
      ">": "&gt;",
      '"': "&quot;"
    })[character]);
  }

  function itemRow(entry, showGroup = false) {
    const item = catalog[entry.id];
    const state = entry.state || item.state;
    const photo = item.photo
      ? `<a class="part-photo" href="${PHOTO}${escapeHtml(item.photo)}"><img src="${PHOTO}${escapeHtml(item.photo)}" alt="${escapeHtml(item.name)}"></a>`
      : `<span class="part-photo part-photo-empty">Chưa có ảnh</span>`;
    const search = item.search
      ? `<div class="part-search"><strong>Từ khóa:</strong> <code>${escapeHtml(item.search)}</code></div>`
      : "";
    const groupCell = showGroup ? `<td>${escapeHtml(entry.group)}</td>` : "";
    const note = entry.note ? `<div class="part-note">${escapeHtml(entry.note)}</div>` : "";
    return `<tr>
      ${groupCell}
      <td>${photo}</td>
      <td><strong>${escapeHtml(entry.qty)}</strong></td>
      <td><strong>${escapeHtml(item.name)}</strong><div class="part-spec">${escapeHtml(item.spec)}</div>${search}${note}</td>
      <td><span class="part-state part-state-${escapeHtml(state)}">${escapeHtml(stateLabels[state] || state)}</span></td>
    </tr>`;
  }

  function projectPartsSection(project) {
    return `<section class="section project-parts" id="danh-sach-linh-kien">
      <h2>Danh sách linh kiện đầy đủ</h2>
      <p class="section-lead">Số lượng dưới đây là số món vật lý cần đặt lên bàn cho project. Món ghi <strong>Nằm trong combo</strong> không mua lại nếu combo đã đủ.</p>
      <div class="table-scroll">
        <table>
          <thead><tr><th>Ảnh</th><th>SL</th><th>Linh kiện và quy cách</th><th>Trạng thái</th></tr></thead>
          <tbody>${project.items.map((entry) => itemRow(entry)).join("")}</tbody>
        </table>
      </div>
      <p class="inventory-update-note"><strong>Sau khi mua:</strong> chụp ảnh vào <code>docs/inventory/photos/</code>, cập nhật <code>inventory.md</code>, rồi thêm tên file ảnh vào <code>project-parts.js</code>.</p>
    </section>`;
  }

  function renderProjectPage(filename) {
    const project = projects[filename];
    if (!project) return;
    const hero = document.querySelector("main .hero");
    if (!hero || document.querySelector(".project-parts")) return;
    hero.insertAdjacentHTML("afterend", projectPartsSection(project));
  }

  function renderIndex() {
    document.querySelectorAll("a.card[href$='.html']").forEach((card) => {
      const filename = card.getAttribute("href").split("/").pop();
      const project = projects[filename];
      if (!project || card.querySelector(".card-parts")) return;
      card.insertAdjacentHTML("beforeend", `<span class="card-parts"><span>Linh kiện</span>${escapeHtml(project.summary)}</span>`);
    });

    const target = document.querySelector("#robot-shopping-list");
    if (!target) return;
    target.innerHTML = `<div class="table-scroll"><table>
      <thead><tr><th>Nhóm</th><th>Ảnh</th><th>SL mua</th><th>Tên chính xác / từ khóa tìm</th><th>Trạng thái</th></tr></thead>
      <tbody>${robotBom.map((entry) => itemRow(entry, true)).join("")}</tbody>
    </table></div>`;
  }

  const filename = window.location.pathname.split("/").pop() || "index.html";
  if (filename === "index.html") renderIndex();
  else renderProjectPage(filename);
})();
