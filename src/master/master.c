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
#include "../protocol.c"
#include "../array/leddriver.h"
#include "../array/leddriver.c"
using namespace std;

#define USAGE "USAGE %s port command-file\n"
//Example: sudo ./master 5001 command.txt


std::string asString(const std::chrono::system_clock::time_point& tp){
    // convert to system time:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);// convert to calendar time
    ts.resize(ts.size()-1); // skip trailing newline
    return ts;
}


int main(int argc, char *argv[]) {

    if (argc < 3) { printf(USAGE, argv[0]); return -1; }
    std::cout << "Command file: " << argv[2] << std::endl;

    //initialize Client
    Server* myServer = new Server();
    myServer->start(argv[1]);


    //Register Boards
    Message msg;
    myServer->recieve(&msg);
    msg.flag = ACCEPT;
    myServer->send(&msg);

    //------------------------
    Board* myBoard = new Board(1);
    myBoard->addArray(SDI, RCLK, SRCLK);
    int pattern;
    int arraySel;
    int boardSel = 0;
    int last;
    std::string line;
    std::string token;
    std::chrono::system_clock::time_point tp;
    //------------------------

    ofstream outlog;
    outlog.open ("log.txt");

    // later, use log as such:

    std::ifstream ifs(argv[2]);
    if (ifs) {

     while (std::getline(ifs, line)) {
          //  bzero(msg.pattern, ARRAY_SIZE);   //  memset(msg.pattern, false, ARRAY_SIZE);
          //for(bool b : msg.pattern) b = true;

        /*  cout <<  "What array configuration?" << endl;
          cin >> pattern;
          cout << "Which array? 0 or 1" << endl;
          cin >> arraySel;
          cout << "Last Message? 0==No, 1==Yes" << endl;
          cin >> last;*/

         if (!line.empty()){
            //format: pattern array last
              std::stringstream stream(line);
              last = 0;
              stream >> token;
              if (token.find("#") == 0 || token == "\n" || token == " "){ //break;
                    continue;
              }
              std::cout << "TOKEN IS: " << token << '\n';
              pattern = stoi(token);
              stream >> token;
              std::cout << "TOKEN IS: " <<token << '\n';
              arraySel = stoi(token);
              if(stream >> token){
                  std::cout << "TOKEN IS: " <<token << '\n';
                  last = stoi(token);
              }

            /*arraySel=0;
            pattern = rand() & rand() & 0xFF;
            last = 0;*/

          (myBoard->Arrays[arraySel])->shiftin(&(msg.sdi), &(msg.rclk), &(msg.srclk), &pattern, msg.pattern);
          msg.flag = last;
          // for(Array* ledArray : myBoard->Arrays){
          //    ledArray->shiftin(msg.pattern);
          // }

          myServer->send(&msg);
          tp = std::chrono::system_clock::now();
          outlog <<  asString(tp) << "    " << "Board: " << boardSel << "   " << "Array: " << arraySel << "   " << "Pattern: " << pattern << endl;
          bzero(msg.pattern, ARRAY_SIZE);
          myServer->recieve(&msg);
          cout << "Recieved: ";
          for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
          cout << endl;
          if (msg.flag == LAST) break;
          delay(50);

         }
       }
     }


  outlog.close();

  delete myBoard;

  myServer->stop();
  delete myServer;

  return 0;


}
