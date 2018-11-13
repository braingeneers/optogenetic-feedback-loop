#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

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

int main(int argc, char *argv[]){

    TCPClient* myTCPClient = new TCPClient();
    myTCPClient->start(argv[1], argv[2]);

    int pattern;
    char buffer[BUFFER_SIZE];

    while(1){
        bzero(buffer, BUFFER_SIZE);
        std::cout << "What pattern?" << std::endl;
        std::cin >> pattern;

        snprintf(buffer, BUFFER_SIZE, "%d", pattern);
        std::cout << "Pattern is: " << buffer << std::endl;

        myTCPClient->send(buffer); //pattern as char string

         bzero(buffer, BUFFER_SIZE);

         myTCPClient->recieve(buffer);
         printf("Received from organoid: %s\n", buffer);

         //can now acess JPEG


     }


     myTCPClient->stop();
     delete myTCPClient;

     return 0;

}
