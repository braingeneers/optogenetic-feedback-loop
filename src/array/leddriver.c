#include "leddriver.h"


void pulse(int pin){
	bcm2835_gpio_write(pin, LOW);
	bcm2835_gpio_write(pin, HIGH);
}

void shiftin(bool *array){
	int i;
	bool out;

	for(i=0;i<ARRAY_SIZE;i++){
		//out = (byte & (LED_MASK >> i)) > 0;

		out = array[i];
		printf("out: %d, %x\n", out, out);
		bcm2835_gpio_write(SDI, out);
		pulse(SRCLK);
	}

}

void init(void){
				//set  pins as outputs
				bcm2835_gpio_fsel(SDI, BCM2835_GPIO_FSEL_OUTP);
				bcm2835_gpio_fsel(RCLK, BCM2835_GPIO_FSEL_OUTP);
				bcm2835_gpio_fsel(SRCLK, BCM2835_GPIO_FSEL_OUTP);

				//initialize all pins to be low
				bcm2835_gpio_write(SDI, LOW);
				bcm2835_gpio_write(RCLK, LOW);
				bcm2835_gpio_write(SRCLK, LOW);

				//shift zeroes into the chip to clear the array
				bool array[ARRAY_SIZE] = {0};
        shiftin(array);
        pulse(RCLK);
        delay(50);

}
