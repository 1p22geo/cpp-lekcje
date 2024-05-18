INCLUDES=-I/usr/include/libmysockets/
LIBRARIES=-lmysockets
CC=gcc
CFLAGS=-c -Wall $(INCLUDES)
LD=gcc

all: server client

static: server.static client.static

server: server.o
	$(LD) server.o -o server $(LIBRARIES)

client: client.o
	$(LD) client.o -o client $(LIBRARIES)

server.static: server.o
	$(LD) -static server.o -o server.static $(LIBRARIES)

client.static: client.o
	$(LD) -static client.o -o client.static $(LIBRARIES)


clean:
	rm *.o *.a *.so server client server.static client.static


server.o: server.c
	$(CC) $(CFLAGS)  server.c

client.o: client.c
	$(CC) $(CFLAGS) client.c
