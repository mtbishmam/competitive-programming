CC=gcc
CFLAGS=-O2
CXXFLAGS=-O2

all: NoopC

mm-client.o: mm-client.c mm-client.h

NoopC.o: NoopC.c mm-client.h
NoopC: mm-client.o NoopC.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

