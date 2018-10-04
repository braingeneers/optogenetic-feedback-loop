CFLAGS = -Wall -Isrc -lbcm2835 -g
CC = g++ -std=c++17

BLINK_SRC = ledarray/src/blink.c #src/crack.h src/main.cc src/server.cc src/server.h
#TEST_SRC = src/crack.h src/test.cc src/server.cc src/server.h

all: blink

blink: $(BLINK_SRC)
	$(CC) -o $@ $^ $(CFLAGS)
	
#test:  $(TEST_SRC) crack.o
#	$(CC) -o $@ $^ $(CFLAGS)


clean:
	@rm blink

