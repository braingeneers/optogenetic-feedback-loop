//-----------------------------------------------------------------------------
// Kateryna Voitiuk (kvoitiuk@ucsc.edu)
// Braingeneers
// hardware.c
// Description: Implementation of hardware.h functions
//-----------------------------------------------------------------------------

#include "hardware.h"


void Array::shiftin(int * sdi,  int *rclk, int* srclk, int * inPattern, bool * pattern){
		*sdi = sdi_;
		*rclk = rclk_;
		*srclk = srclk_;

		std::cout << "inPattern: " << *inPattern << std::endl;
		for(int i=0;i<ARRAY_SIZE;i++) pattern[i] = (*inPattern & (LED_MASK >> i)) > 0;

}


Array::Array(int sdi, int rclk, int srclk){
		    std::cout <<  "Initializing Array!!" << std::endl;
				this->sdi_ = sdi;
				this->rclk_ = rclk;
				this->srclk_ = srclk;
}
