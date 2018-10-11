#ifndef _DRIVER_H
#define _DRIVER_H

#include <bcm2835.h>
#include <stdio.h>


#define   SDI   16 //27   //serial data input
#define   RCLK  20 //28   //memory clock input(STCP)
#define   SRCLK 21 //29   //shift register clock input(SHCP)


//unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


#define LEDS 24 //leds per organoid
#define LED_MASK 0x800000



void pulse(int pin);


void SIPO(unsigned int byte);


void init(void);

#endif /*_DRIVER_H*/
