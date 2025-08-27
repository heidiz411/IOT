#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// -------- WiFi --------
const char* WIFI_SSID     = "WiFi"; // Wifi to connect
const char* WIFI_PASSWORD = "Password"; // Password to connect

// -------- NETPIE MQTT --------
const char* MQTT_BROKER = "mqtt.netpie.io";
const uint16_t MQTT_PORT = 1883; // ถ้าใช้ TLS จะเป็น 8883 (ดูหมายเหตุด้านล่าง)

// *** ใส่ค่าจาก NETPIE Console ของอุปกรณ์คุณ ***
const char* NETPIE_CLIENT_ID = "Client ID = Device ID"; // Client ID = Device ID
const char* NETPIE_TOKEN     = "Username";     // Username
const char* NETPIE_SECRET    = "Password";    // Password

// -------- DHT22 --------
#define DHTPIN  D2       // ใช้ขา D2 (GPIO4)
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// -------- MQTT Client --------
WiFiClient espClient;           // ถ้าจะใช้ TLS เปลี่ยนเป็น WiFiClientSecure
PubSubClient mqttClient(espClient);

// ตั้งค่า publish ทุกกี่มิลลิวินาที
const unsigned long PUBLISH_INTERVAL_MS = 2000;
unsigned long lastPublish = 0;

// หัวข้อ (Topic)
const char* TOPIC_TEMP = "@msg/esp8266/temperature";
const char* TOPIC_HUMI = "@msg/esp8266/humidity";
const char* TOPIC_JSON = "@msg/esp8266/data";

// ---------- ฟังก์ชัน ----------
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  Serial.print("Connecting to WiFi: ");
  Serial.print(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
    yield(); // ป้องกัน watchdog บน ESP8266
  }
  Serial.println();
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  while (!mqttClient.connected()) {
    Serial.print("Connecting to NETPIE MQTT...");
    // clientId, username, password
    if (mqttClient.connect(NETPIE_CLIENT_ID, NETPIE_TOKEN, NETPIE_SECRET)) {
      Serial.println("connected.");
      // ถ้าต้องการ subscribe อะไร เพิ่มที่นี่
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state()); // rc=5 => Not authorized
      Serial.println(" retry in 2s");
      delay(2000);
      yield();
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);
  dht.begin();

  connectWiFi();
  connectMQTT();

  // ปรับ keepalive ให้เหมาะกับเครือข่ายบ้านทั่วไป
  mqttClient.setKeepAlive(20);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqttClient.connected()) connectMQTT();
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
    lastPublish = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature(); // °C

    if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT!");
      return;
    }

    char bufT[16], bufH[16];
    dtostrf(t, 0, 2, bufT);
    dtostrf(h, 0, 2, bufH);

    // ส่งแบบหัวข้อแยก (ตัวเลขล้วน)
    mqttClient.publish(TOPIC_TEMP, bufT);
    mqttClient.publish(TOPIC_HUMI, bufH);

    // ส่งแบบ JSON รวม (เผื่อใช้)
    // ตัวอย่าง: {"temp":27.53,"humid":62.18}
    String json = String("{\"temp\":") + bufT + ",\"humid\":" + bufH + "}";
    mqttClient.publish(TOPIC_JSON, json.c_str());

    Serial.print("Published -> ");
    Serial.print(TOPIC_TEMP); Serial.print(": "); Serial.print(bufT);
    Serial.print(", ");
    Serial.print(TOPIC_HUMI); Serial.print(": "); Serial.print(bufH);
    Serial.print(", ");
    Serial.print(TOPIC_JSON); Serial.print(": "); Serial.println(json);

    yield();
  }
}