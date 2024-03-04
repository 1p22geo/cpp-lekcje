CC=g++
CFLAGS=-c -Wall
OBJECTS=main.o lib.o rownanie.o errors.o

all: prog

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o prog

main.o: main.cpp main.h lib.h
	$(CC) $(CFLAGS) main.cpp

lib.o: lib.cpp lib.h
	$(CC) $(CFLAGS) lib.cpp

rownanie.o: rownanie.cpp rownanie.h
	$(CC) $(CFLAGS) rownanie.cpp

errors.o: errors.cpp errors.h
	$(CC) $(CFLAGS) errors.cpp