int sensorPin = A0;            // กำหนดให้ sensor LDR ต่อกับ ขา A0
unsigned int sensorValue = 0;  // ค่าเริ่มต้น = 0

void setup()
{
  pinMode(13, OUTPUT);        // กำหนดขา D7 หรือ GPIO 13 ส่งค่าออกเป็น output 
  Serial.begin(9600);        
}
void loop()
{
  sensorValue = analogRead(sensorPin);  // ค่าที่อ่านได้ จากเซนเซอร์   
  if(sensorValue<400)     // ถ้าค่าที่อ่านได้ มีค่าน้อยกว่า 400
digitalWrite(13, HIGH);   //  LED ON
  else
{
 digitalWrite(13, LOW);   //  LED OFF
  }
  Serial.print(sensorValue, DEC);     // แสดงค่าที่อ่านได้ทาง Serial Monitor (0 to 1024)
  Serial.println("");                    
  delay(500);  
}

