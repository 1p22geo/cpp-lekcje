CC=gcc
CFLAGS=-c -Wall
LD=gcc
LFLAGS=-shared
OBJECTS=client.o server.o

all: mysockets.so

mysockets.so: $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) -o mysockets.so

clean:
	rm mysockets.so
	rm *.o

install: mysockets.so mysockets.h
	cp mysockets.so /usr/lib/libmysockets.so
	mkdir -p /usr/include/libmysockets
	cp mysockets.h /usr/include/libmysockets/libmysockets.h
