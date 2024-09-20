CC=g++
CFLAGS=-c -Wall
OBJECTS=main.o kolor/kolor.o


all: prog

prog: main.o libkolor
	$(CC) $(OBJECTS) -o prog

main.o: main.cpp main.h kolor/kolor.h
	$(CC) $(CFLAGS) main.cpp

libkolor:
	bash -c "cd kolor;make;cd .."
