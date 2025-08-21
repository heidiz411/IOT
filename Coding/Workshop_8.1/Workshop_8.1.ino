#include <ESP8266WiFi.h>
      #define D1 5
      #define LED D1
      #define D2 4
      #define BUZZER D2
      #define GASsensor A0
    int Sensorthres = 280;
    void setup() 
    {
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(GASsensor, INPUT);
      Serial.begin(9600);
      }
      void loop()
      {
      int analogSensor = analogRead(GASsensor);
      Serial.println("GAS Value:  " );
      Serial.println(analogSensor);
      if (analogSensor > Sensorthres)
      {
        digitalWrite(LED,HIGH);  // BUZZER ส่งเสียงเตือนแก็สรั่ว
        tone(BUZZER,1500,250); 
      }
      else
      {
        digitalWrite(LED,LOW);
      }
      delay(500);
      }

