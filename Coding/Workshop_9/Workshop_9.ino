void Line_Notify(String message) ;
#include <ESP8266WiFi.h>

// Config connect WiFi
#define WIFI_SSID "JACK"
#define WIFI_PASSWORD "jack310321"

// Line config
#define LINE_TOKEN "NGqeU7GurZLLR9cLcBZkY8uvYLAPDKiZxb14Qjlh8hx"

#define GASsensor A0
int ValuaBegin = 200;
String message = "%E0%B9%81%E0%B8%81%E0%B9%87%E0%B8%AA%E0%B8%A3%E0%B8%B1%E0%B9%88%E0%B8%A7%20%E0%B8%AD%E0%B8%B1%E0%B8%99%E0%B8%95%E0%B8%A3%E0%B8%B2%E0%B8%A2%20!";

void setup() {
  pinMode(GASsensor, INPUT);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int analogSensor = analogRead(GASsensor);
      Serial.println("GAS Value:  ");
      Serial.println(analogSensor);
       if (analogSensor > ValuaBegin)
   {
    delay(500);

    Serial.println("GAS_leak!");
    Line_Notify(message);
    // Serial.println();
  }
  delay(500);
}

void Line_Notify(String message) {
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}

