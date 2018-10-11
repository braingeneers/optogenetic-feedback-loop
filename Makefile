CFLAGS = -Wall -Isrc -lbcm2835 -g #-lwiringPi
CC = g++ -std=c++17
#CCN = gcc -std=c99 
#CNFLAGS = -Wall -lbcm2835 #-lwiringPi

#BLINK_SRC = ledarray/src/blink.c #src/crack.h src/main.cc src/server.cc src/server.h
#TEST_SRC = src/crack.h src/test.cc src/server.cc src/server.h
#74HC595_LED_SRC = 74HC595_LED.c
#UI_74_SRC = ui74.c
#SR_SRC = sr.c
#OPTI_UI_74_SRC = optimized_ui74.c

#MAIN_SRC = src/main.c led_driver src/ledarray/driver.h
#DRIVER_SRC = src/ledarray/driver.c src/ledarray/driver.h

SRC=$(wildcard src/*.c)

all: uiblink

uiblink: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)



#main: $(MAIN_SRC)
#	$(CC) -o $@ $^ $(CFLAGS)

#led_driver: $(DRIVER_SRC)
#	$(CC) -o $@ $^ $(CFLAGS)


#blink 74HC595_LED sr ui74HC595 opti_ui74HC595

#blink:	$(BLINK_SRC)
#	$(CC) -o $@ $^ $(CFLAGS)

#test:  $(TEST_SRC) crack.o
#	$(CC) -o $@ $^ $(CFLAGS)

#74HC595_LED:  $(74HC595_LED_SRC)
#	$(CCN) -o $@ $^ $(CNFLAGS) 

#sr: $(SR_SRC)
#	$(CCN) -o $@ $^ $(CNFLAGS) 

#ui74HC595:  $(UI_74_SRC)
#	$(CC) -o $@ $^ $(CFLAGS) 


#opti_ui74HC595:  $(OPTI_UI_74_SRC)
#	$(CC) -o $@ $^ $(CFLAGS)



clean:
	@rm uiblink #blink 74HC595_LED sr ui74HC595 opti_ui74HC595

