/***************************************************************************************
 *
 * Title:       Blink Interrupt
 * Description: Turn the onboard LED on and off every 500 milliseconds using interrupts.
 *              This uses the timer1 which is also used by the motors, you cannot use
 *              this program if you want to use the motors.
 *
 ***************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#define NOMOTOR
#include <robopoly.h>

void blink()
{
  // toggle the LED pin
  PORTC ^= (1 << 2);
}

// vector that is called when the interrupt fires
ISR(TIMER1_COMPA_vect)
{
  // we want the LED to turn on and off
  blink();
}

int main()
{
  // set LED pin as output
  pin_mode(PORTC, 2, 1);
  
  // reset timer1 counter
  TCNT1 = 0;
  // set CTC mode (compare match mode) and prescaler to 256
  TCCR1A = 0;
  TCCR1B = (1 << CS12) | (1 << WGM12);
  // set compare value (8MHz / 256 / 15625 = 2Hz = 500ms)
  OCR1A = 15625;
  // enable output compare match interrupt (enables TIMER1_COMPA_vect call)
  TIMSK = (1 << OCIE1A);
  // enable interrupts
  asm("sei");

  while(1)
  {
    // nothing to do here, interrupts take care of the blinking
  }
  return 0;
}
