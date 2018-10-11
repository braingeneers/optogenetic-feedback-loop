//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// array.c
// Description: Implementation of array hardware control and communication
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

#include "leddriver.h"
#include "../protocol.h"

using namespace std;


int main(int argc, char *argv[]) {
  if(!bcm2835_init()) return 1;
  int port = atoi(argv[1]);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) exit(-1);

  struct sockaddr_in server_addr;
  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) exit(-1);

  struct sockaddr_in remote_addr;
  socklen_t len = sizeof(remote_addr);

        //unsigned int num  = atoi(argv[3]);
      //  const unsigned int terminate = 0;

        //send list to server
      //  for(unsigned int &num : list){
      //        int n = sendto(sockfd, &num, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr,len);
      //        if (n < 0) exit(-1);
      //  }

        //end list transmission
        //int n = sendto(sockfd, &terminate, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr,len);
        //if (n < 0) exit(-1);

        //recieve sorted list
        Message msg;
        int n;


      //  for (unsigned int &num : list){
          //  unsigned int buffer; //char buffer[256];
            //buffer = 0; //bzero(buffer,256);
        do{
          n = recvfrom(sockfd, &msg, sizeof(msg), 0,(struct sockaddr *)&remote_addr, &len);
          if (n < 0) exit(-1);
          cout << "Recieved the pattern: ";
          for(int i; i<ARRAY_SIZE; i++){ cout << msg.pattern[i] << " "; }
          std::cout << std::endl;


          shiftin(msg.pattern);
          pulse(RCLK);
          delay(25);

        } while (msg.flag != LAST);


        close(sockfd);

        bcm2835_close();
        return 0;


}
