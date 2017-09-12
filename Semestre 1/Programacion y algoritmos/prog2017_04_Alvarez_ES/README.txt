Para compilar:
gcc -c memo.c
gcc -c frecuencias.c
gcc -c separador.c
gcc -c funciones.c
gcc -c main.c
gcc -o main main.o memo.o frecuencias.o separador.o funciones.o

Para ejecutar:
./main [nombre_libros_1] [cant_libros_1] [nombre_libros_2] [cant_libros_2] [semilla]

Nota: El valor de la semilla es opcional.
Nota: En el nombre de los libros se escribe la base, sin el número ni la extensión.

Ejemplo:
./main OZ1 5 OZ2 5 1987

Se producirán los archivos: clasified.txt (Clasificación de los bloques), frequencies.txt (Frecuencias relativas de los bloques), words.txt (Palabras únicas de los bloques).
Así como los N bloques que se separaron de los archivos de texto originales.
