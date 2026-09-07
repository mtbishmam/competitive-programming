CC=gcc
CFLAGS=-O2
CXXFLAGS=-O2

all: AvoidC

mm-client.o: mm-client.c mm-client.h

AvoidC.o: AvoidC.c mm-client.h
AvoidC: mm-client.o AvoidC.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

