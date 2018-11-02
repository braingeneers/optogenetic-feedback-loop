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
//#define MAX_VALUES 128

#define NONE    0 // Default flag for on-wire datagram
#define LAST    1 // Identifies last datagram in batch
#define RESEND  2 // Request for a re-send of missing batches
                   // If set, VALUES contains the sequence numbers of missing batches

/*
 * On-wire datagram.
 * All elements should be converted to network byte-order before transmission
 * and converted back to host byte-order on recepit.
 */

typedef struct message_t {
    //bool pattern[ARRAY_SIZE]; // Sorted or to-be sorted numbers if FLAG is NONE or LAST
                                    // Missing sequence numbers if FLAG is RESEND
     int size; // Number of valid entries in VALUES
//    unsigned int sequence;   // Unique sequence number of trasmission batch, starting at zero
  //  unsigned int flag;       // One of NONE, LAST, RESEND
}
Message;


class Server {
      private:
        int sockfd_;
        int port_;
        int n_;
        struct sockaddr_in server_addr;
        struct sockaddr_in remote_addr;
        socklen_t len_;

      public:
        void start(int dport);
        void stop();
        void recieve(Message* msg);

};


class Client{
    private:
      int sockfd_;
      int port_;
      int n_;
      struct hostent *server;
      struct sockaddr_in remote_addr;
      socklen_t len_;

    public:
      void start(char* host, int port);
      void stop();
      void send(Message* msg);

};




#endif /*_PROTOCOL_H*/
