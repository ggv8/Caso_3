CC = g++
CFLAGS = -Wall -g

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp PostfixParser QueueStacks Queue Airport
	$(CC) $(CFLAGS) -c main.cpp

PostfixParser: Postfix/PostfixParser.hpp

QueueStacks: structs/QueueStacks.hpp Stack

Queue: structs/Queue.hpp List

Stack: structs/Stack.hpp List

List: structs/List.hpp structs/Node.hpp

Airport: Airport/Airport.hpp Airport/Flight.hpp PriorityQueue

PriorityQueue: structs/PriorityQueue.hpp structs/PriorityNode.hpp