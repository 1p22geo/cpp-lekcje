AS=nasm
AFLAGS=-g -f elf64
LD=ld
LFLAGS=-static

all: main

main: main.o
	$(LD) $(LFLAGS) $^ -o $@

main.o: main.asm
	$(AS) $(AFLAGS) $< -o $@

clean:
	rm *.o main
