CFLAGS = -Wall -Isrc -lbcm2835 -lpthread #-lwiringPi
CC = g++ -std=c++17
#CCN = gcc -std=c99
#CNFLAGS = -Wall -lbcm2835 #-lwiringPi

ARRAY_SRC=$(wildcard src/array/*.c /src/protocol.h)
MASTER_SRC=$(wildcard src/master/*.c /src/protocol.h /src/array/leddriver.h)
ORGANOID_SRC=$(wildcard src/organoid/*.c /src/protocol.h)
ORGANOIDMAST_SRC=$(wildcard src/organoidmaster/*.c /src/protocol.h)


all: master organoid organoidmast #array


array: $(ARRAY_SRC)
	$(CC) -o $@ $^ $(CFLAGS)


master: $(MASTER_SRC)
	$(CC) -o $@ $^ $(CFLAGS)

organoid: $(ORGANOID_SRC)
	$(CC) -o $@ $^ $(CFLAGS)

organoidmast: $(ORGANOIDMAST_SRC)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm master organoid organoidmast #array
