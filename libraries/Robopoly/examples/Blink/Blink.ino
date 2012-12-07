/***************************************************************************************
 *
 * Title:       Blink
 * Description: Turn the onboard LED on and off every 500 milliseconds
 *
 ***************************************************************************************/
#include <avr/io.h>
#include <robopoly.h>

// the LED is on pin 2 of port C
#define LED_PORT PORTC
#define LED_PIN  2

int main()
{
  pin_mode(LED_PORT, LED_PIN, 1);
  while(1)
  {
    // turn LED on
    digital_write(LED_PORT, LED_PIN, 1);
    // in milliseconds
    waitms(500);
    // turn LED off
    digital_write(LED_PORT, LED_PIN, 0);
    waitms(500);
  }
  return 0;
}

