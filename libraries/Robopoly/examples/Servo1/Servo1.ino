// servomotor function is defined inside Robopoly's library (uses timer2)
#include <robopoly.h>

// servo must be connected to PORTB0-7
#define SERVO 0

unsigned char pos;
unsigned char step;

void setup()
{
  // define initial angle
  pos = 0;
  // define increment step
  step = 5;
}

// increase angle from 0 to 180 
void loop()
{
  // set angle
  pos += step;
  setServo(SERVO, pos);
  
  // reverse direction at both ends
  if(pos <= 0 || pos >= 180)
  {
    step = -step;
  }
  
  // increment every 500ms
  delay(500);
}

