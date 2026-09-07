CC=g++
CFLAGS=-O2
CXXFLAGS=-O2

all: SalmonC

mm-client.o: mm-client.c mm-client.h

SalmonC.o: SalmonC.cpp mm-client.h
SalmonC: mm-client.o SalmonC.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

