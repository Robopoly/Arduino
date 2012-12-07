/***************************************************************************************
 *
 * Title:       FadePWM
 * Description: Fade the onboard LED using PWM (Pulse Width Modulation) signal using
 *              interrupts (timer1). The LED will be toggeled on and off so fast the
 *              eye will not see it flickering. Motors cannot be used as they use the
 *              timer1 too.
 *
 ***************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#define NOMTOR
#include <robopoly.h>

// initial PWM value between 1 to 100%
volatile unsigned char ledPWM = 50;
char fadeAmount = 1;

// timer1 compare vector
ISR(TIMER1_COMPA_vect)
{
  // turn LED off
  digital_write(PORTC, 2, 0);
}

// timer1 overflow vector
ISR(TIMER1_OVF_vect)
{
  // turn the LED on
  digital_write(PORTC, 2, 1);
  // timer1 start value reset (2^16-100)
  TCNT1 = 65436;
  // set next compare interrupt
  OCR1A = 65436+ledPWM;
}

int main()
{
  // set LED port as output
  pin_mode(PORTC, 2, 1);
  
  // set prescaler to 256 (8MHz/256 = 31.25kHz)
  TCCR1A = 0;
  TCCR1B = (1 << CS12);
  // set timer1 start value (count from 155 to 255: 255-155 = 100)
  TCNT1 = 65436;
  // set timer1 compare value
  OCR1A = 65436+ledPWM;
  // enable compare match interrupt (OCR1 == TCNT1 generates a compare interrupt)
  // enable overflow interrupt (TCNT1 == 255 generates an overflow interrupt)
  TIMSK = (1 << OCIE1A) | (1 << TOIE1);
  // enable interrupts
  asm("sei");
  
  while(1)
  {
    // change the brightness
    ledPWM += fadeAmount;
  
    // reverse the direction of the fading
    if(ledPWM == 1 || ledPWM == 100)
    {
      fadeAmount *= -1;
    }
    
    // wait for 30 milliseconds to see the fading effect
    waitms(10);
  }
  return 0;
}

