// กำหนดขาเชื่อมต่อ
const int leftSensor = 12;      // เซ็นเซอร์ซ้าย
const int rightSensor = 13;     // เซ็นเซอร์ขวา

// ขาควบคุมมอเตอร์ซ้าย
const int motorLeftA = 6;      // IN1
const int motorLeftB = 7;      // IN2
const int motorLeftPWM = 5;   // ENA

// ขาควบคุมมอเตอร์ขวา
const int motorRightA = 8;     // IN3
const int motorRightB = 9;     // IN4
const int motorRightPWM = 10;  // ENB

// ความเร็วมอเตอร์
const int baseSpeed = 150;     // ความเร็วพื้นฐาน (0-255)
const int turnSpeed = 100;     // ความเร็วขณะเลี้ยว

void setup() {
  // กำหนดโหมดการทำงานของขา
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(motorLeftPWM, OUTPUT);
  
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorRightPWM, OUTPUT);
  
  Serial.begin(9600);  // เริ่มการสื่อสารกับคอมพิวเตอร์
}

void loop() {
  // อ่านค่าจากเซ็นเซอร์
  int leftValue = digitalRead(leftSensor);
  int rightValue = digitalRead(rightSensor);
  
  // แสดงค่าเซ็นเซอร์
  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" Right: ");
  Serial.println(rightValue);
  
  // ตัดสินใจเคลื่อนที่ตามค่าเซ็นเซอร์
  if (leftValue == LOW && rightValue == LOW) {
    // เส้นอยู่ตรงกลาง - เดินหน้า
    moveForward();
  } 
  else if (leftValue == LOW && rightValue == HIGH) {
    // เส้นอยู่ทางซ้าย - เลี้ยวซ้าย
    turnLeft();
  } 
  else if (leftValue == HIGH && rightValue == LOW) {
    // เส้นอยู่ทางขวา - เลี้ยวขวา
    turnRight();
  } 
  else {
    // ไม่เจอเส้น - หยุด
    stopMotors();
  }
  
  delay(10);  // หน่วงเวลาเล็กน้อย
}