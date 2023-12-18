CC=g++
CFLAGS=-c -Wall
OBJECTS=main.o vector.o

all: prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o prog

main.o: main.cpp vector.h
	$(CC) $(CFLAGS) main.cpp
vector.o: vector.cpp vector.h
	$(CC) $(CFLAGS) vector.cpp

clean:
	del *.o prog.exe