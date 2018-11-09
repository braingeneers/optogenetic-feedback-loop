//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// array.c
// Description: Implementation of array hardware control and communication
//-----------------------------------------------------------------------------

#include "leddriver.h"
#include "../protocol.h"
#include "../protocol.c"

using namespace std;
#define USAGE "USAGE %s host port\n"
//Example: sudo ./array localhost 5001

int main(int argc, char *argv[]) {

  if (argc < 2) { printf(USAGE, argv[0]);  return -1;}

  //initizlize I/O
  initPins();

  //initialize Client
  Client* myClient = new Client();
  myClient->start(argv[1], argv[2]);

  //Announce your resrouce to Server
  Message msg;
  do {
    msg.flag = ANNOUNCE;
    statusPreSendMsg();
    myClient->send(&msg);
    statusSentMsg();
    statusAwaitingMsg();
    myClient->recieve(&msg);
    statusRecievedMsg();
  } while (msg.flag != ACCEPT);

  statusConnected();

  //Array control
  int exit = 0;
  do {
      statusAwaitingMsg();
      bzero(msg.pattern,ARRAY_SIZE);
      myClient->recieve(&msg);
      statusRecievedMsg();
      cout << "Recieved: ";
      for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
      cout << endl << "sdi: " << msg.sdi << endl << "rclk: " << msg.rclk << endl << "srclk: " << msg.srclk << endl << "FLAG:" << msg.flag << endl;
      if (msg.flag == LAST) exit = 1;
      msg.flag = ACK;
      statusPreSendMsg();
      myClient->send(&msg); //echo
      statusSentMsg();
      activate(msg.sdi, msg.rclk, msg.srclk, msg.pattern);

  } while (!exit);


  //Shut down Client
  myClient->stop();
  delete myClient;

  //Shut down I/0
  shutDownPins();

  return 0;


}
