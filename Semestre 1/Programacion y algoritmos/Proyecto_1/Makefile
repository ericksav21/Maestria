CC=gcc
CFLAGS=-I. -g

main: main.o memo.o imagen.o
	$(CC) -o main main.o memo.o imagen.o -I. -lm

clean:
	rm -f main main.o memo.o imagen.o