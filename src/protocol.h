//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// protocol.h
// Description: Header file for network protocol between array and master
//-----------------------------------------------------------------------------

#ifndef _PROTOCOL_H
#define _PROTOCOL_H

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

#include <functional>
#include "array/leddriver.h"

using namespace std;

/*
 * On-wire datagram.
 * All elements should be converted to network byte-order before transmission
 * and converted back to host byte-order on recepit.
 */

typedef struct message_t {
      bool pattern[ARRAY_SIZE];
      int sdi;
      int rclk;
      int srclk;
}
Message;


class Server {
      private:
        int port;
        int sockfd;
        socklen_t len;
        struct sockaddr_in server_addr;
        struct sockaddr_in remote_addr;
        int n;

      public:
      //  void runServer(char* argv1);
        void start(char * argv1);
        void send(Message * msg);
        void recieve(Message* msg);
        void stop();

};


class Client{
    private:
      int port;
      int sockfd;
      socklen_t len;
      struct sockaddr_in remote_addr;
      struct hostent *server;
      int n;

    public:
    //  void runClient(char * argv1, char* argv2, char * argv3);
      void start(char * argv1, char* argv2);
      void send(Message* msg);
      void recieve(Message* msg);
      void stop();
};



#endif /*_PROTOCOL_H*/
