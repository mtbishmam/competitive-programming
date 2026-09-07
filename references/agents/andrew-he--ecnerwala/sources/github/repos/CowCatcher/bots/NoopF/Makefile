CC=gcc
CFLAGS=-O2
CXXFLAGS=-O2

all: NoopF

mm-client.o: mm-client.c mm-client.h

NoopF.o: NoopF.c mm-client.h
NoopF: mm-client.o NoopF.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

