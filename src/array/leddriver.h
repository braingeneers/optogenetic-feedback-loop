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
#include <iterator>
#include <vector>


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
void pulse(int pin);
void activate(int sdi, int rclk, int srclk, bool * pattern);
void initPins();
/*

class Array {
      private:
        int sdi_; //serial data input // 16
        int rclk_; //memory clock input (STCP) //20
        int srclk_;  //shift register clock input (SHCP) //21

      public:
        Array(int sdi, int rclk, int srclk,  Client * myClient);

        int rclk(void) {return rclk_;};
        int sdi(void) {return sdi_;};
        int srclk(void) {return srclk_;};

        //void shiftin(bool *pattern);
        void shiftin(Message * msg, int pattern, Client * myClient);
};




class Board {
      private:
          int numArrays_;
          //int arraySize_;  //8 //leds per array
          //int ledMask_; //define LED_MASK 0x80

      public:
          std::vector<Array*> Arrays;
          Board(int numArrays){ numArrays_=numArrays; }; //arraySize, ledMask
          ~Board(){ for(Array* ledArray: Arrays) delete ledArray; };
          void addArray(int sdi, int rclk, int srclk){Arrays.push_back(new Array(sdi, rclk, srclk)); };
          int numArrays() {return numArrays_;};

};*/


/*class Rack {
    private:
          int numBoards_;

    public:
        std::vector<Board*> Boards;
        Rack(int numBoards){ numBoards_=numBoards; };
        ~Rack(){ for(Board* ledBoard: Boards) delete ledBoard; };
        void addBoard(int numArrays){Boards.push_back(new Board(numArrays)); };
        int numBoards() {return numBoards_;};

};
*/

//class Cluster {};



#endif  /*_LEDDRIVER_H*/
