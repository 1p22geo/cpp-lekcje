CC=gcc
CFLAGS=-c -Wall

all: server client

server: server.o
	$(CC) server.o -o server

server.o: server.c server.h
	$(CC) $(CFLAGS) server.c


client: client.o
	$(CC) client.o -o client

client.o: client.c client.h
	$(CC) $(CFLAGS) client.c
