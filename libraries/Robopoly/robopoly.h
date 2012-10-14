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

// port ddr addresses are one below the port
#define port_ddr(port) (port-1)
// port pin addresses are two below the port
#define port_pin(port) (port-2)

// set pin mode
#define pin_mode(port, pin, mode) (*(port_ddr(&port)) = (*(&port-1) & (~(1 << pin))) | (mode << pin))
// write bit on port
#define digital_write(port, pin, value) (port = (port & (~(1 << pin))) | (value << pin))
// read digital port value
#define digital_read(port, pin) (*(port_ddr(&port)) & (1 << pin))

void setSpeed(int left, int right);

unsigned char setCallback(void (*newCallbackAddr)(void), unsigned int interval, unsigned char executionNumber);
void clearCallback(unsigned char callbackId);

void setServo(unsigned char id, unsigned char angle);

#endif
