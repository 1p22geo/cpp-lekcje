CC=g++
CFLAGS=-Wall -c

all: prog

prog: main.o exception.o trojkot.o
	$(CC) main.o exception.o trojkot.o -o prog

main.o: main.cpp main.h exception.h trojkot.h
	$(CC) $(CFLAGS) main.cpp

exception.o: exception.cpp exception.h
	$(CC) $(CFLAGS) exception.cpp

trojkot.o: trojkot.cpp trojkot.h
	$(CC) $(CFLAGS) trojkot.cpp