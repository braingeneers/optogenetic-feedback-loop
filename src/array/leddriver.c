#include "leddriver.h"


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

