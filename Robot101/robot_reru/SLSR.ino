void Sl() {
  int SslA=120;
  int SslB=120;
  // Motor A
  analogWrite(speedPinA, SslA); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  // Motor B
  analogWrite(speedPinB, SslB); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  delay(50);
}

void SR() {
  int SsrA=120;
  int SsrB=120;
  
  // Motor A
  analogWrite(speedPinA, SsrA); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  // Motor B
  analogWrite(speedPinB, SsrB); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  delay(50);
}
