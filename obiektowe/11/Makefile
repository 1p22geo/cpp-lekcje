CC=g++
CFLAGS=-c -Wall

all: prog

prog: main.o prostokat.o trojkat.o figura.o
	$(CC) main.o prostokat.o trojkat.o figura.o -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
prostokat.o: prostokat.cpp prostokat.h figura.h
	$(CC) $(CFLAGS) prostokat.cpp
trojkat.o: trojkat.cpp trojkat.h figura.h
	$(CC) $(CFLAGS) trojkat.cpp
figura.o: figura.cpp figura.h 
	$(CC) $(CFLAGS) figura.cpp

clean:
	del *.o
	del *.exe