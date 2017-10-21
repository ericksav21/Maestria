CC=gcc
CFLAGS=-I. -g

main: main.o matriz_vector.o met_num.o memo.o funciones.o
	$(CC) -o main main.o matriz_vector.o met_num.o memo.o funciones.o -I. -lgsl -lgslcblas -lm

clean:
	rm -f *.o main