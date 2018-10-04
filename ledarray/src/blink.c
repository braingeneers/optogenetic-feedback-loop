// blink.c

#include <bcm2835.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN_17 RPI_GPIO_P1_11

void blink(int pin){
        // Turn it on
        bcm2835_gpio_write(pin, HIGH);
        // wait a bit
        bcm2835_delay(50);
        // turn it off
        bcm2835_gpio_write(pin, LOW);
        // wait a bit
        bcm2835_delay(500);
}


int main(int argc, char **argv){
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);

    if (!bcm2835_init())
      return 1;

    int pin;
    while (1){
        cout <<  "Blink pin?" ;
        cin >> pin;
	if(pin == 0) break;
        cout << "Blinking pin #" << pin << endl;
       // Set the pin to be an output
       bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);


        // Blink
        blink(pin);
    }

    bcm2835_close();
    return 0;
}
