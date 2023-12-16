CC=g++
CFLAGS=-c -Wall

all: prog

prog: main.o klasa.o
	$(CC) main.o klasa.o -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
klasa.o: klasa.cpp klasa.h
	$(CC) $(CFLAGS) klasa.cpp

clean:
	del *.o
