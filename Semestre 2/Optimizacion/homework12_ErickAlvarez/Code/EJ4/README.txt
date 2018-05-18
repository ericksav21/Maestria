Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string: El nombre del archivo binario donde se encuentra el punto inicial.
-Un flotante: El valor del mu inicial.
-Un flotante: La tolerancia para el método de penalización cuadrática.
-Un flotante: La tolerancia inicial para el método de optimización (GCNL).
-Un flotante: El valor de dx para diferencias finitas.

Ejemplo de ejecución: ./main x1.txt 1.0 0.005 0.1 0.0001

*El programa aplicará el método PC con los parámetros indicados y usará una aproximación por diferencias finitas para calcular el gradiente de la función y posteriormente hará uso del algoritmo de gradiente conjugado no lineal para obtimizar el problema con restricciones.
*EL algoritmo imprimirá la información de cada iteración del gradiente conjugado no lineal y al finalizar la penalización cuadrática imprimirá los resultados obtenidos (punto final, número de iteraciones, valor de la función, valor de las restricciones).
*Se anexan los archivos con los dos puntos iniciales indicados en la tarea.
