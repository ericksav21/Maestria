CC=gcc
CFLAGS=-I. -g

main: main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o
	$(CC) -o main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o -I. -lm

help:
	@echo 'Clasificador de textos, elaborado por Erick Salvador Alvarez Valencia.'
	@echo 'Opciones de compilación:'
	@echo 'Comando: make - Compila normalmente, genera un ejecutable llamado main.'
	@echo 'Comando: make opt - Compila de manera optimizada.'
	@echo 'Comando: make deb - Compila en modo debug.'
	@echo 'Comando: make latex - Compila el reporte escrito en latex y genera un archivo PDF en la carpeta docs.'
	@echo 'Comando: make clean - Limpia todos los archivos generados por la compilación, excepto los ejecutables y el documento en PDF.'
	@echo 'Comando: make cleanall - Limpia todos los archivos, incluyendo los ejecutables y los documentos.'

clean:
	rm chunked_*.txt words.txt frequencies.txt clasified.txt main main.o funciones.o frecuencias.o separador.o memo.o metricas_calidad.o generador.o
