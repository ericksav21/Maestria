C=gcc
CFLAGS=-I. -g

main: main.o matriz_vector.o met_num.o memo.o reader.o
	$(CC) -o main main.o matriz_vector.o met_num.o memo.o reader.o -I. -lm

clean:
	rm -f main *.o