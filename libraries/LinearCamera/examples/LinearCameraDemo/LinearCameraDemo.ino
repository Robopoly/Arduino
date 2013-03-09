/***************************************************************************************
 *
 * Title:       Linear Camera Demo
 * Description: Uses the TSL3301 to gather light and returns the highest intensity
 *              region from 0 to 24. It uses 100 pixels and then takes the average of 4
 *              pixels for each of the 25 regions.
 *
 ***************************************************************************************/
#include <robopoly.h>
#include <LinearCamera.h>

unsigned char max_area;

int main()
{
  serialSetup();
  lcam_setup();
  
  // camera needs a reset after 200ms
  waitms(200);
  lcam_reset();
  
  while(1)
  {
    // gather light (integrate) for 10 microseconds
    lcam_integrate(10);
    // load pixel values to lcam_buffer byte array
    lcam_read();
    // get the highest 4-pixel area (between 0 and 24)
    max_area = lcam_getpic();
    // send data back to computer
    serialPrint(max_area);
    serialWrite("\n");
    // wait 200ms between measurements
    waitms(200);
  }
  return 0;
}

