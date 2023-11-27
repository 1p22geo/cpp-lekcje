CC=g++
CFLAGS=-c -Wall

all: prog

prog: main.o pojazd.o koparka.o taxi.o
	$(CC) main.o pojazd.o koparka.o taxi.o -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
koparka.o: koparka.cpp koparka.h
	$(CC) $(CFLAGS) koparka.cpp
taxi.o: taxi.cpp taxi.h
	$(CC) $(CFLAGS) taxi.cpp
pojazd.o: pojazd.cpp pojazd.h
	$(CC) $(CFLAGS) pojazd.cpp

clean:
	del *.o