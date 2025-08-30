void TL() {
  int SsrA = 180;
  int SsrB = 180;
  while (true) {
    int SensorLState = digitalRead(SensorL);
    if (SensorLState == 0) {
      // Motor A
      analogWrite(speedPinA, SsrA); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      // Motor B
      analogWrite(speedPinB, SsrB); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
    }
    if (SensorLState == 1) {
      Ao();
      break;
    }
  }
}
void TR() {
  int SsrA = 180;
  int SsrB = 180;
  while (true) {
    int SensorRState = digitalRead(SensorR);
    if (SensorRState == 0) {
      // Motor A
      analogWrite(speedPinA, SsrA); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
      // Motor B
      analogWrite(speedPinB, SsrB); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
    }
    if (SensorRState == 1) {
      Ao();
      break;
    }
  }
}
