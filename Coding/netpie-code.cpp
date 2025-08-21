#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// NETPIE Credentials (ตามที่คุณสร้างใน Dashboard)
#define CLIENT_ID "56a77258-f2c2-4542-afff-40116c06c006"   // ClientID จาก NETPIE
#define TOKEN     "SHTunjthh6JunGLxk2bQ3yYw2JxjVeKR"    // Token จาก NETPIE
#define SECRET    "G7eBBUao3CLM5uQ8JvmxSfVyYxEJGPG5"      // Secret จาก NETPIE

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