\`\`\`cpp  
\#include \<WiFi.h\>  
\#include \<PubSubClient.h\>  
\#include "DHT.h"

// \-------- WiFi (Wokwi) \--------  
const char\* WIFI\_SSID     \= "Wokwi-GUEST";  
const char\* WIFI\_PASSWORD \= "";

// \-------- NETPIE MQTT \--------  
const char\* MQTT\_BROKER \= "mqtt.netpie.io";  
const uint16\_t MQTT\_PORT \= 1883;

// \*\*\* ใส่ค่าจาก NETPIE Console ของคุณ \*\*\*  
const char\* NETPIE\_CLIENT\_ID \= "ID"; // \= ClientID (Device ID)  
const char\* NETPIE\_TOKEN     \= "Token";     // \= Username  
const char\* NETPIE\_SECRET    \= "Secret";    // \= Password

// \-------- DHT22 \--------  
\#define DHTPIN  16       // ขาที่ต่อ DATA  
\#define DHTTYPE DHT22    // ใช้ DHT22  
DHT dht(DHTPIN, DHTTYPE);

// \-------- MQTT Client \--------  
WiFiClient espClient;  
PubSubClient mqttClient(espClient);

unsigned long lastPublish \= 0;  
const unsigned long PUBLISH\_INTERVAL\_MS \= 2000;

// หัวข้อ (Topic)  
const char\* TOPIC\_TEMP \= "@msg/esp32/temperature";  
const char\* TOPIC\_HUMI \= "@msg/esp32/humidity";  
const char\* TOPIC\_JSON \= "@msg/esp32/data";

void connectWiFi() {  
 if (WiFi.status() \== WL\_CONNECTED) return;  
 Serial.print("Connecting to WiFi");  
 WiFi.begin(WIFI\_SSID, WIFI\_PASSWORD);  
 while (WiFi.status() \!= WL\_CONNECTED) {  
   delay(400);  
   Serial.print(".");  
 }  
 Serial.println();  
 Serial.print("WiFi connected, IP: ");  
 Serial.println(WiFi.localIP());  
}

void connectMQTT() {  
 mqttClient.setServer(MQTT\_BROKER, MQTT\_PORT);  
 while (\!mqttClient.connected()) {  
   Serial.print("Connecting to NETPIE MQTT...");  
   // clientId, username, password  
   if (mqttClient.connect(NETPIE\_CLIENT\_ID, NETPIE\_TOKEN, NETPIE\_SECRET)) {  
     Serial.println("connected.");  
   } else {  
     Serial.print("failed, rc=");  
     Serial.print(mqttClient.state()); // 5 \= Not authorized  
     Serial.println(" retry in 2s");  
     delay(2000);  
   }  
 }  
}

void setup() {  
 Serial.begin(115200);  
 delay(300);  
 dht.begin();        // เริ่มต้น DHT

 connectWiFi();  
 connectMQTT();  
}

void loop() {  
 if (WiFi.status() \!= WL\_CONNECTED) connectWiFi();  
 if (\!mqttClient.connected()) connectMQTT();  
 mqttClient.loop();

 unsigned long now \= millis();  
 if (now \- lastPublish \>= PUBLISH\_INTERVAL\_MS) {  
   lastPublish \= now;

   // อ่านเซ็นเซอร์  
   float h \= dht.readHumidity();  
   float t \= dht.readTemperature(); // Celsius (ค่าเริ่มต้น)  
   // ถ้าต้องการ Fahrenheit: dht.readTemperature(true);

   // กัน NAN  
   if (isnan(t) || isnan(h)) {  
     Serial.println("Failed to read from DHT\!");  
     return;  
   }

   // ส่งแบบหัวข้อแยก (numeric)  
   char bufT\[16\], bufH\[16\];  
   dtostrf(t, 0, 2, bufT);   // ทศนิยม 2 ตำแหน่ง  
   dtostrf(h, 0, 2, bufH);

   mqttClient.publish(TOPIC\_TEMP, bufT);  
   mqttClient.publish(TOPIC\_HUMI, bufH);

   // ส่งแบบ JSON รวม (ทางเลือก)  
   String json \= String("{\\"temp\\":") \+ bufT \+ ",\\"humid\\":" \+ bufH \+ "}";  
   mqttClient.publish(TOPIC\_JSON, json.c\_str());

   Serial.print("Published \-\> ");  
   Serial.print(TOPIC\_TEMP); Serial.print(": "); Serial.print(bufT);  
   Serial.print(", ");  
   Serial.print(TOPIC\_HUMI); Serial.print(": "); Serial.print(bufH);  
   Serial.print(", ");  
   Serial.print(TOPIC\_JSON); Serial.print(": "); Serial.println(json);  
 }  
}  
\`\`\`  
