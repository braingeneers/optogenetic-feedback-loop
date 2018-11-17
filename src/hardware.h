//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// hardware.h
// Description: Header file for inventorization and control of optogenetic
// array boards from master server
//-----------------------------------------------------------------------------


#ifndef _HARDWARE_H
#define _HARDWARE_H

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <semaphore.h>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.



#define   SDI   16 //27   //serial data input
#define   RCLK  21 //28   //memory clock input(STCP)
#define   SRCLK 20 //29   //shift register clock input(SHCP)

#define   SDI_2   13 //27   //serial data input
#define   RCLK_2  19 //28   //memory clock input(STCP)
#define   SRCLK_2 26 //29   //shift register clock input(SHCP)

//LED Indication
#define   IND_SERVER_CONNECTION   17
#define   IND_SERVER_MSG_RCV      4
#define   IND_CLIENT_POWER        3
#define   IND_CLIENT_MSG_SEND     2

//unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
#define ARRAY_SIZE 8 //leds per array
#define LED_MASK 0x80
#define STANDARD_DELAY 25 //ms
#define LONG_DELAY 1000 //ms

//int arraySize; //8 //leds per array
//int ledMask; //0x80
//int standardDelay;

class Array {
      private:
        int sdi_; //serial data input // 16
        int rclk_; //memory clock input (STCP) //20
        int srclk_;  //shift register clock input (SHCP) //21


      public:
        Array(int sdi, int rclk, int srclk);//Client * myClient);
        int rclk(void) {return rclk_;};
        int sdi(void) {return sdi_;};
        int srclk(void) {return srclk_;};
        void shiftin(int * sdi,  int *rclk, int* srclk, int * inPattern, bool * pattern);
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
          void addArray(int sdi, int rclk, int srclk) {Arrays.push_back(new Array(sdi, rclk, srclk));};
          int numArrays() {return numArrays_;};

};


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
