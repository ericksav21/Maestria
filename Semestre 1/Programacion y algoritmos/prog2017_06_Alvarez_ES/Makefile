CC=gcc
CFLAGS=-I. -g

main: main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o
	$(CC) -o main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o -I. -lm

clean:
	rm chunked_*.txt words.txt frequencies.txt clasified.txt main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o
