CFLAGS = -Wall -Isrc -lbcm2835 -g
CC = g++ -std=c++17
CCN = gcc 
CNFLAGS = -Wall -lwiringPi

BLINK_SRC = ledarray/src/blink.c #src/crack.h src/main.cc src/server.cc src/server.h
#TEST_SRC = src/crack.h src/test.cc src/server.cc src/server.h
74HC595_LED_SRC = 74HC595_LED.c

all: blink 74HC595_LED

blink: $(BLINK_SRC)
	$(CC) -o $@ $^ $(CFLAGS)
	
#test:  $(TEST_SRC) crack.o
#	$(CC) -o $@ $^ $(CFLAGS)

74HC595_LED:  $(74HC595_LED_SRC)
	$(CCN) -o $@ $^ $(CNFLAGS) 

clean:
	@rm blink 74HC595_LED

