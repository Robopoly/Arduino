/***************************************************************************************
 *
 * Title:       Robopoly library v2.0
 * File:        robopoly.h
 * Date:        21.07.2012
 * Authors:     Christophe Winter, Thierry Barras, Karl Kangur
 * 
 * Description: This library is made for EPFL's robotics club members: Robopoly. It
 *              contains some specific functions for used modules (motors) and an agenda
 *              function to do pseudo-multitasking.
 *
 ***************************************************************************************/

#ifndef _ROBOPOLY_H
#define _ROBOPOLY_H

void setSpeed(int left, int right);

unsigned char setCallback(void (*newCallbackAddr)(void), unsigned int interval, unsigned char executionNumber);
void clearCallback(unsigned char callbackId);

void setServo(unsigned char id, unsigned char angle);

#endif
