/***************************************************************************************
 *
 * Title:       Servo Motor
 * Description: Use the servo motors to turn to a specific angle from 0-180 degrees,
 *              uses the timer2. Controls up to 8 servomotors connected to the PORTB.
 *
 ***************************************************************************************/
#include <robopoly.h>

// servo must be connected to PORTB0-7
#define SERVO 0

// define initial angle
volatile unsigned char angle = 0;
unsigned char step = 1;

int main()
{
  while(1)
  {
    // set angle
    angle += step;
    setServo(SERVO, angle);
    
    // reverse direction at both ends
    if(angle == 0 || angle == 180)
    {
      step *= -1;
    }
    
    // increment every 500ms
    waitms(10);
  }
}
