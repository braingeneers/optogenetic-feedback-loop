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

#define USAGE "USAGE %s host port command-file\n"


int main(int argc, char *argv[]) {

    if (argc < 3) { printf(USAGE, argv[0]); return -1; }
    std::cout << "Command file: " << argv[1] << std::endl;

    Client* myClient = new Client();
    myClient->start(argv[1], argv[2]);

    //------------------------
    Board* myBoard = new Board(2);
    myBoard->addArray(SDI, RCLK, SRCLK);
    myBoard->addArray(SDI_2, RCLK_2, SRCLK_2);
    int  pattern;
    int arraySel;
    int last;
    Message msg;
    std::string line;
    std::string token;
    //------------------------

    std::ifstream ifs(argv[3]);
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
                  cout << "!!!!!!!!" << endl;
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



          (myBoard->Arrays[arraySel])->shiftin(&(msg.sdi), &(msg.rclk), &(msg.srclk), &pattern, msg.pattern);
          msg.flag = last;
          // for(Array* ledArray : myBoard->Arrays){
          //    ledArray->shiftin(msg.pattern);
          // }

          myClient->send(&msg);
          bzero(msg.pattern, ARRAY_SIZE);
          myClient->recieve(&msg);
          cout << "Recieved: ";
          for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
          cout << endl;
          if (msg.flag ==LAST) break;
          delay(1000);

         }
       }


   }

  delete myBoard;

  myClient->stop();
  delete myClient;

  return 0;


}
