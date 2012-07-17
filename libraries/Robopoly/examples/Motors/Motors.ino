// motor speed function is defined inside Robopoly's library (uses timer1)
#include <robopoly.h>

void setup()
{
  
}

void loop()
{
  // set left and right motor speeds from 0 to 100
  setSpeed(20, -40);
  delay(500);
  setSpeed(-20, 40);
  delay(500);
}
