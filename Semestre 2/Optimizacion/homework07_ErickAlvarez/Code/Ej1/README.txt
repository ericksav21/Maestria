Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string. El nombre del archivo de texto donde se encuentra el punto inicial.
-Un string. El nombre del método a ejecutar: rosembrock_2, rosembrock_n, wood.
-Un flotante. El valor de lambda.
-Un flotante. La tolerancia para la función gradiente.
-Un flotante. La tolerancia para la diferencia de x_i+1 y x_i.
-Un flotante. La tolerancia para la diferencia de las funciones.

Ejemplo de ejecución: ./main yk.txt 100.0 1e-6 1e-10 1e-12

*En esta misma carpeta se encuentra el archivo necesario para ejecutar el programa: yk.txt.
*El programa generará un punto inicial con valores que estén entre 0 y 3. Ejecutará el gradiente conjutado usando los valores de 'y' que se encuentran el archivo
inicial y el lambda indicado. Por cada iteración que haga se imprimirá información de las normas, y finalmente se imprimirá el punto crítico encontrado.

*Como tolerancias se pueden usar las siguientes:
-TolG: 1e-6
-TolX: 1e-10
-TolF: 1e-12
