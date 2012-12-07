/***************************************************************************************
 *
 * Title:       Callback
 * Description: Call a function periodically to make a pseudo-multitasking program.
 *              This program blinks the onboard LED every 100ms for 2 seconds, stops for
 *              2 seconds and then blinks the LED again.
 *
 ***************************************************************************************/
#include <avr/io.h>
#include <robopoly.h>

// the LED is on pin 2 of port C
#define LED_PORT PORTC
#define LED_PIN  2

// this stores the callback id
unsigned char myCallbackId;

// callback mustn't have any arguments
void callbackBlinkLed()
{
  // turn the LED on for 100ms
  digital_write(LED_PORT, LED_PIN, 1);
  waitms(100);
  // turn LED off
  digital_write(LED_PORT, LED_PIN, 0);
}

int main()
{
  // set LED port as output
  pin_mode(LED_PORT, LED_PIN, 1);
  while(1)
  {
    // blink LED every 200ms, 0 means the callback will be called indefinitely
    myCallbackId = setCallback(callbackBlinkLed, 200, 0);
    // wait for 2 seconds while the LED blinks
    waitms(2000);
    // clear callback
    clearCallback(myCallbackId);
    // wait for 2 seconds while the LED if off
    waitms(2000);
  }
  return 0;
}

