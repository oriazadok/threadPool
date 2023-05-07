CC = gcc
CFLAGS = -g -Wall


all: coder

coder: coder.o queue.o
	$(CC) $(CFLAGS) -o coder coder.o queue.o -L. ./libCodec.so -pthread

q: q_test.o queue.o
	$(CC) $(CFLAGS) -o q q_test.o queue.o

q_test.o: q_test.c queue.h
	$(CC) $(CFLAGS) -c q_test.c

coder.o: coder.c queue.h codec.h
	$(CC) $(CFLAGS) -c coder.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c


.PHONY: all clean

clean:
	-rm coder *.o 2>/dev/null
