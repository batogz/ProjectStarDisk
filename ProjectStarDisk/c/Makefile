SHELL=/bin/bash

CC=gcc
CFLAGS=-Wall -std=c99 -g

.PHONY: all clean

all: AB

AB: AB.c game.o hashset.o heuristic.o algo.o heap.o
	$(CC) $(CFLAGS) AB.c game.o hashset.o heuristic.o algo.o heap.o -lm -o AB

algo.o: algo.c algo.h

game.o: game.c game.h

heuristic.o: heuristic.c heuristic.h

hashset.o: hashset.c hashset.h

heap.o: heap.c heap.h -lm

clean:
	$(RM) *.o AB
