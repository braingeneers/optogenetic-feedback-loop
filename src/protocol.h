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
    bool pattern[ARRAY_SIZE]; // Sorted or to-be sorted numbers if FLAG is NONE or LAST
                                    // Missing sequence numbers if FLAG is RESEND
  //  unsigned int size; // Number of valid entries in VALUES
    unsigned int sequence;   // Unique sequence number of trasmission batch, starting at zero
    unsigned int flag;       // One of NONE, LAST, RESEND
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


void Server::start(int dport){
      std::cout<< "1" << endl;
       port_ = dport;
       sockfd_= socket(AF_INET, SOCK_DGRAM, 0);
       if (sockfd_ < 0) exit(-1);

      std::cout<< "2" << endl;
       bzero((char *) &server_addr, sizeof(server_addr));
             std::cout<< "3" << endl;
       server_addr.sin_family = AF_INET;
       server_addr.sin_addr.s_addr = INADDR_ANY;
       server_addr.sin_port = htons(port_);

      std::cout<< "4" << endl;
       if (bind(sockfd_, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) exit(-1);

      std::cout<< "5" << endl;
       len_ = sizeof(remote_addr);

}



void Server::recieve(Message* msg){
       n_ = recvfrom(sockfd_, &msg, sizeof(msg), 0,(struct sockaddr *)&remote_addr, &len_);
       if (n_ < 0) exit(-1);
}




void Server::stop(){ close(sockfd_); }








#endif /*_PROTOCOL_H*/
