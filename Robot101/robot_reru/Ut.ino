void Ut(int SsrA, int SsrB,int TimeUt) {
  // Motor A
  analogWrite(speedPinA, SsrA); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  // Motor B
  analogWrite(speedPinB, SsrB); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  delay(TimeUt);
    // Motor A
  analogWrite(speedPinA, 0); 
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  // Motor B
  analogWrite(speedPinB, 0); 
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
