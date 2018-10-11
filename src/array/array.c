#include "leddriver.h"
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

using namespace std;

void print(std::vector<unsigned int> &bucket){
    for(unsigned int &num : bucket){ std::cout << num << " "; }
    std::cout << std::endl;
}

int main(void) {

        if(!bcm2835_init()) return 1;

        bool array[24] = {0};
        int i;
        while(1){
                int pattern; // pattern = rand() & rand();
                cout <<  "What array configuration?" << endl;
                cin >> pattern;
                for(i=0;i<ARRAY_SIZE;i++)
                    array[i] = (pattern & (LED_MASK >> i)) > 0;

                cout << endl;

                shiftin(array);
                pulse(RCLK);
                delay(25);
        }

        bcm2835_close();
        return 0;
}
/*
int main(int argc, char *argv[]) {
  std::vector<std::vector<unsigned int> > lists;
  std::vector<unsigned int> list1 = {1, 2345, 4567, 45643, 123, 789765, 2345, 7};
  std::vector<unsigned int> list2 = {2, 34554, 4541, 2345, 4567, 45643, 123, 789765, 2345, 8};
  lists.push_back(list1); lists.push_back(list2);


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

  //unsigned int num  = atoi(argv[3]);
  const unsigned int terminate = 0;
  for(std::vector<unsigned int> &list : lists){
    //std::cout << "New List: ";
    //print(list);

    //send list to server
      for(unsigned int &num : list){
          int n = sendto(sockfd, &num, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr,len);
          if (n < 0) exit(-1);
      }
      //end list transmission
      int n = sendto(sockfd, &terminate, sizeof(unsigned int), 0, (struct sockaddr *)&remote_addr,len);
      if (n < 0) exit(-1);

      //recieve sorted list
      for (unsigned int &num : list){
        //  unsigned int buffer; //char buffer[256];
          //buffer = 0; //bzero(buffer,256);
          n = recvfrom(sockfd, &num, sizeof(unsigned int), 0,(struct sockaddr *)&remote_addr, &len);
          if (n < 0) exit(-1);
      }

      //printf("Received list:");
      //print(list);
  }

  close(sockfd);

}
*/
