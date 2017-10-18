CC=gcc
CFLAGS=-c
LFLAGS=-o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS) imagen.h
	$(CC) $(LFLAGS) $@ $(OBJS) -lm

*.o: $(CPPS)
	$(CC) $(CFLAGS) $<

opt:
	$(MAKE) CFLAGS="-O2 -c" LFLAGS="-O2 -o"

deb:
	$(MAKE) CFLAGS="-g -c" LFLAGS="-g -o"

clean:
	rm -f $(EXEC) $(OBJS) out*.pgm angulos.txt longitudes.txt

help:
	@echo 'Opciones de compilación:'
	@echo 'Comando: make - Compila normalmente, genera un ejecutable llamado main.'
	@echo 'Comando: make opt - Compila de manera optimizada.'
	@echo 'Comando: make deb - Compila en modo debug.'
	@echo 'Comando: make clean - Limpia todos los archivos generados por la compilación y la ejecución del programa.'