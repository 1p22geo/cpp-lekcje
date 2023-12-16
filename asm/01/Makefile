# Windows build
CC=g++


all: prog

hello: hello.o
	$(CC) hello.o -o hello

hello.o: hello.asm
	.\nasm.exe hello.asm -f win64 -o hello.o


