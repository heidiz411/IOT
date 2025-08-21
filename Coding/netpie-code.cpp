#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// NETPIE Credentials (ตามที่คุณสร้างใน Dashboard)
#define CLIENT_ID "กรอก Client ID จาก NETPIE"   // ClientID จาก NETPIE
#define TOKEN     "กรอก Token จาก NETPIE"    // Token จาก NETPIE
#define SECRET    "กรอก Secret จาก NETPIE"      // Secret จาก NETPIE

#define DHTPIN 17
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to NETPIE...");
    if (client.connect(CLIENT_ID, TOKEN, SECRET)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer("mqtt.netpie.io", 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("อ่านค่าไม่ได้");
    return;
  }

  String payload = "{\"temp\":";
  payload += String(temperature);
  payload += ",\"humi\":";
  payload += String(humidity);
  payload += "}";

  Serial.println("ส่งข้อมูล: " + payload);
  client.publish("@msg/esp32/temp", String(temperature).c_str());
  client.publish("@msg/esp32/humi", String(humidity).c_str());

  delay(5000);
}