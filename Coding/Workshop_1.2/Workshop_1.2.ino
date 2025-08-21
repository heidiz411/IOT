#define LED 7  // ขา D0 ของบอร์ด NodeMCU เป็นขาที่ต่อกับ LED 
void setup() 
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT); // setup output
}

void loop() 
{
  digitalWrite(LED,HIGH); // Pin D0 is HIGH
  Serial.println("LED ON"); 
  delay(1000);
  digitalWrite(LED,LOW); // Pin D0 is LOW
  Serial.println("LED OFF"); 
  delay(1000);
}
