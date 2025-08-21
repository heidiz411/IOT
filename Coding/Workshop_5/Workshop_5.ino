#define D0 16
#define LED D0    // pin D0
int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
  Serial.begin(9600);
}
void loop() {

  long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!"); // ตรวจพบการเคลื่อนไหวของมนุษย์
      digitalWrite(LED,HIGH);   // หลอดไฟติด 
      delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");   // ตรวจไม่พบการเคลื่อนไหว 
      digitalWrite(LED,LOW);   // หลอดไฟดับ
      delay(1000);
      }
}

