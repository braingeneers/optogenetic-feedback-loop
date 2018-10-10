#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define   SDI   27   //serial data input
#define   RCLK  28   //memory clock input(STCP)
#define   SRCLK 29   //shift register clock input(SHCP)

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void pulse(int pin){
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

void SIPO(unsigned char byte){
	int i;
	int out;

	for(i=0;i<8;i++){
		out = ((byte & (0x80 >> i)) > 0);
//		printf("out: %d, %x\n", out, out);
		digitalWrite(SDI, out);
		pulse(SRCLK);
	}

}

void init(void){
	pinMode(SDI, OUTPUT); //make P0 output
	pinMode(RCLK, OUTPUT); //make P0 output
	pinMode(SRCLK, OUTPUT); //make P0 output

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

int main(void) {


	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();

	while(1){

		int pattern;
		cout <<  "What array configuration?" << endl;
		cin >> pattern;
		cout << endl;

		SIPO(pattern);
		pulse(RCLK);
		//digitalWrite(RCLK, 0);


	}

	return 0;
}
