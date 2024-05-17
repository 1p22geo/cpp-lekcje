CC=gcc
CFLAGS=-c -Wall
LD=gcc
AR=ar
OBJECTS=libmysockets.client.o libmysockets.server.o

all: mysockets.so mysockets.a

mysockets.so: $(OBJECTS)
	$(LD) -shared $(OBJECTS) -o mysockets.so

mysockets.a: $(OBJECTS)
	$(AR) rcs mysockets.a $(OBJECTS)

libmysockets.client.o: client.c
	$(CC) $(CFLAGS) client.c -o libmysockets.client.o

libmysockets.server.o: server.c
	$(CC) $(CFLAGS) server.c -o libmysockets.server.o


clean:
	rm *.o *.so *.a

install: mysockets.so mysockets.h
	cp mysockets.a /usr/lib/libmysockets.a
	cp mysockets.so /usr/lib/libmysockets.so
	mkdir -p /usr/include/libmysockets
	cp mysockets.h /usr/include/libmysockets/libmysockets.h
