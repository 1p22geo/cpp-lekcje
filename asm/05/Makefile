INCLUDES=-I/usr/include/libmysockets/
LIBRARIES=-lmysockets
CC=gcc
CFLAGS=-c -Wall $(INCLUDES)
LD=gcc
LFLAGS=$(LIBRARIES)

all: server client


server: server.o
	$(LD) $(LFLAGS) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS)  server.c

client: client.o
	$(LD) $(LFLAGS) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c
