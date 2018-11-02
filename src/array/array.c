//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// array.c
// Description: Implementation of array hardware control and communication
//-----------------------------------------------------------------------------

#include "leddriver.h"
#include "../protocol.h"
#include "../protocol.c"

#define USAGE "USAGE %s port\n"
using namespace std;


int main(int argc, char *argv[]) {

  //-----------------------------------------------------
  if(!bcm2835_init()) return 1;
  if (argc < 2) { printf(USAGE, argv[0]);  return -1;}
  //-----------------------------------------------------
  Board* myBoard = new Board(2);
  myBoard->addArray(SDI, RCLK, SRCLK);
  myBoard->addArray(SDI_2, RCLK_2, SRCLK_2);
  
  //-----------------------------------------------------

  Server* myServer = new Server();
  myServer->start(argv[1]);

  Message msg;

  do {
      bzero(msg.pattern,ARRAY_SIZE);
      myServer->recieve(&msg);
      cout << "Recieved: ";
      for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
      cout << endl;
      myServer->send(&msg);

     cout <<  "Shifting in..." << endl;
     for(Array* ledArray : myBoard->Arrays){
        ledArray->shiftin(msg.pattern);
        pulse(ledArray->rclk());
     }

  } while (1);  //msg.flag != LAST);

  myServer->stop();
  delete myServer;




  bcm2835_close();
  delete myBoard;
  return 0;


}
