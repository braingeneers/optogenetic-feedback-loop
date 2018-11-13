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

#define NONE      0
#define LAST      1
#define ANNOUNCE  2
#define ACCEPT    3
#define ACK       4


#define BUFFER_SIZE 128   //TCP message buffer

/*
 * UDP On-wire datagram.
 * All elements should be converted to network byte-order before transmission
 * and converted back to host byte-order on recepit.
 */

typedef struct message_t {
      bool pattern[ARRAY_SIZE];
      int sdi;
      int rclk;
      int srclk;
      int flag;
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
        void start(char * inPort);
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
      void start(char * inHost, char* inPort);
      void send(Message* msg);
      void recieve(Message* msg);
      void stop();
};


class TCPClient{
    private:
      int port;
      int sockfd;
     struct sockaddr_in serv_addr; //struct sockaddr_in remote_addr;
      struct hostent *server;
      int n;

    public:
    //  void runClient(char * argv1, char* argv2, char * argv3);
      void start(char * inHost, char* inPort);
      void send(char* pattern);
      void recieve(char* pattern);
      void stop();
};




class TCPServer {
      private:
        int port;
        int sockfd;
        int newsockfd;
        struct sockaddr_in server_addr;
  //      struct sockaddr_in remote_addr;
        int n;
        struct sockaddr_in client_addr;
        socklen_t len;

      public:
      //  void runServer(char* argv1);
        void start(char * inPort);
        void send(char* pattern);
        void recieve(char* pattern);
        void stop();
        void closeConnection();
        void openConnection();

};




#endif /*_PROTOCOL_H*/
