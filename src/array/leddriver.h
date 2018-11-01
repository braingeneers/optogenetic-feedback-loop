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
#include <iostream>


#define   SDI   16 //27   //serial data input
#define   RCLK  20 //28   //memory clock input(STCP)
#define   SRCLK 21 //29   //shift register clock input(SHCP)

#define   SDI_2   13 //27   //serial data input
#define   RCLK_2  19 //28   //memory clock input(STCP)
#define   SRCLK_2 26 //29   //shift register clock input(SHCP)

//unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
#define ARRAY_SIZE 8 //leds per array
#define LED_MASK 0x80
#define STANDARD_DELAY 25 //ms

//int arraySize; //8 //leds per array
//int ledMask; //0x80
//int standardDelay;

class Array {
      private:
        int sdi_; //serial data input // 16
        int rclk_; //memory clock input (STCP) //20
        int srclk_;  //shift register clock input (SHCP) //21

      public:
        int rclk(void) {return rclk_;};
        int sdi(void) {return sdi_;};
        int srclk(void) {return srclk_;};
        void init(int sdi, int rclk, int srclk);
        void shiftin(bool *pattern);
        //void stop();

};


void pulse(int pin);

/*
class Board {
      private:
          std::vector<LedArray>;


      public:
          void start(const int port, const unsigned int cores);
          void stop();


};


class Rack {
    private:
          std::vector<Board>;


    public:
        void start();
        void stop();

};
*/


//class Cluster {};


#endif /*_LEDDRIVER_H*/
