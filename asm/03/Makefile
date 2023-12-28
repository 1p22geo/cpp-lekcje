CC=gcc
CFLAGS=-Wall -c

all: hello

hello: main.o stuff.o
	$(CC) main.o stuff.o -o hello

main.o: main.c stuff.h
	$(CC) $(CFLAGS) main.c -o main.o

stuff.o: stuff.asm stuff.h
	nasm -f elf64 stuff.asm

clean:
	rm *.o
	rm hello
