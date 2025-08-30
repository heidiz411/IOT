void Fd() {
  // Motor A ซ้าย
  analogWrite(speedPinA, 170); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  // Motor B ขวา
  analogWrite(speedPinB, 150); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
void Ao() {
  // Motor A ซ้าย
  analogWrite(speedPinA, 0); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  // Motor B ขวา
  analogWrite(speedPinB, 0); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
void Bk(int BKT) {
  // Motor A
  analogWrite(speedPinA, 170); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  // Motor B
  analogWrite(speedPinB, 150); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  delay (BKT);
}
