/***************************************************************************************
 *
 * Title:       TSL3301 linear camera C library for the PRisme2
 * File:        linearCamera.cpp
 * Date:        07.12.2012
 * Author:      Karl Kangur
 * Comments:    Based on the assembly code by Christophe Winter, Fabrizio Lo Conte and
 *              Eric Seuret.
 * 
 * Datasheet:   http://www.ams.com/eng/content/download/250205/975793/142526
 *
 ***************************************************************************************/
#include <util/delay.h>
#include <robopoly.h>
#include "LinearCamera.h"

unsigned char lcam_buffer[102];

void lcam_pulse()
{
  digital_write(LCAM_PORT, LCAM_SCLK, 1);
  digital_write(LCAM_PORT, LCAM_SCLK, 0);
}

void lcam_pulse_clock(unsigned char times)
{
  for(unsigned char i = 0; i < times; i++)
  {
    lcam_pulse();
  }
}

// Send a byte to the linear camera
void lcam_send(unsigned char value)
{
  // Start bit
  digital_write(LCAM_PORT, LCAM_SDIN, 0);
  lcam_pulse();
  // Send 8 bits to camera
  for(unsigned char i = 0; i < 8; i++)
  {
    digital_write(LCAM_PORT, LCAM_SDIN, ((value >> i) & 1));
    lcam_pulse();
  }
  // Stop bit
  digital_write(LCAM_PORT, LCAM_SDIN, 1);
  lcam_pulse();
}

// Initialization Sequence
void lcam_reset(void)
{
  // allow a minimum of 1 millisecond for the internal analog circuitry to settle
  _delay_ms(1);
  
  // 10 clock impulsions with SDIN held high to clear the receiver logic
  digital_write(LCAM_PORT, LCAM_SDIN, 1);
  lcam_pulse_clock(10);
  // 3 reset instructions to clear the control logic
  lcam_send(0x1b);
  lcam_send(0x1b);
  lcam_send(0x1b);
  // 30 clock impulsions to assure the state of SDOUT
  lcam_pulse_clock(30);
  
  // register write mode
  lcam_send(0X5F);
  // Clear mode register (single chip, not sleep)
  lcam_send(0x00);
}

void lcam_setup(void)
{
  lcam_reset();
  
  // set inputs and outputs
  pin_mode(LCAM_PORT, LCAM_SCLK, 1);
  pin_mode(LCAM_PORT, LCAM_SDIN, 1);
  pin_mode(LCAM_PORT, LCAM_SDOUT, 0);
  // make sure the clock is cleared
  digital_write(LCAM_PORT, LCAM_SCLK, 0);
  
  // Left offset
  lcam_send(0x40);
  lcam_send(0);
  // Left gain
  lcam_send(0x41);
  lcam_send(15);
  // Middle offset
  lcam_send(0x42);
  lcam_send(0);
  // Middle gain
  lcam_send(0x43);
  lcam_send(15);
  // Right offset
  lcam_send(0x44);
  lcam_send(0);
  // Right gain
  lcam_send(0x45);
  lcam_send(15);
}

void lcam_startintegration(void)
{
  // Send start integration command
  lcam_send(0x08);
  // delayed until the pixel reset cycle has been completed (22-clock delay)
  lcam_pulse_clock(22);
}

void lcam_endintegration(void)
{
  // Sample int command
  lcam_send(0x10);
  // pixel reset sequence is initiated, requires 22 clocks
  lcam_pulse_clock(22);
}

// shortcut for starting and ending integration
void lcam_integrate(unsigned int microseconds)
{
  lcam_startintegration();
  _delay_us(microseconds);
  lcam_endintegration();
}

// Tell the camera to be ready to send data
void lcam_read(void)
{
  unsigned char i, pixel_bit, pixel;
  // Read pixel command
  lcam_send(0x02);
  // 44-clock cycle delay until the first pixel data is output
  lcam_pulse_clock(44);
  // Read the 102 pixels from the camera
  for(i = 0; i < 102; i++)
  {
    pixel = 0;
    // pulse the pixel start bit (SDOUT = 0)
    lcam_pulse();
    // read a byte, bit by bit
    for(pixel_bit = 0; pixel_bit < 8; pixel_bit++)
    {
      digital_write(LCAM_PORT, LCAM_SCLK, 1);
      // read pin while clock is at 1
      pixel |= (((LCAM_PIN >> LCAM_SDOUT) & 1) << pixel_bit);
      digital_write(LCAM_PORT, LCAM_SCLK, 0);
    }
    // store byte to buffer
    lcam_buffer[i] = pixel;
    // pulse the pixel stop bit (SDOUT = 1)
    lcam_pulse();
  }
}

unsigned char* lcam_getdata()
{
  return lcam_buffer;
}

// Divide the 100 first pixels into 25 4-byte averages and return the highest average index
unsigned char lcam_getpic(void)
{
  unsigned char i, value, highest = 0, max_region = 0;
  unsigned int average;
  for(i = 0; i < 25; i++)
  {
    // take 4-byte average and divide by 4 (shift to right by 2)
    value = ((lcam_buffer[i*4] + lcam_buffer[i*4+1] + lcam_buffer[i*4+2] + lcam_buffer[i*4+3]) >> 2);
    if(value > highest)
    {
      highest = value;
      max_region = i;
    }
    average += value;
  }
  
  average /= 25;
  
  if(highest > average + 30)
  {
    return max_region;
  }
  else
  {
    return 0;
  }
}
