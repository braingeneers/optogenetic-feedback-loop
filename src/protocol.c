//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// protocol.h
// Description: Implementation of network protocol between array and master
//-----------------------------------------------------------------------------


#include "array/leddriver.h"
#include "protocol.h"



/*void Client::runClient(char * argv1, char* argv2, char * argv3){
   start(argv1, argv2);

   Message msg;
   strcpy(msg.note, argv3);
   send(&msg);
   bzero(msg.note,30);
   recieve(&msg);
   printf("Received: %s\n",msg.note);

   stop();
}*/

/*void Server::runServer(char* argv1) {
   start(argv1);
   Message msg;

   for (;;) {
       bzero(msg.note,30);
       recieve(&msg);
       printf("Received: %s\n", msg.note);
       send(&msg);
   }

   stop();

}*/

void Server::start(char * argv1){
    port = atoi(argv1);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) exit(-1);

     bzero((char *) &server_addr, sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_addr.s_addr = INADDR_ANY;
     server_addr.sin_port = htons(port);

     if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
     exit(-1);

     len = sizeof(remote_addr);
}


void Client::start(char * argv1, char* argv2){
  port = atoi(argv2);

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) exit(-1);

  server = gethostbyname(argv1);
  if (server == NULL) exit(-1);

 bzero((char *) &remote_addr, sizeof(remote_addr));
 remote_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
 remote_addr.sin_port = htons(port);

 len = sizeof(remote_addr);

}


void Server::send(Message* msg){
  n = sendto(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, len);
  if (n < 0) exit(-1);
}

void Server::recieve(Message* msg) {
  n = recvfrom(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, &len);
  if (n < 0) exit(-1);

}
void Server::stop(){ close(sockfd);}

void Client::recieve(Message* msg){
  n = recvfrom(sockfd, msg, sizeof(*msg), 0,(struct sockaddr *)&remote_addr, &len);
  if (n < 0) exit(-1);
}

void Client::send(Message* msg){
  n = sendto(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, len);
  if (n < 0) exit(-1);
}

void Client::stop(){ close(sockfd);}
