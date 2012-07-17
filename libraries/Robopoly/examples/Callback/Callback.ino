// we have to use generic _delay_ms() function as Arduino delay() uses timer0
#include <util/delay.h>
// callback function is defined inside Robopoly's library (uses timer0)
#include <robopoly.h>

// the LED is on pin 2 of port C
#define LED PC(2)

// this stores the callback id
unsigned char myCallbackId;

// callback mustn't have any arguments
void callbackBlinkLed()
{
  // turn the LED on for 100ms
  digitalWrite(LED, HIGH);
  _delay_ms(100);
  // turn LED off
  digitalWrite(LED, LOW);
}

void setup()
{
  // set LED port as output
  pinMode(LED, OUTPUT);
}

void loop()
{
    // blink LED every 200ms, 0 means the callback will be called indefinitely
    myCallbackId = setCallback(callbackBlinkLed, 200, 0);
    // wait for 2 seconds while the LED blinks
    _delay_ms(2000);
    // clear callback
    clearCallback(myCallbackId);
    // wait for 2 seconds while the LED if off
    _delay_ms(2000);
}

