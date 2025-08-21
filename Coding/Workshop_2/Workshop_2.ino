#include <ESP8266WiFi.h>
const char* ssid     = "Heidiz411-iPhone";  // SSID
const char* password = "0895955456"; //PASSWORD
void setup() 
{
   Serial.begin(9600);
   Serial.println("Starting...");
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
   }
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
}
void loop() 
{
}
