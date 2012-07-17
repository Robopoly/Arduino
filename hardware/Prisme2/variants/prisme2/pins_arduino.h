/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
  
  Modified 2012-06-27 for atmega8535 K.Kangur
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 24 : -1)

#define digitalPinHasPWM(p)         ((p) == 4 || (p) == 5 || (p) == 6 || (p) == 11)

const static uint8_t SS   = 12;
const static uint8_t MOSI = 13;
const static uint8_t MISO = 14;
const static uint8_t SCK  = 15;

const static uint8_t SDA = 17;
const static uint8_t SCL = 16;
const static uint8_t LED_BUILTIN = 18;

// I have no idea what these are supposed to do...
#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 31) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#ifndef ARDUINO_MAIN

// makes more sense to add these IMO
#define PA(x) (x)
#define PB(x) (8+x)
#define PC(x) (16+x)
#define PD(x) (24+x)

// wire/i2c/twi lines
#define SCL PC(0)
#define SDA PC(1)

#endif

// for servo motors
#define TIFR1 TIFR
#define TIMSK1 TIMSK

#define TIMER0 TIMER0A

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading and writing)
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

// pin order in numbers (shortcut), first pin is 0 so you can call digitalWrite(0, 1)
const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	PA, // PA0 = 0
	PA, // PA1 = 1
	PA, // PA2 = 2
	PA, // PA3 = 3
	PA, // PA4 = 4
	PA, // PA5 = 5
	PA, // PA6 = 6
	PA, // PA7 = 7
	PB, // PB0 = 8
	PB, // PB1 = 9
	PB, // PB2 = 10
	PB, // PB3 = 11
	PB, // PB4 = 12
	PB, // PB5 = 13
	PB, // PB6 = 14
	PB, // PB7 = 15
	PC, // PC0 = 16
	PC, // PC1 = 17
	PC, // PC2 = 18 (LED pin)
	PC, // PC3 = 19
	PC, // PC4 = 20
	PC, // PC5 = 21
	PC, // PC6 = 22
	PC, // PC7 = 23
	PD, // PD0 = 24
	PD, // PD1 = 25
	PD, // PD2 = 26
	PD, // PD3 = 27
	PD, // PD4 = 28
	PD, // PD5 = 29
	PD, // PD6 = 30
	PD // PD7 = 31
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	_BV(0), // 0, port A
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), // 8, port B
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), // 16, port C
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), // 24, port D
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER, // 0 - port A
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, // 8 - port B
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER0,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, // 16 - port C
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, // 24 - port D
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER1B,
	TIMER1A,
	NOT_ON_TIMER,
	TIMER2
};

#endif

#endif