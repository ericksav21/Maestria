CC=gcc
CFLAGS=-I. -g

main: main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o
	$(CC) -o main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o -I.

clean:
	rm chunked_*.txt words.txt frequencies.txt clasified.txt main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o
