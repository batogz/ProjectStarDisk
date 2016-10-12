SHELL=/bin/bash

CC=gcc
CFLAGS=-Wall -std=c99

.PHONY: all clean

all: AB

AB: AB.c game.o hashset.o heuristic.o algo.o

algo.o: algo.c algo.h

game.o: game.c game.h

heuristic.o: heuristic.c heuristic.h

hashset.o: hashset.c hashset.h

clean:
	$(RM) *.o AB
