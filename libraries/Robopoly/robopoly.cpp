/***************************************************************************************
 *
 * Title:       Robopoly library v2.0
 * File:        robopoly.cpp
 * Date:        21.07.2012
 * Authors:     Christophe Winter, Thierry Barras, Karl Kangur
 * 
 * Description: This library is made for EPFL's robotics club members: Robopoly. It
 *              contains some specific functions for used modules (motors) and an agenda
 *              function to do pseudo-multitasking.
 *
 ***************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "robopoly.h"

// set motor speed for both wheels, uses timer1
void setSpeed(int left, int right)
{
	// PD4-7 as output
	DDRD |= 0xf0;
	// set Waveform Generation Mode
	TCCR1A = 0x03; // (1<<WGM11)|(1<<WGM10): PWM, phase correct, 10bits
	TCCR1B = 0x01; // (1<<CS10): set prescaling of 1 (8MHz/1 = 8MHz)
	
	if(left == 0)
	{
		// normal port operation, OC1A disconnected
		TCCR1A &= ~(3 << COM1A0);
		PORTD &= ~(1 << PD5);
	}
	else
	{
		// clear OC1A on Compare Match (set output to low level)
		TCCR1A |= (1 << COM1A1);
		
		// set left motor direction (PD7)
		if(left < 0)
		{
			left = -left;
			PORTD |= (1 << 7);
		}
		else
		{
			PORTD &= ~(1 << 7);
		}
		
		// limit to maximum speed
		if(left > 100)
		{
			left = 1023;
		}
		else
		{
			left = (long) 1023*left/100;	
		}
	}

	if(right == 0)
	{
		// normal port operation, OC1B disconnected
		TCCR1A &= ~(3 << COM1B0);
		PORTD &= ~(1 << PD4);
	}
	else
	{
		// clear OC1B on Compare Match (set output to low level)
		TCCR1A |= (1 << COM1B1);
		
		// set right motor direction (PD6)
		if(right < 0)
		{
			right = -right;
			PORTD |= (1 << 6);
		}
		else
		{
			PORTD &= ~(1 << 6);
		}
		
		// limit to maximum speed
		if(right > 100)
		{
			right = 1023;
		}
		else
		{
			right = (long) 1023*right/100;
		}
	}
	
	// first write high byte (important, see datasheet)
	OCR1AH = left >> 8;
	OCR1AL = left & 0xff;
	OCR1BH = right >> 8;
	OCR1BL = right & 0xff;
}

// agenda routine, allows up to 8 callbacks, uses timer0
void(*callbackFct[8])(void); // callback function addresses
static volatile unsigned char callbackStatus = 0; // callback status flags, indicates callback existence
static volatile unsigned int timeInterval[8] = {0,0,0,0,0,0,0,0}; // maximum of 2^16*1ms = about 1 minute between 2 calls
static volatile unsigned char repeatNumber[8] = {0,0,0,0,0,0,0,0}; // repeat up to 255 times (0 means infinite repeat)
static volatile unsigned long nextExecutionTime[8] = {0,0,0,0,0,0,0,0}; // absolute time + interval
static volatile unsigned long time = 0; // absolute time counter, prone to overflow, but lasts 2^32*1ms = about 50 days

// set callback: function to be called every [interval] in milliseconds, [repeatNumber] times (set to 0 for infinite repeat)
unsigned char setCallback(void (* newCallbackAddr)(void), unsigned int interval, unsigned char executionNumber)
{
	// start agenda timer (timer0)
	if(callbackStatus == 0)
	{
		// clock select, fclk/64 = 8MHz/64 = 125kHz, (3<<CS00)
		TCCR0 = 3;
		// output compare register (125kHz / 125 = 1000Hz = 1ms)
		OCR0 = 125;
		// enable compare match interrupt (interrupt when timer0 == OCR0)
		TIMSK |= (1 << OCIE0);
		// clear output compare flag (enable counting)
		TIFR &= ~(1 << OCF0);
		// enable global interrupts
		sei();
	}

	unsigned char i;
	for(i=0; i<8; i++)
	{
		// callback slot already used
		if((callbackStatus & (1 << i)) != 0)
		{
			continue;
		}
		
		// set callback slot
		callbackStatus |= (1 << i);
		// set callback function
		callbackFct[i] = newCallbackAddr;
		// set delay between callbacks
		timeInterval[i] = interval;
		// number of times to execute
		repeatNumber[i] = executionNumber;
		// set next callback
		nextExecutionTime[i] = time + interval;
		// return callback id
		return i;	
	}
	
	// if no slot was available return 255
	return 255;
}

// clear callback
void clearCallback(unsigned char callbackId)
{
	// in case no slot was available (callbackId = 255)
	if(callbackId > 7)
	{
		return;
	}
	
	// clear callback slot
	callbackStatus &= ~(1 << callbackId);
	// stop timer0 if there are no more callbacks
	if(callbackStatus == 0)
	{
		// no clock source (stop timer0)
		TCCR0 = 0;
		// disable compare match interrupt
		TIMSK &= ~(1 << OCIE0);
		// reset absolute time counter
		time = 0;
	}
}

// agenda interrupt vector, called every 1 millisecond, uses timer0
ISR(TIMER0_COMP_vect)
{
	// reset timer/counter register
	TCNT0 = 0;
	// add time (1ms) to the total absolute time counter
	time++;
	
	unsigned char i;
	for(i=0; i<8; i++)
	{
		// callback slot not used or not the one we want to call
		if((callbackStatus & (1 << i)) == 0 || nextExecutionTime[i] > time)
		{
			continue;
		}
		
		// call function
		(* callbackFct[i])();
		
		// calculate next call time
		nextExecutionTime[i] = time + timeInterval[i];
	
		// remove callback when number of executions completed
		if(repeatNumber[i] == 1)
		{
			clearCallback(i);
		}
		else if(repeatNumber[i] > 1)
		{
			// count down to 1, execute and remove
			repeatNumber[i]--;
		}
		break;
	}
}

// up to 8 servomotors can be controlled with this routine
static volatile unsigned char servoSetup = 0;
unsigned char servoAngle[8]= {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char servoId = 0;

// valid angles are between 0 and 125
void setServo(unsigned char id, unsigned char angle)
{
	// set up timer2 for servomotors
	if(!servoSetup)
	{
		servoSetup = 1;
		// set prescaler of 128: 8MHz/128 = 62.5kHz = 16us/call (increments timer2 envery 16us)
		TCCR2 = 5;
		// set timer2 first compare value (value for compare interrupt)
		OCR2 = 250;
		// servos work by sending them a 1ms to 2ms pulse every 20ms period in theory, 1ms = 0deg, 2ms = 180deg
		// for 8 servomotors the PWM full period for one servomotor = 8*(255-TCNT2)*16us = 20ms => TCNT2 = 100
		// PWM max time at logical 1 is defined by OCR2
		// set timer2 start value, overflow count 255-TCNT2 = 255-100 = 155 cycles at 16us = 2.48ms per servo motor
		TCNT2 = 100;
		// clear output compare flag for OCR2 == TCNT2 and TCNT2 overflow flag
		TIFR &= ~((1 << OCF2) + (1 << TOV2));
		// enable compare match interrupt (OCR2 == TCNT2 generates a compare interrupt)
		// enable overflow interrupt (TCNT2 == 255 generates an overflow interrupt)
		TIMSK |= (1 << OCIE2) + (1 << TOIE2);
		// enable global interrupts
		sei();
	}

	// check for valid input angle
	if(angle >= 0 && angle <= 180)
	{
		// these are empirical values to get angles from 0 to 180deg
		// casting not necessary for some reason
		servoAngle[id] = angle*110/180 + 135; // min = 135, max = 245
		// set pin as output
		DDRB |= (1 << id);
	}
}

// set servo line to logical 0 with compare
ISR(TIMER2_COMP_vect)
{
	if(servoAngle[servoId])
	{
		PORTB &= ~(1 << servoId);
	}
}

// set servo line to logical 1 with overflow
ISR(TIMER2_OVF_vect)
{
	// compare value counter reset for 155 cycles (interrupt when TCNT2 == 255)
	TCNT2 = 100;
	// loop servomotors
	servoId++;
	if(servoId == 8)
	{
		servoId = 0;
	}
	
	// set line to 1 if a servo has been declared on this line
	if(servoAngle[servoId])
	{
		// set next compare interrupt to set line back to 0
		OCR2 = servoAngle[servoId];
		PORTB |= (1 << servoId);
	}
}
