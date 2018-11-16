#include <iostream>
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

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include "opencv2/opencv.hpp"
//using namespace cv;

using namespace std;

//usage: ./organoidmast localhost 5001
void supervisor(int* pattern){
  std::cout << "What pattern?" << std::endl;
  std::cin >> *pattern;
}


int main(int argc, char *argv[]){

    TCPClient* myTCPClient = new TCPClient();
    myTCPClient->start(argv[1], argv[2]);

    int pattern;
    char buffer[BUFFER_SIZE];

    while(1){
        bzero(buffer, BUFFER_SIZE);

        supervisor(&pattern);

        snprintf(buffer, BUFFER_SIZE, "%d", pattern);
        std::cout << "Pattern is: " << buffer << std::endl;
        myTCPClient->send(buffer); //pattern as char string

        bzero(buffer, BUFFER_SIZE);
        myTCPClient->recieve(buffer);
        printf("Received from organoid: %s\n", buffer);

         //can now acess JPEG


     }


     myTCPClient->stop();
     delete myTCPClient;

     return 0;

}

/*

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
*/
