int SensorL = 12;
int SensorR = 13;
// Motor A
int dir1PinA = 6;
int dir2PinA = 7;
int speedPinA = 5; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์
// Motor B
int dir1PinB = 8;
int dir2PinB = 9;
int speedPinB = 10; // เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์

void setup() {
  Serial.begin(9600);
  pinMode(SensorL, INPUT);
  pinMode(SensorR, INPUT);
  //กำหนด ขา เพื่อใช้ในการควบคุมการทำงานของ  Motor ผ่านทาง L298N
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  delay(2000);
}

void loop() {
  for(int i=150; i<255; i++) {
    analogWrite(speedPinA, i);
    analogWrite(speedPinB, i);
    Serial.println(i);
    delay(500);
  }
}
