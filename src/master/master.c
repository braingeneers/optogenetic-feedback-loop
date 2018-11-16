//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// master.c
// Description: Master program for synthesizing virtual organoid model,
//       top-level supervisor algorithm, array stimulation, and visual display
//-----------------------------------------------------------------------------

#include <iostream>
#include <iterator>
#include <vector>
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
//#include "../protocol.c"
#include "../array/leddriver.h"
//#include "../array/leddriver.c"
using namespace std;

#define USAGE "USAGE %s listening-port organoid-host organoid-port\n"
//Example: sudo ./master 5001 localhost 5002

std::string asString(const std::chrono::system_clock::time_point& tp){
    // convert to system time:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);// convert to calendar time
    ts.resize(ts.size()-1); // skip trailing newline
    return ts;
}




int main(int argc, char *argv[]) {

    if (argc < 3) { printf(USAGE, argv[0]); return -1; }

    //initialize Organoid Client
    TCPClient* myTCPClient = new TCPClient();
    myTCPClient->start(argv[2], argv[3]);
    char buffer[BUFFER_SIZE];

    //initialize Array Board Server
    Server* myServer = new Server();
    myServer->start(argv[1]);


    //Register Boards
    Message msg;
    myServer->recieve(&msg);
    msg.flag = ACCEPT;
    myServer->send(&msg);

    cout << "Accepted!\n";

    //------------------------
    Board* myBoard = new Board(1);
    myBoard->addArray(SDI, RCLK, SRCLK);
    int pattern, arraySel, last;
    int boardSel = 0;
    std::string line;
    std::string token;
    std::chrono::system_clock::time_point tp;
    //------------------------

    ofstream outlog;
    outlog.open ("log.txt");


    while(1){

            arraySel=0;
            pattern = rand() & rand() & 0xFF;
            last = 0;

//---------------communicate with organoid ---------------
            snprintf(buffer, BUFFER_SIZE, "%d", pattern);
            myTCPClient->send(buffer); //pattern as char string


             bzero(buffer, BUFFER_SIZE);

             myTCPClient->recieve(buffer);
             printf("Received from organoid: %s\n", buffer);
             //can now acess JPEG

//---------------communicate with organoid ---------------


          (myBoard->Arrays[arraySel])->shiftin(&(msg.sdi), &(msg.rclk), &(msg.srclk), &pattern, msg.pattern);
          msg.flag = last;
          // for(Array* ledArray : myBoard->Arrays){
          //    ledArray->shiftin(msg.pattern);
          // }

          myServer->send(&msg);
          tp = std::chrono::system_clock::now();
          outlog <<  asString(tp) << "    " << "Board: " << boardSel << "   " << "Array: " << arraySel << "   " << "Pattern: " << pattern << endl;
          bzero(msg.pattern, ARRAY_SIZE);
          //do{
            myServer->recieve(&msg);
        //  } while (msg.flag != ACK)
          cout << "Recieved: ";
          for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
          cout << "Flag: " << msg.flag << endl;
          if (msg.flag == LAST) break;
          delay(50);

  }


  outlog.close();

  delete myBoard;

  myServer->stop();
  delete myServer;

  myTCPClient->stop();
  delete myTCPClient;

  return 0;

}
