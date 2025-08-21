#include <WiFi.h>

const char* ssid     = "Heidiz411-iPhone";   // ลองให้ตรงเป๊ะ หรือชั่วคราวเปลี่ยนชื่อเป็น Khemawit_iPhone
const char* password = "0895955456";          // ใช้เฉพาะตัวอักษร/ตัวเลข ASCII

void connectWiFi() {
  WiFi.mode(WIFI_STA);          // โหมด Station
  WiFi.persistent(false);       // ไม่เขียนค่าในแฟลช ลดปัญหาค่าค้าง
  WiFi.setAutoReconnect(true);  // ต่ออัตโนมัติถ้าหลุด
  WiFi.setSleep(false);         // ปิด sleep เพื่อลดปัญหาหลุดตอนเชื่อม

  Serial.println("\nScanning WiFi...");
  int n = WiFi.scanNetworks();
  if (n <= 0) {
    Serial.println("No networks found");
  } else {
    for (int i = 0; i < n; i++) {
      Serial.printf("%2d) SSID: %s  RSSI: %d dBm  Ch:%d  Enc:%s\n",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i),
                    (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "OPEN" : "SECURED");
    }
  }

  Serial.printf("\nConnecting to: %s ...\n", ssid);
  WiFi.begin(ssid, password);

  // รอผลการเชื่อมต่อแบบมี timeout
  uint8_t result = WiFi.waitForConnectResult(15000); // 15 วินาที
  if (result == WL_CONNECTED) {
    Serial.println("Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.print("Connect failed, status = "); Serial.println(WiFi.status());
    Serial.println("WiFi diagnostics:");
    WiFi.printDiag(Serial); // พิมพ์ข้อมูลไดอะแกน
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  connectWiFi();
}

void loop() {
  // ถ้าหลุด ลองต่อใหม่
  if (WiFi.status() != WL_CONNECTED) {
    static unsigned long last = 0;
    if (millis() - last > 10000) { // ลองทุก 10 วินาที
      last = millis();
      Serial.println("Reconnecting...");
      WiFi.disconnect();
      connectWiFi();
    }
  }
}