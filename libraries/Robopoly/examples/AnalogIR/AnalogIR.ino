/***************************************************************************************
 *
 * Title:       AnalogIR
 * Description: Read an analog value from port A, example based on an IR sensor.
 * Note:        Only works on analog pins (port A).
 *              analogReadPortA(pin): 8-bit value (0: ostacle, 255: no obstacle)
 *
 ***************************************************************************************/
#include <robopoly.h>

#define ANALOG_PIN 0

// stores values from 0 to 255
unsigned char ir_value;

int main()
{
  // send data to computer via serial, 9600 baud by default
  serialSetup();
  
  while(1)
  {
    // read analog value from PORTA pin 0
    ir_value = analogReadPortA(ANALOG_PIN);
    serialPrint(ir_value);
    // send a new line character
    serialWrite("\n");
    // wait 500ms between measurements
    waitms(500);
  }
}

