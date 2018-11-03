//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// master.c
// Description: Master program for synthesizing virtual organoid model,
//       top-level supervisor algorithm, array stimulation, and visual display
//-----------------------------------------------------------------------------

#include <iostream>
#include <iterator>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "../protocol.h"
#include "../protocol.c"
#include "../array/leddriver.h"
#include "../array/leddriver.c"
using namespace std;


int main(int argc, char *argv[]) {

  Client* myClient = new Client();
  myClient->start(argv[1], argv[2]);

  //------------------------
  Board* myBoard = new Board(2);
  myBoard->addArray(SDI, RCLK, SRCLK);
  myBoard->addArray(SDI_2, RCLK_2, SRCLK_2);
  int  pattern;
  int arraySel;
  //int last;
  //------------------------

  Message msg;


    for (;;) {
    //  memset(msg.pattern, false, ARRAY_SIZE);
      bzero(msg.pattern, ARRAY_SIZE);
      //for(bool b : msg.pattern) b = true;

      cout <<  "What array configuration?" << endl;
      cin >> pattern;
      cout << "Which array? 0 or 1" << endl;
      cin >> arraySel;

      (myBoard->Arrays[arraySel])->shiftin(&(msg.sdi), &(msg.rclk), &(msg.srclk), &pattern, msg.pattern);

      // for(Array* ledArray : myBoard->Arrays){
      //    ledArray->shiftin(msg.pattern);
      // }

      myClient->send(&msg);
      bzero(msg.pattern, ARRAY_SIZE);
      myClient->recieve(&msg);
      cout << "Recieved: ";
      for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
      cout << endl;


    }

  delete myBoard;

  myClient->stop();
  delete myClient;



}
