//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// array.c
// Description: Implementation of array hardware control and communication
//-----------------------------------------------------------------------------

#include "leddriver.h"
#include "../protocol.h"
#include "../protocol.c"

#define USAGE "USAGE %s port\n"
using namespace std;


int main(int argc, char *argv[]) {

  Server* myServer = new Server();
  myServer->start(argv[1]);

  Message msg;

  for (;;) {
      bzero(msg.pattern,ARRAY_SIZE);
      myServer->recieve(&msg);
      cout << "Recieved: ";
      for(int i=0; i<ARRAY_SIZE;i++) cout << msg.pattern[i] << " ";
      cout << endl;
      myServer->send(&msg);
  }

  myServer->stop();

  delete myServer;


  /*
  if(!bcm2835_init()) return 1;

if (argc < 2) {
     printf(USAGE, argv[0]);
     return -1;
 }

  Board* myBoard = new Board(2);
  myBoard->addArray(SDI, RCLK, SRCLK);
  myBoard->addArray(SDI_2, RCLK_2, SRCLK_2);

  //cout << "Initializing Server..." << endl;
  //Server* masterServer = new Server();
  //cout << "Starting Server..." << endl;

//  masterServer->start(atoi(argv[1]));


  //  Message msg;
  //    int array;


    do{

        cout << "waiting for Message" << endl;
        //  masterServer->recieve(&msg);
        recieveUDP(atoi(argv[1]));
        //  cout << "Recieved the pattern: " << ntohl(msg.size) << endl;
          //for(int i=0; i<ARRAY_SIZE; i++){ cout << (bool) msg.pattern[i] << " "; }
        //std::cout << std::endl;
      //    cout << "Flag: " << msg.flag <<endl;

//          msg.pattern[ARRAY_SIZE] = {0};

          //int array = rand() & rand();
         cout <<  "What array configuration?" << endl;
          cin >> array;
          for(int i=0;i<ARRAY_SIZE;i++) {msg.pattern[i] = (array & (LED_MASK >> i)) > 0;}


         cout <<  "Shifting in..." << endl;
          for(Array* ledArray : myBoard->Arrays){
            ledArray->shiftin(msg.pattern);
            pulse(ledArray->rclk());
          }
*/
      /*  } while (1);//msg.flag != LAST);



    //    masterServer->stop();
        bcm2835_close();
        delete myBoard;
        return 0;


*/
}
