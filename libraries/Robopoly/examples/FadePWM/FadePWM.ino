// timer2 usage example for PWM signal

// the LED is on pin 2 of port C
#define LED PC(2)

// initial PWM value from 0 to 100%
char ledPWM = 0;
// how fast the fading will be done (increment from 0 to 100%)
int fadeAmount = 5;

void setup()
{
  // set LEd port (pin 2 port C) as output, equivalent to pinMode(LED, HIGH)
  DDRC |= (1 << 2);
  // set prescaler of 128: 8MHz/128 = 62.5kHz = 16us/call (arbitrary)
  TCCR2 = 5;
  // set timer2 start value (count from 155 to 255: 255-155 = 100)
  TCNT2 = 155;
  // set timer2 compare value
  OCR2 = 155+ledPWM;
  // clear output compare flag (OCR2 == TCNT2) and TCNT2 overflow flag (TCNT2 == 255)
  TIFR &= ~((1 << OCF2) + (1 << TOV2));
  // enable compare match interrupt (OCR2 == TCNT2 generates a compare interrupt)
  // enable overflow interrupt (TCNT2 == 255 generates an overflow interrupt)
  TIMSK |= (1 << OCIE2) + (1 << TOIE2);
  // enable global interrupts
  sei();
} 

void loop()  {
  // change the brightness
  ledPWM += fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if(ledPWM <= 0 || ledPWM >= 100)
  {
    fadeAmount = -fadeAmount;
  }
  
  // wait for 30 milliseconds to see the fading effect, delay() uses timer1
  delay(30);
}

// set line to logical 0 with compare
ISR(TIMER2_COMP_vect)
{
  // equivalent to digitalWrite(LED, LOW);
  PORTC &= ~(1 << 2);
}

// set line to logical 1 with overflow
ISR(TIMER2_OVF_vect)
{
  // timer2 start value reset
  TCNT2 = 155;
  
  // ledPWM must not be smaller than 1 or it will flicker
  if(ledPWM < 1)
  {
    ledPWM = 1;
  }
  // set next compare interrupt to set line to 0
  OCR2 = 155+ledPWM;
  // equivalent to digitalWrite(LED, HIGH);
  PORTC |= (1 << 2);
}

