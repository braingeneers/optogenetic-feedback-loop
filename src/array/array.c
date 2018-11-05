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

  if (argc < 2) { printf(USAGE, argv[0]);  return -1;}
 
  //initizlize I/O
  if(!bcm2835_init()) return 1;
  initPins();

  //initialize Server
  Server* myServer = new Server();
  myServer->start(argv[1]);

  //Array control
  Message msg;
  do {
      bzero(msg.pattern,ARRAY_SIZE);
      myServer->recieve(&msg);
      cout << "Recieved: ";
      for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
      cout << "sdi: " << msg.sdi << endl << "rclk: " << msg.rclk << endl << "srclk: " << msg.srclk << endl << endl;
      myServer->send(&msg); //echo
      activate(msg.sdi, msg.rclk, msg.srclk, msg.pattern);

  } while (msg.flag != LAST);


  //Shut down Server
  myServer->stop();
  delete myServer;

  //Shut down I/0
  bcm2835_close();

  return 0;


}
