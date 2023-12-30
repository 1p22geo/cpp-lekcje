CC=gcc
CFLAGS=-c -Wall
LD=gcc
LFLAGS=-no-pie
AS=nasm
AFLAGS=-Wall -f elf64


all: prog

prog: main.o list.o
	$(LD) $(LFLAGS) main.o list.o -o prog

main.o: main.c list.h
	$(CC) $(CFLAGS) main.c -o main.o

list.o: list.asm
	$(AS) $(AFLAGS) list.asm


clean:
	rm *.o
	rm prog
