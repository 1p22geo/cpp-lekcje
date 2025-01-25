CC=gcc
CFLAGS=-c -Wall -nostdlib -fno-stack-protector
LD=gcc
LDFLAGS=-nostdlib -static
AS=nasm
AFLAGS=-f elf64

all: main


main: main.o libcalls.o server.o
	$(LD) $(LDFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) $< -o $@

libcalls.o: libcalls.asm
	$(AS) $(AFLAGS) $<

server.o: server.asm
	$(AS) $(AFLAGS) $<


clean:
	rm *.o main
