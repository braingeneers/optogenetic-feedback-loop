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
  Array* myArray_first =  new Array;
  Array* myArray_second =  new Array;
  myArray_first->init(SDI, RCLK, SRCLK);
  myArray_second->init(SDI_2, RCLK_2, SRCLK_2);
/*  int port = atoi(argv[1]);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) exit(-1);

  struct sockaddr_in server_addr;
  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) exit(-1);

  struct sockaddr_in remote_addr;
  socklen_t len = sizeof(remote_addr);*/

      Message msg;
      //  int n;

        int array;


      //  for (unsigned int &num : list){
          //  unsigned int buffer; //char buffer[256];
            //buffer = 0; //bzero(buffer,256);
        do{
        /*  n = recvfrom(sockfd, &msg, sizeof(msg), 0,(struct sockaddr *)&remote_addr, &len);
          if (n < 0) exit(-1);
          cout << "Recieved the pattern: ";
          for(int i; i<myArray->arraySize; i++){ cout << msg.pattern[i] << " "; }
          std::cout << std::endl;
*/
          msg.pattern[ARRAY_SIZE] = {0};

//int array = rand() & rand();
          cout <<  "What array configuration?" << endl;
          cin >> array;
          for(int i=0;i<ARRAY_SIZE;i++) {msg.pattern[i] = (array & (LED_MASK >> i)) > 0;}
          cout <<  "Shifting in..." << endl;

          myArray_first->shiftin(msg.pattern);
          pulse(myArray_first->rclk());

          myArray_second->shiftin(msg.pattern);
          pulse(myArray_second->rclk());


        } while (1); //msg.flag != LAST);


      //  close(sockfd);

        bcm2835_close();
        delete myArray_first;
        delete myArray_second;
        return 0;


}
