//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// protocol.h
// Description: Implementation of network protocol between array and master
//-----------------------------------------------------------------------------

#include "array/leddriver.h"
#include "protocol.h"


//-------------------------------UDP Server------------------------------------
void Server::start(char * inPort){
    port = atoi(inPort);

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


void Server::send(Message* msg){
    n = sendto(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, len);
    if (n < 0) exit(-1);
}


void Server::recieve(Message* msg) {
    n = recvfrom(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, &len);
    if (n < 0) exit(-1);
}

void Server::stop(){ close(sockfd);}

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



//-------------------------------UDP Client------------------------------------

void Client::start(char * inHost, char* inPort){
      port = atoi(inPort);

      sockfd = socket(AF_INET, SOCK_DGRAM, 0);
      if (sockfd < 0) exit(-1);

      server = gethostbyname(inHost);
      if (server == NULL) exit(-1);

     bzero((char *) &remote_addr, sizeof(remote_addr));
     remote_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
     remote_addr.sin_port = htons(port);

     len = sizeof(remote_addr);

}

void Client::send(Message* msg){
    n = sendto(sockfd, msg, sizeof(*msg), 0, (struct sockaddr *)&remote_addr, len);
    if (n < 0) exit(-1);
}


void Client::recieve(Message* msg){
    n = recvfrom(sockfd, msg, sizeof(*msg), 0,(struct sockaddr *)&remote_addr, &len);
    if (n < 0) exit(-1);
}


void Client::stop(){ close(sockfd);}


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



//-------------------------------TCP Client------------------------------------

void TCPClient::start(char * inHost, char* inPort){
      port = atoi(inPort);

      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0) exit(-1);

      server = gethostbyname(inHost);
      if (server == NULL) exit(-1);

      bzero((char *) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
      serv_addr.sin_port = htons(port);

      if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) exit(-1);

}

void TCPClient::send(char* pattern){
    n = write(sockfd,pattern,strlen(pattern));
    if (n < 0) exit(-1);
}

void TCPClient::recieve(char* pattern){
    n = read(sockfd,pattern,BUFFER_SIZE-1);
    if (n < 0) exit(-1);
}

void TCPClient::stop(){ close(sockfd);}




//-------------------------------TCP Server------------------------------------

void TCPServer::start(char* inPort){
      port = atoi(inPort);

      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0) exit(-1);

      bzero((char *) &server_addr, sizeof(server_addr));
      server_addr.sin_family = AF_INET;
      server_addr.sin_addr.s_addr = INADDR_ANY;
      server_addr.sin_port = htons(port);

      if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) exit(-1);

      listen(sockfd,5);

      len = sizeof(client_addr);

}


void TCPServer::send(char* pattern){
  n = write(newsockfd,pattern,strlen(pattern));
  if (n < 0) exit(-1);
}

void TCPServer::recieve(char* pattern){
  int n = recv(newsockfd,pattern,BUFFER_SIZE-1,0);
  if (n < 0) exit(-1);
}

void TCPServer::openConnection(){
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len);
    if (newsockfd < 0) exit(-1);
}

void TCPServer::closeConnection(){ close(newsockfd); }

void TCPServer::stop(){ close(sockfd);}
