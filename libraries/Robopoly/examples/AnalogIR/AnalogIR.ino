// read an analog value from port A

// connect IR sensor to pin 0 of port A
#define IR_SENSOR PA(0)

void setup()
{
  // send sensor values back to serial
  Serial.begin(9600);
}

void loop()
{
  // analogRead only works on analog pins (port A)
  // analogRead returns values on 10 bytes: between 0 and 1024
  // 0 means an obstacle reflects IR light (light)
  // 1024 means there are no obstalces (dark)
  Serial.println(analogRead(IR_SENSOR));
  // wait 500ms between measurements
  delay(500);
}
