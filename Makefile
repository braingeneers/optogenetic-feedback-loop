CFLAGS = -Wall -Isrc -lbcm2835 -g #-lwiringPi
CC = g++ -std=c++17
#CCN = gcc -std=c99
#CNFLAGS = -Wall -lbcm2835 #-lwiringPi


ARRAY_SRC=$(wildcard src/array/*.c /src/protocol.h)
MASTER_SRC=$(wildcard src/master/*.c /src/protocol.h /src/array/leddriver.h)

all: array master


array: $(ARRAY_SRC)
	$(CC) -o $@ $^ $(CFLAGS)


master: $(MASTER_SRC)
	$(CC) -o $@ $^ $(CFLAGS)



clean:
	@rm array master

