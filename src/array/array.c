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

sem_t announceExit;

void announce(Message msg, Client myClient){
  int sval;
  for(;;){
    statusPreSendMsg();
    myClient.send(&msg);
    statusSentMsg();
  //  for(int i=0; i==99999999; i++){}//
    delay(1000);
    if(!sem_getvalue(&announceExit, &sval)) cout << "sval: " << sval << endl;
    else exit(-1);
    if (sval == 1) return;
  }
}

int main(int argc, char *argv[]) {

  if (argc < 2) { printf(USAGE, argv[0]);  return -1;}

  //initizlize I/O
  initPins();

  //initialize Client
  Client* myClient = new Client();
  myClient->start(argv[1], argv[2]);

  //Announce your resrouce to Server
  Message msg;
  msg.flag = ANNOUNCE;
  cout << "Thread\n";


  sem_init(&announceExit, 0, 1);
  sem_wait(&announceExit);
  std::thread t (announce, msg, *myClient);
  cout << "After thread\n";
  Message rcvmsg;


  do{
    statusAwaitingMsg();
    cout << "Recieving\n";
    myClient->recieve(&rcvmsg);
  } while (rcvmsg.flag != ACCEPT);

  sem_post(&announceExit);
  cout << "Recieved, accepted\n";


  if(t.joinable()) t.join();
  sem_destroy(&announceExit);

  cout << "Joined\n";

  statusRecievedMsg();

  statusConnected();
  cout << "Accepted!\n";

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
