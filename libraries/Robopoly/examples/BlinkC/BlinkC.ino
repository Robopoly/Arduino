// blink LED in C

// include input/output definitions
#include <avr/io.h>
// use light _delay_ms() function
#include <util/delay.h>

int main()
{
  // set PORTC pin 2 mode as output
  DDRC = 0b00000100;
  while(1)
  {
    // set PORTC pin 2 value
    PORTC = 0b00000100;
    _delay_ms(500);
    PORTC = 0b00000000;
    _delay_ms(500);
  }
  return 0;
}
