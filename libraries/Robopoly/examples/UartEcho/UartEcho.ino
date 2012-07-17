void setup()
{
  // serial communication speed in baud
  Serial.begin(9600);
}

void loop()
{
  // only if the serial buffer contains something
  if(Serial.available() > 0)
  {
    // read input buffer and write it to output buffer
    Serial.write(Serial.read());
  }
}

