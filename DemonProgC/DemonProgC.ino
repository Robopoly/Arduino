#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600

#include <util/setbaud.h>

uint8_t ir_sensor, i;

void writeUart(const char *text)
{
  for(i = 0; text[i] != '\0'; i++)
  {
    // wait for empty buffer
    while((UCSRA & (1 << UDRE)) == 0);
    // set uart buffer value
    UDR = (unsigned char)text[i];
  }
}

int main()
{
  // set up uart communication
  UBRRH = UBRRH_VALUE;
  UBRRL = UBRRL_VALUE;
  UCSRA &= ~(1 << U2X);
  UCSRB |= 0x18;

  // set LED as output
  DDRC = 0b00000100;
  while(1)
  {
    // read pin 0 from PORTA
    ir_sensor = PINA & 0x00000001;
    if(ir_sensor == 0)
    {
      PORTC = 0b00000100;
      writeUart("Stop\n");
    }
    else
    {
      PORTC = 0;
      writeUart("Go\n");
    }
    _delay_ms(1000);
  }
}

