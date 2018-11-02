//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// protocol.h
// Description: Implementation of network protocol between array and master
//-----------------------------------------------------------------------------


#include "array/leddriver.h"
#include "protocol.h"


//-----------------------------Server-------------------------------------------
void Server::start(int port){

       port_ = port;
       sockfd_= socket(AF_INET, SOCK_DGRAM, 0);
       if (sockfd_ < 0) exit(-1);

       bzero((char *) &server_addr, sizeof(server_addr));

       server_addr.sin_family = AF_INET;
       server_addr.sin_addr.s_addr = INADDR_ANY;
       server_addr.sin_port = htons(port_);

       if (bind(sockfd_, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) exit(-1);

       len_ = sizeof(remote_addr);

}


void Server::recieve(Message* msgo){
      Message msg;
       n_ = recvfrom(sockfd_, &msg, sizeof(msg), 0,(struct sockaddr *)&remote_addr, &len_);
       printf("Size: %d", ntohl(msg.size));
       if (n_ < 0) exit(-1);
}



void Server::stop(){ close(sockfd_); }

//---------------------------Client---------------------------------------------

void Client::start(char* host, int port){
  port_ = port;
  sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd_ < 0) exit(-1);

  //struct hostent *
  server = gethostbyname(host);
  if (server == NULL) exit(-1);

  bzero((char *) &remote_addr, sizeof(remote_addr));
  remote_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
  remote_addr.sin_port = htons(port_);

  len_ = sizeof(remote_addr);

}

void Client::send(Message* msg){
      n_ = sendto(sockfd_, &msg, sizeof(msg), 0, (struct sockaddr *)&remote_addr, len_);
            std::cout << "sending..! " << port_ << std::endl ;
      if (n_ < 0) exit(-1);
      std::cout << "success!\n";
}


void Client::stop(){ close(sockfd_); }
