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

using namespace std;


int main(int argc, char *argv[]) {
  //std::vector<unsigned int> list;

  //cout << "I'm server!";


  int port = atoi(argv[2]);
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) exit(-1);

  struct hostent *server = gethostbyname(argv[1]);
  if (server == NULL) exit(-1);

  struct sockaddr_in remote_addr;
  bzero((char *) &remote_addr, sizeof(remote_addr));
  remote_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
  remote_addr.sin_port = htons(port);

  socklen_t len = sizeof(remote_addr);

  int n;
  Message msg;

  //unsigned int buffer;
  for (;;) {

    msg.pattern[ARRAY_SIZE] = {0};

    int array = rand() & rand();
  //  cout <<  "What array configuration?" << endl;
  //  cin >> array;
    for(int i=0;i<ARRAY_SIZE;i++) msg.pattern[i] = (array & (LED_MASK >> i)) > 0;
    cout << endl;
    msg.flag = NONE;




    cout << "Sending Message with this array: " << endl;
    for(int i; i<ARRAY_SIZE; i++){ cout << msg.pattern[i] << " "; }
    std::cout << std::endl;


    n = sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&remote_addr, len);
    if (n < 0) exit(-1);

    cout << "Message sent!" << endl;

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




 close(sockfd);


}
