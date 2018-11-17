//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// leddriver.h
// Description: Header file for LED array driver using parallel shift registers
//-----------------------------------------------------------------------------


#ifndef _LEDDRIVER_H
#define _LEDDRIVER_H

#include <bcm2835.h>
#include "../hardware.h"


void pulse(int pin);
void activate(int sdi, int rclk, int srclk, bool * pattern);

void initPins();
void shutDownPins();

void statusConnected();

void statusPreSendMsg();
void statusSentMsg();

void statusAwaitingMsg();
void statusRecievedMsg();


#endif  /*_LEDDRIVER_H*/
