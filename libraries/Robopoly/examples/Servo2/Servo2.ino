// use Arduino library, the servo control uses timer1
// these functions can't be used with the setSpeed function of Robopoly libraray
#include <Servo.h>

// attach servo to the pin 0 of port C
#define SERVO PC(0)

// servo instance
Servo myServo;

void setup()
{
  myServo.attach(SERVO);
}

// toggle between 0 and 180 degrees every 2 seconds
void loop()
{
  myServo.write(0);
  delay(2000);
  myServo.write(180);
  delay(2000);
}
