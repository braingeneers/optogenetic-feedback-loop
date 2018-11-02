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

using namespace std;


int main(int argc, char *argv[]) {

  Client* myClient = new Client();
  myClient->start(argv[1], argv[2]);

  Message msg;
  strcpy(msg.note, argv[3]);
  myClient->send(&msg);
  bzero(msg.note,30);
  myClient->recieve(&msg);
  printf("Received: %s\n",msg.note);

  myClient->stop();

  delete myClient;





  //cout << "Initializing Client..." << endl;
  //Client* masterClient = new Client();
  //cout << "Starting Server..." << endl;

/*  char* host = argv[1];
  //masterClient->start(host, atoi(argv[2]) );


//  Message msg;
  char array[8] = {0};
//  int last;

  //unsigned int buffer;
  for (;;) {
  //  msg.pattern[ARRAY_SIZE] = {0};

  //  array = rand() & rand();
    cout <<  "What array configuration?" << endl;
    cin >> array;
  //  for(int i=0;i<ARRAY_SIZE;i++) msg.pattern[i] = (array & (LED_MASK >> i)) > 0;
  //  cout << endl;
    //cout <<  "Last Message? Enter: 0 or 1" << endl;
    //cin >> last;
    //msg.flag = (last = 0) ? LAST : NONE;
  //  msg.flag = LAST;

    cout << "Sending Message with this array ..." << endl;
  //  for(int i=0; i<ARRAY_SIZE; i++){ cout << msg.pattern[i] << " "; }
  //  std::cout << std::endl;

  sendUDP(argv[3], host, atoi(argv[2]));
//    msg.size = htonl(array);
//    masterClient->send(&msg);


    delay(25);
    //  buffer = 0;//bzero(buffer,256);

    //  int n = recvfrom(sockfd, &buffer, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr, &len);
    //  if (n < 0) exit(-1);

      //printf("Received: %d\n", buffer);

      //if (buffer != 0){
      //  list.push_back(buffer);
        //cout << "My list is now: ";
        //print(list);
      //} else {
        //cout << "Sorting list";
    //    for(unsigned int num : list){
    //      n = sendto(sockfd, &num, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr, len);
    //      if (n < 0) exit(-1);
      //  }
        //list.clear();
      //}

  }


//  masterClient->stop();

*/
}
