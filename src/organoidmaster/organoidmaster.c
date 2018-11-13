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

    myTCPClient->send(argv[3]);

     char buffer[BUFFER_SIZE];
     bzero(buffer, BUFFER_SIZE);

     myTCPClient->recieve(buffer);
     printf("Received: %s\n", buffer);

     myTCPClient->stop();
     delete myTCPClient;

     return 0;

}
