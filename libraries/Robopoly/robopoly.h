#ifndef _ROBOPOLY_H
#define _ROBOPOLY_H

void setSpeed(int left, int right);

unsigned char setCallback(void (*newCallbackAddr)(void), unsigned int interval, unsigned char executionNumber);
void clearCallback(unsigned char callbackId);

void setServo(unsigned char id, unsigned char angle);

#endif
