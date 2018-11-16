//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// leddriver.c
// Description: Driver for LED array using parallel shift registers
//-----------------------------------------------------------------------------

#include "leddriver.h"
#include <bcm2835.h>

const int pins[] = {SDI, RCLK, SRCLK, SDI_2, RCLK_2, SRCLK_2, IND_SERVER_CONNECTION, IND_SERVER_MSG_RCV, IND_CLIENT_POWER, IND_CLIENT_MSG_SEND};
const int indPins[] = {IND_SERVER_CONNECTION, IND_SERVER_MSG_RCV, IND_CLIENT_POWER, IND_CLIENT_MSG_SEND};

void initPins(){	//set  pins as outputs
	if(!bcm2835_init()) exit(1);

	//initialize all pins to be outputs, initially low
	for (int pin : pins){
			bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
			bcm2835_gpio_write(pin, LOW);
	}

	//flash indication leds to ensure they work
	for (int indPin : indPins){ bcm2835_gpio_write(indPin, HIGH);}
	delay(LONG_DELAY);
	for (int indPin : indPins){ bcm2835_gpio_write(indPin, LOW);}

	//turn power indication LED on
	bcm2835_gpio_write(IND_CLIENT_POWER, HIGH);

}


void shutDownPins(){
	for (int pin : pins){ bcm2835_gpio_write(pin, LOW); }
	bcm2835_close();
}


void statusConnected(){	bcm2835_gpio_write(IND_SERVER_CONNECTION, HIGH); }

void statusPreSendMsg() {bcm2835_gpio_write(IND_CLIENT_MSG_SEND, HIGH); }
void statusSentMsg(){ bcm2835_gpio_write(IND_CLIENT_MSG_SEND, LOW); }

void statusAwaitingMsg(){ bcm2835_gpio_write(IND_SERVER_MSG_RCV, LOW); }
void statusRecievedMsg(){ bcm2835_gpio_write(IND_SERVER_MSG_RCV, HIGH); }



void pulse(int pin){
		bcm2835_gpio_write(pin, LOW);
		bcm2835_gpio_write(pin, HIGH);
}


void activate(int sdi, int rclk, int srclk, bool * pattern){
			int i;
			bool out;

		  std::cout <<  "Set array by shiftin()" << std::endl;
			for(i=0;i<ARRAY_SIZE;i++){
				//out = (byte & (LED_MASK >> i)) > 0;
				out = pattern[i];
				printf("out: %d\n", out);
				bcm2835_gpio_write(sdi, out);
				pulse(srclk);
			}
			pulse(rclk);

}
