CC=g++
CFLAGS=-Wall -c

all: prog

prog: main.o exception.o
	$(CC) main.o -o prog

main.o: main.cpp main.h exception.h
	$(CC) $(CFLAGS) main.cpp

exception.o: exception.cpp exception.h
	$(CC) $(CFLAGS) exception.cpp