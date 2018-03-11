Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string. El nombre del archivo de texto donde se encuentra el punto inicial.
-Un string. El nombre del método a ejecutar: rosembrock_2, rosembrock_n, wood.
-Un entero. El número máximo de iteraciones.
-Un flotante. La tolerancia para la función gradiente.
-Un flotante. La tolerancia para la diferencia de x_i+1 y x_i.
-Un string. Tipo de cálculo de alfa: StepHess, StepAprox, StepFijo, Backtracking, Quadratic, Cubic.
-Un flotante. El tamaño de paso alfa fijo (Sólo si en el parámetro anterior se indicó: StepFijo).

Ejemplo de ejecución: ./main rosembrock_2.txt rosembrock_2 1000000 1e-5 1e-3 1e-7 Backtracking

*En esta misma carpeta se encuentran dos puntos iniciales para las funciones.
*Para la última función el archivo yk_r.txt contiene: y, x_0, x_i.
*Use 'make help' sin comillas para más información de la compilación.
