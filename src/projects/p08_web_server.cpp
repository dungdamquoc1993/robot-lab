#include "p08_web_server.h"

#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>
#include <cstring>

#ifndef P08_WIFI_SSID
#define P08_WIFI_SSID ""
#endif

#ifndef P08_WIFI_PASSWORD
#define P08_WIFI_PASSWORD ""
#endif

constexpr int ONBOARD_LED_PIN = 2;
constexpr int OPTIONAL_SERVO_PIN = 18;
constexpr int OPTIONAL_SERVO_CHANNEL = 1;
constexpr int SERVO_PWM_FREQ = 50;
constexpr int SERVO_PWM_BITS = 16;
constexpr int SERVO_MIN_US = 700;
constexpr int SERVO_MAX_US = 2300;
constexpr int SERVO_PERIOD_US = 1000000 / SERVO_PWM_FREQ;

constexpr char AP_SSID[] = "RobotLab-P8";
constexpr char AP_PASSWORD[] = "robotlab8";

WebServer p08Server(80);

bool p08LedOn = false;
int p08ServoAngle = 90;
bool p08ServoAttached = false;

uint32_t p08DutyFromMicros(int pulseUs) {
  const uint32_t maxDuty = (1UL << SERVO_PWM_BITS) - 1;
  return (static_cast<uint32_t>(pulseUs) * maxDuty) / SERVO_PERIOD_US;
}

void p08WriteServoAngle(int angle) {
  if (!p08ServoAttached) {
    ledcSetup(OPTIONAL_SERVO_CHANNEL, SERVO_PWM_FREQ, SERVO_PWM_BITS);
    ledcAttachPin(OPTIONAL_SERVO_PIN, OPTIONAL_SERVO_CHANNEL);
    p08ServoAttached = true;
  }

  p08ServoAngle = constrain(angle, 0, 180);
  const int pulseUs = map(p08ServoAngle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  ledcWrite(OPTIONAL_SERVO_CHANNEL, p08DutyFromMicros(pulseUs));
}

void p08WriteLed(bool on) {
  p08LedOn = on;
  digitalWrite(ONBOARD_LED_PIN, p08LedOn ? HIGH : LOW);
}

String p08JsonStatus() {
  String json = "{";
  json += "\"led\":";
  json += p08LedOn ? "true" : "false";
  json += ",\"servoAngle\":";
  json += p08ServoAngle;
  json += ",\"ip\":\"";
  json += (WiFi.getMode() == WIFI_AP) ? WiFi.softAPIP().toString() : WiFi.localIP().toString();
  json += "\"}";
  return json;
}

void p08SendHome() {
  String html = R"rawliteral(
<!doctype html>
<html lang="vi">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>RobotLab P8</title>
  <style>
    :root { color-scheme: dark; font-family: Arial, sans-serif; }
    body { margin: 0; background: #0d1110; color: #e7eeeb; }
    main { max-width: 680px; margin: 0 auto; padding: 24px 16px 40px; }
    section { border: 1px solid #2a3734; border-radius: 8px; padding: 18px; margin: 14px 0; background: #151b1a; }
    h1 { margin: 0 0 8px; font-size: 32px; }
    h2 { margin: 0 0 12px; font-size: 20px; }
    button { min-height: 44px; padding: 0 16px; margin: 4px; border: 1px solid #47c7ad; border-radius: 8px; background: #14352f; color: #d9fff6; font-size: 16px; }
    input[type=range] { width: 100%; }
    .status { color: #aab8b3; }
    .value { font-weight: 700; color: #d9fff6; }
  </style>
</head>
<body>
  <main>
    <h1>P8 Web server</h1>
    <p class="status">HTTP request từ điện thoại đang điều khiển ESP32 trực tiếp.</p>

    <section>
      <h2>Onboard LED GPIO2</h2>
      <button onclick="setLed('on')">ON</button>
      <button onclick="setLed('off')">OFF</button>
      <button onclick="setLed('toggle')">TOGGLE</button>
      <p>Trạng thái: <span id="led" class="value">...</span></p>
    </section>

    <section>
      <h2>Servo tùy chọn GPIO18</h2>
      <input id="servo" type="range" min="0" max="180" value=")rawliteral";
  html += p08ServoAngle;
  html += R"rawliteral(" oninput="setServo(this.value)">
      <p>Góc: <span id="angle" class="value">)rawliteral";
  html += p08ServoAngle;
  html += R"rawliteral(</span> độ</p>
    </section>
  </main>

  <script>
    async function refresh() {
      const res = await fetch('/api/status');
      const data = await res.json();
      document.getElementById('led').textContent = data.led ? 'ON' : 'OFF';
      document.getElementById('angle').textContent = data.servoAngle;
      document.getElementById('servo').value = data.servoAngle;
    }
    async function setLed(state) {
      await fetch('/api/led?state=' + state);
      refresh();
    }
    async function setServo(angle) {
      document.getElementById('angle').textContent = angle;
      await fetch('/api/servo?angle=' + angle);
      refresh();
    }
    refresh();
  </script>
</body>
</html>
)rawliteral";
  p08Server.send(200, "text/html; charset=utf-8", html);
}

void p08HandleLed() {
  const String state = p08Server.arg("state");
  if (state == "on") {
    p08WriteLed(true);
  } else if (state == "off") {
    p08WriteLed(false);
  } else if (state == "toggle") {
    p08WriteLed(!p08LedOn);
  }

  p08Server.send(200, "application/json", p08JsonStatus());
}

void p08HandleServo() {
  if (p08Server.hasArg("angle")) {
    p08WriteServoAngle(p08Server.arg("angle").toInt());
  }

  p08Server.send(200, "application/json", p08JsonStatus());
}

bool p08ConnectStation() {
  if (std::strlen(P08_WIFI_SSID) == 0) return false;

  WiFi.mode(WIFI_STA);
  WiFi.begin(P08_WIFI_SSID, P08_WIFI_PASSWORD);

  Serial.printf("P8 connecting to Wi-Fi SSID '%s'", P08_WIFI_SSID);
  const unsigned long startedAt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startedAt < 12000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("STA connect failed; falling back to RobotLab-P8 access point.");
    return false;
  }

  Serial.print("P8 STA IP: http://");
  Serial.println(WiFi.localIP());
  return true;
}

void p08StartAccessPoint() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  Serial.println("P8 AP mode ready.");
  Serial.printf("SSID: %s\n", AP_SSID);
  Serial.printf("Password: %s\n", AP_PASSWORD);
  Serial.print("Open: http://");
  Serial.println(WiFi.softAPIP());
}

void p08_setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("P8 booting...");

  pinMode(ONBOARD_LED_PIN, OUTPUT);
  p08WriteLed(false);

  if (!p08ConnectStation()) {
    p08StartAccessPoint();
  }

  p08Server.on("/", HTTP_GET, p08SendHome);
  p08Server.on("/api/status", HTTP_GET, []() {
    p08Server.send(200, "application/json", p08JsonStatus());
  });
  p08Server.on("/api/led", HTTP_GET, p08HandleLed);
  p08Server.on("/api/servo", HTTP_GET, p08HandleServo);
  p08Server.onNotFound([]() {
    p08Server.send(404, "text/plain; charset=utf-8", "P8 route not found");
  });
  p08Server.begin();

  Serial.println("P8 Web server ready. Breadboard can stay blank.");
}

void p08_loop() {
  p08Server.handleClient();
}
