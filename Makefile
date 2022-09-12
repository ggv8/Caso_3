CC = g++
CFLAGS = -Wall -g

all: main

main: main.o
	$(CC) $(CFLAGS) -o main.o

main.o: main.cpp QueueStacks.hpp structs/Queue.hpp
	$(CC) $(CFLAGS) -c main.cpp