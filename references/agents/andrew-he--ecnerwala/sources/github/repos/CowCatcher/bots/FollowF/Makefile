CC=gcc
CFLAGS=-O2
CXXFLAGS=-O2

all: FollowF

mm-client.o: mm-client.c mm-client.h

FollowF.o: FollowF.c mm-client.h
FollowF: mm-client.o FollowF.o
	${CC} ${CFLAGS} -o $@ $^ -lm

clean:
	rm -f *.o

fresh: clean all

