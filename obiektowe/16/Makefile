CC=g++
CFLAGS=-c -Wall
OBJECTS=main.o kolor/kolor.o


all: prog

prog: main.o kolor
	$(CC) $(OBJECTS) -o prog

main.o: main.cpp main.h kolor/kolor.h
	$(CC) $(CFLAGS) main.cpp

kolor:
	cd kolor
	make
	cd ..