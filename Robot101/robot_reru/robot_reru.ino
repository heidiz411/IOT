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
void setup()
{
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
  //--------------เขียนคำสั่ง---------------------
  mistion1();
  //  TackStop(); //วิ่งไปข้างหน้าเจอแยกหยุด
  //  delay(100);
  //  Bk(200);
  //  delay(100);
  //  TR();
  //--------------เขียนคำสั่ง---------------------
}
void loop()
{
  //int SensorLState = digitalRead(SensorL);  int SensorRState = digitalRead(SensorR);
  //Serial.print(SensorLState); Serial.print("   "); Serial.println(SensorRState);
  //Fd(170,150);
  //Bk(170,150);
  //delay(1);
}
