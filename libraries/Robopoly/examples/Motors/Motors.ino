/***************************************************************************************
 *
 * Title:       Motors
 * Description: Use the motors to move your robot. The setSpeed() function uses timer1.
 *              setSpeed takes some time to have an effect, when calling setSpeed too
 *              often (for a line follower for example) a delay must follow the call
 *              (about 100ms sould do it).
 *
 ***************************************************************************************/
#include <robopoly.h>

int main()
{
  while(1)
  {
    setSpeed(20, 20);
    waitms(500);
    setSpeed(-20, -20);
    waitms(500);
  }
}
