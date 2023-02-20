all:build

build:task1.c bmp_header.h
	gcc -g -Wall task1.c bmp_header.h -o bmp

clean:
	rm -rf bmp *.o
