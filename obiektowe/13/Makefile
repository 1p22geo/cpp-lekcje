CC=g++
CFLAGS=-Wall -c

all: prog

prog: main.o czas.o
	$(CC) main.o czas.o -o prog

main.o: main.cpp czas.h
	$(CC) $(CFLAGS) main.cpp

czas.o: czas.cpp czas.h
	$(CC) $(CFLAGS) czas.cpp

clean: 
	del *.o *.exe