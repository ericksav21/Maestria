Para compilar:
gcc -c memo.c
gcc -c frecuencias.c
gcc -c separador.c
gcc -c funciones.c
gcc -c metricas_calidad.c
gcc -c main.c
gcc -o main main.o memo.o frecuencias.o separador.o funciones.o metricas_calidad.o

Para ejecutar:
./main [nombre_libros_1] [cant_libros_1] [nombre_libros_2] [cant_libros_2] [metrica_calidad] [semilla]

Nota: La métrica de calidad es opcional.
Nota: Las métricas de calidad disponibles son: accuracy, sensitivity, specificity, precision, negative, balanced accuracy, f1 score.
Nota: El valor de la semilla es opcional.
Nota: En el nombre de los libros se escribe la base, sin el número ni la extensión.

Ejemplos:
./main OZ1 5 OZ2 5
./main OZ1 5 OZ2 5 sensitivity 1987
./main OZ1 5 OZ2 5 f1\ score

Se producirán los archivos: clasified.txt (Clasificación de los bloques), frequencies.txt (Frecuencias relativas de los bloques), words.txt (Palabras únicas de los bloques).
Así como los N bloques que se separaron de los archivos de texto originales.
