int ir_sensor;

void setup()
{
  pinMode(PC(2), OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  ir_sensor = digitalRead(PA(0));
  if(ir_sensor == 0)
  {
    digitalWrite(PC(2), HIGH);
    Serial.write("Stop\n");
  }
  else
  {
    digitalWrite(PC(2), LOW);
    Serial.write("Go\n");
  }
  delay(500);
}
