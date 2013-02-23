/***************************************************************************************
 *
 * Title:       SerialEcho
 * Description: Sends data read from the serial input buffer to the serial output
 *              buffer.
 *
 ***************************************************************************************/
#include <robopoly.h>

char data;

int main()
{
  // setup the serial communication, 9600 baud by default
  serialSetup();
  
  while(1)
  {
    // check for data in the input buffer
    if(serialAvailable())
    {
      // read a single character to data variable
      data = serialRead();
      // send data back to computer
      serialWrite(&data);
    }
  }
  return 0;
}

