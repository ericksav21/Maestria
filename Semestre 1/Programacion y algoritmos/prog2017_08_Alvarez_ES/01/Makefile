CC=g++
CFLAGS=-I. -g

main: main.o separador.o clasificador.o memo.o
	$(CC) -o main main.o separador.o clasificador.o memo.o -I.

clean:
	rm -f main *.o
