void TackCTI(int TackCTI) {
  while (true) {
    // statements
    int SensorLState = digitalRead(SensorL);
    int SensorRState = digitalRead(SensorR);
    Serial.print(SensorLState);
    Serial.print("   ");
    Serial.println(SensorRState);
    if (SensorLState == 0 && SensorRState == 0) {
      Fd();
    }
    if (SensorLState == 1 && SensorRState == 1) {
      Fd();
      delay(TackCTI);
      Ao();
      break;
    }

    if (SensorLState == 1) {
      Sl();
    }
    if (SensorRState == 1) {
      SR();
    }
  }
}
