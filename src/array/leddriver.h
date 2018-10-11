//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// leddriver.h
// Description: Header file for LED array driver using parallel shift registers
//-----------------------------------------------------------------------------


#ifndef _LEDDRIVER_H
#define _LEDDRIVER_H

#include <bcm2835.h>
#include <stdio.h>


#define   SDI   16 //27   //serial data input
#define   RCLK  20 //28   //memory clock input(STCP)
#define   SRCLK 21 //29   //shift register clock input(SHCP)


//unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

#define ARRAY_SIZE 24 //leds per array
#define LED_MASK 0x800000


void pulse(int pin);

void shiftin(bool *pattern);

void init(void);

#endif /*_LEDDRIVER_H*/
