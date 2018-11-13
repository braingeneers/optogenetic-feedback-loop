#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../protocol.h"
#include "../protocol.c"



int main(int argc, char *argv[]) {

    TCPServer* myTCPServer = new TCPServer();
    myTCPServer->start(argv[1]);
    char buffer[BUFFER_SIZE];

    myTCPServer->openConnection();
    for (;;) {
        bzero(buffer,BUFFER_SIZE);
        myTCPServer->recieve(buffer);
        printf("Received: %s\n", buffer);
        myTCPServer->send(buffer);
    }
    myTCPServer->closeConnection();

    myTCPServer->stop();
    delete myTCPServer;


     return 0;
}
