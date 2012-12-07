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
    if(serialAvailable())
    {
      // read a single character to data
      data = serialRead();
      // send data to computer
      serialWrite(&data);
    }
  }
  return 0;
}

