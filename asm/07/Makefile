AS=nasm
AFLAGS=-f elf64
LD=ld
LFLAGS=--dynamic-linker /lib64/ld-linux-x86-64.so.2
LIBRARIES=-lmysockets

all: client

client: client.o
	$(LD) $(LFLAGS) client.o -o client $(LIBRARIES)

client.o: client.asm
	$(AS) $(AFLAGS) client.asm

clean: 
	rm client *.o *.so *.a
