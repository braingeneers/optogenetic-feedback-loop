#include <bcm2835.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define   SDI   16 //27   //serial data input
#define   RCLK  20 //28   //memory clock input(STCP)
#define   SRCLK 21 //29   //shift register clock input(SHCP)

//unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

#define LEDS 24 //leds per organoid
#define LED_MASK 0x800000


void pulse(int pin){
	bcm2835_gpio_write(pin, LOW);
	bcm2835_gpio_write(pin, HIGH);
}

void SIPO(unsigned int byte){
	int i;
	int out;

	for(i=0;i<LEDS;i++){
		out = (byte & (LED_MASK >> i)) > 0;
		printf("out: %d, %x\n", out, out);
		bcm2835_gpio_write(SDI, out);
		pulse(SRCLK);
	}

}

void init(void){
	bcm2835_gpio_fsel(SDI, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RCLK, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(SRCLK, BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_write(SDI, LOW);
	bcm2835_gpio_write(RCLK, LOW);
	bcm2835_gpio_write(SRCLK, LOW);

        SIPO(0);
        pulse(RCLK);
        delay(50);

}


int main(void) {

	if(!bcm2835_init()) return 1;


	while(1){

		int pattern;
//		pattern = rand() & rand();
		cout <<  "What array configuration?" << endl;
		cin >> pattern;
		cout << endl;

		//if(pattern == -1) break;
		SIPO(pattern);
		pulse(RCLK);
		delay(25);

//		SIPO(0);
//		pulse(RCLK);
//		delay(50);
		//digitalWrite(RCLK, 0);


	}

	bcm2835_close();

	return 0;
}
