CC = g++
CFLAGS = -Wall -g

main: main.o PostfixParser.o
	$(CC) $(CFLAGS) -o main main.o PostfixParser.o

main.o: main.cpp structs/QueueStacks.hpp structs/Queue.hpp Postfix/PostfixParser.hpp
	$(CC) $(CFLAGS) -c main.cpp

PostfixParser.o: Postfix/PostfixParser.cpp Postfix/PostfixParser.hpp
	$(CC) $(CFLAGS) -c Postfix/PostfixParser.cpp