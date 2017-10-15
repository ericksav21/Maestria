C=gcc
CFLAGS=-I. -g

main: main.o matriz_vector.o met_num.o memo.o
	$(CC) -o main main.o matriz_vector.o met_num.o memo.o -I. -lm

clean:
	rm -f main *.o