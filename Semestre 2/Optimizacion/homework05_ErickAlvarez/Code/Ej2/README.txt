Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string. El nombre del archivo base del entrenamiento (Ej.: train) El programa sabrá que el archivo corresponde con el X y el Y.
-Un string. El nombre del archivo base de prueba (Ej.: test) El programa sabrá que el archivo corresponde con el X y el Y.
-Un entero. El número máximo de iteraciones.
-Un flotante. La tolerancia para la función gradiente.
-Un flotante. La tolerancia para la diferencia de x_i+1 y x_i.
-Un flotante. La tolerancia para la diferencia en el valor de las funciones.
-Un entero. El primer número a clasificar.
-Un entero. El segundo número a clasificar.
-Un entero. El tamaño de la muestra de números.

Ejemplo de ejecución: ./main train test 10000 1e-2 1e-10 1e-10 1 3 1000

*En los archivos proporcionados hay un error con los de entrenamiento, hay una línea en blanco, si el programa se ejecuta con esos archivos dará error. Por lo cual se generó un nuevo archivo sin esa línea, se puede proporcionar si se necesita.
