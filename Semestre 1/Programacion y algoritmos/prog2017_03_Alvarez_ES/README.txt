Para compilar:
gcc -c memo.c
gcc -c fpalabras.c
gcc -c main.c
gcc -o main main.o memo.o fpalabras.o

Para ejecutar:
./main < data.in

Notas: La salida del programa se produce en el archivo "histogram.txt"
