# Linux build config

AS=nasm
AFLAGS=-f elf64

all: hello

hello: hello.o
	ld hello.o -o hello

hello.o: hello.asm
	$(AS) $(AFLAGS) hello.asm


clean: 
	rm *.o
	rm ./hello

run: all
	./hello
