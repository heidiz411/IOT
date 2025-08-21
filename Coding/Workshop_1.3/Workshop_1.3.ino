void setup() 
{
  Serial.begin(9600);
}
 void loop() 
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  Serial.print("ADC 10 bit = ");
  Serial.print(sensorValue); // print out the value you read:

  float volts = 3.30*(float)sensorValue/1023.00;
  Serial.print(" , Voltage = ");
  Serial.print(volts,3);
  Serial.println(" V");
  delay(3000);        // delay in between reads for stability
}
