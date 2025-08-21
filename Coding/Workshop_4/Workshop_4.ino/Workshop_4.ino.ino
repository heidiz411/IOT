#include <AuthClient.h>     //รวมไลบรารี่ของ NETPIE 4 ไฟล์ 
#include <MicroGear.h>      //ไลบรารี MicroGear ของ NETPIE
#include <ESP8266WiFi.h>     //ไลบรารี ของ ESP8266      

const char* ssid     = "prapas";             //ชื่อเครือข่าย WiFi
const char* password = "40494049";           //รหัสผ่านของเครือข่าย
#define LEDPin D4                            // LED ต่อกับ D4      
#define APPID       "lamp1"                  //ชื่อ APPLICATION ของอุปกรณ์ที่เชื่อมต่อกับ NETPIE
#define GEARKEY     "ESxsW7HuAsck2lH"             //Key ของอุปกรณ์ที่เชื่อมต่อกับ NETPIE
#define GEARSECRET  "xHlNp5o8MHHmYZPUdUTqNvHfa"   //Secret ของอุปกรณ์ที่เชื่อมต่อกับ NETPIE
#define ALIAS       "nodemcu"                     //ชื่อเรียกอุปกรณ์ที่เชื่อมต่อกับ NETPIE
#define SCOPE       ""
 
  WiFiClient client;
  AuthClient *authclient;
  MicroGear microgear(client);
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) //ฟังก์ชันตรวจสอบการปรากฏของข้อความ
{
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}
 
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) // รับข้อความจาก server
{
  Serial.print("Incoming message --> "); 
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
for (int i = 0; i < msglen; i++)
{
  strState[i] = (char)msg[i];
  Serial.print((char)msg[i]);
}
  Serial.println();

String stateStr = String(strState).substring(0, msglen); // ข้อความที่ได้รับจาก server
if (stateStr == "ON")
{
  digitalWrite(LEDPin, HIGH);
  microgear.chat("SensorLED", "ON");  // ส่งข้อความถึง server
}
else if (stateStr == "OFF")
{
  digitalWrite(LEDPin, LOW);
  microgear.chat("SensorLED", "OFF"); // ส่งข้อความถึง server
}
}
 
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(LEDPin, OUTPUT);

  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);

if (WiFi.begin(ssid, password))
 {
 while (WiFi.status() != WL_CONNECTED)  //วนรอการเชื่อมต่อ WiFi
{
  delay(500);
  Serial.print(".");    //พิมพ์เครื่องหมาย ... แสดงสถานะรอการเชื่อมต่อ
}
  Serial.println("WiFi connected");  //แสดงข้อความแจ้งการเชื่อมต่อ WiFi สำเร็จ
  Serial.println("IP address: ");    //แสดงหมายเลข ไอพีแอดเดรส ของเครือข่าย WiFi ที่เชื่อมต่อ
  Serial.println(WiFi.localIP());

  microgear.resetToken();            //รีเซ็ทโทเคน
  microgear.init(GEARKEY, GEARSECRET, SCOPE);
  microgear.connect(APPID);
   }
 }
 void loop()
{
 if (microgear.connected())  //รอการเชื่อมต่อกับ NETPIE
 {
  microgear.loop();
  Serial.println("connect...");  //แสดงข้อความเชื่อมต่อกับ NETPIE สำเร็จ
}
else
 {
 Serial.println("connection lost, reconnect...");  //แสดงข้อความการเชื่อมต่อกับ NETPIE ไม่สำเร็จ
 microgear.connect(APPID);
}
delay(500);
}
