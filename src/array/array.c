#include "leddriver.h"
#include <iostream>

using namespace std;

int main(void) {

        if(!bcm2835_init()) return 1;


        while(1){

                int pattern;
//              pattern = rand() & rand();
                cout <<  "What array configuration?" << endl;
                cin >> pattern;
                cout << endl;

                //if(pattern == -1) break;
                SIPO(pattern);
                pulse(RCLK);
                delay(25);

//              SIPO(0);
//              pulse(RCLK);
//              delay(50);
                //digitalWrite(RCLK, 0);


        }

        bcm2835_close();

        return 0;
}




