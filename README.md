# optogenetic-feedback-loop
Optogenetic feedback loop for shaping the behavior of cortical organoids

## Contents
### Array
  Drives Raspberry Pi Zero GPIO connected to Serial to Parallel Converter Chips
  - Serial Shift Register Chip: 8 bit, 7HC595 from NXP Semiconductors
    - datasheet: 
      - https://cdn-shop.adafruit.com/datasheets/sn74hc595.pdf
      - https://datasheet.octopart.com/74HC595N-Philips-datasheet-7085704.pdf
  - High-performance GPIO Library bcm2835: https://www.airspayce.com/mikem/bcm2835/
  - Raspberry pi pinout reference: https://pinout.xyz/pinout/wiringpi
  
### Organoid Simulation


### Supervisor Algorithm
- Hebbian Learning feedback loop

### Communication Protocol
  - UNIX network sockets
  - Master send boolean values as a list inside Message
  - Array recieves message and toggles LEDs

### Graphics Library 

