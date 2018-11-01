//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// leddriver.c
// Description: Driver for LED array using parallel shift registers
//-----------------------------------------------------------------------------

#include "leddriver.h"


void pulse(int pin){
	bcm2835_gpio_write(pin, LOW);
	bcm2835_gpio_write(pin, HIGH);
}

void Array::shiftin(bool *pattern){
	int i;
	bool out;

  std::cout <<  "Set array by shiftin()" << std::endl;
	for(i=0;i<ARRAY_SIZE;i++){
		//out = (byte & (LED_MASK >> i)) > 0;
		out = pattern[i];
		printf("out: %d, %x\n", out, out);
		bcm2835_gpio_write(this->sdi_, out);
		pulse(this->srclk_);
	}

}

void Array::init(int sdi, int rclk, int srclk){
		    std::cout <<  "Initializing Array!!" << std::endl;
				this->sdi_ = sdi;
				this->rclk_ = rclk;
				this->srclk_ = srclk;

				//set  pins as outputs
				bcm2835_gpio_fsel(this->sdi_, BCM2835_GPIO_FSEL_OUTP);
				bcm2835_gpio_fsel(this->rclk_, BCM2835_GPIO_FSEL_OUTP);
				bcm2835_gpio_fsel(this->srclk_, BCM2835_GPIO_FSEL_OUTP);

				//initialize all pins to be low
				bcm2835_gpio_write(	this->sdi_, LOW);
				bcm2835_gpio_write(	this->rclk_, LOW);
				bcm2835_gpio_write(	this->srclk_, LOW);

				//shift zeroes into the chip to clear the array
			  std::cout <<  "Flash!" << std::endl;
				bool pattern[ARRAY_SIZE] = {0};
				shiftin(pattern);
        delay(STANDARD_DELAY);

}
