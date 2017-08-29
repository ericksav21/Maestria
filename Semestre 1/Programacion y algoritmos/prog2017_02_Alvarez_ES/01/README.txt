Para compilar:
gcc -std=c99 -c fpunteros.c main.c
gcc -std=c99 -o main fpunteros.o main.o

Para ejecutar:
./main

NOTAS:
Al iniciar el programa se indica un tipo de dato (char, int, float, double) y posteriormente se muestra un valor en hexadecimal y se pide que se ingrese un nuevo valor igualmente en hexadecimal, pero desplazado r posiciones, donde r = (-3, 3) y r != 0. Hay que destacar que el desplazamiento se hace de acuerdo al tipo de dato, siendo por ejemplo: int -> 4 posiciones.
Por lo cual para calcular el desplazamiento, se hace: des = val + (tam(tipo) * r), donde tam(.) denota el tamaño de tipo dado.
