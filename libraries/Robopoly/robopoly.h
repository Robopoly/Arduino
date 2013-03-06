/***************************************************************************************
 *
 * Title:       Robopoly library v2.1
 * File:        robopoly.h
 * Date:        14.10.2012
 * Authors:     Christophe Winter, Thierry Barras
 * Modified:    Karl Kangur
 *
 * Description: This library is made for EPFL's robotics club members: Robopoly. It
 *              contains some specific functions for used modules (motors) and an agenda
 *              function to do pseudo-multitasking.
 *
 ***************************************************************************************/

#ifndef _ROBOPOLY_H
#define _ROBOPOLY_H

#define A PORTA
#define B PORTB
#define C PORTC
#define D PORTD

// shortcut macros for delay functions
#include <util/delay.h>
#define waitms(value) _delay_ms(value)
#define waitus(value) _delay_us(value)

// port ddr addresses are one below the port
#define port_ddr(port) (port-1)
// port pin addresses are two below the port
#define port_pin(port) (port-2)

// set pin mode
#define pin_mode(port, pin, mode) (*(port_ddr(&port)) = (*(&port-1) & (~(1 << pin))) | (mode << pin))
// write bit on port
#define digital_write(port, pin, value) (port = (port & (~(1 << pin))) | (value << pin))
// read digital port value
#define digital_read(port, pin) (*(port_pin(&port)) & (1 << pin))

unsigned char analogReadPortA(unsigned char bit);

#ifndef NOSERIAL
void serialSetup(void);
void serialWrite(const char*);
void serialPrint(int);
void serialRaw(unsigned char);
unsigned char serialAvailable(void);
char serialRead(void);
#endif

#ifndef NOMOTORS
void setSpeed(int left, int right);
#endif

#ifndef NOCALLBACK
unsigned char setCallback(void (*newCallbackAddr)(void), unsigned int interval, unsigned char executionNumber);
void clearCallback(unsigned char callbackId);
#endif

#ifndef NOSERVO
void setServo(unsigned char id, unsigned char angle);
#endif

#endif
