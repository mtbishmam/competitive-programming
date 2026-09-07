CC=g++
CFLAGS=-O2
CXXFLAGS=-O2

all: SalmonF

mm-client.o: mm-client.c mm-client.h

SalmonF.o: SalmonF.cpp mm-client.h
SalmonF: mm-client.o SalmonF.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

