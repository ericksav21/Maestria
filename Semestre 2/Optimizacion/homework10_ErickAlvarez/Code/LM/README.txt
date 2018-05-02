Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string: El nombre del archivo donde se encuentra el punto inicial.
-Un entero: El número de iteraciones máximas para el algoritmo.
-Un flotante: La tolerancia que se aplicará a la norma del gradiente.
-Un entero: El tipo de Hessiana. 1: Hessiana analítica. 2: Hessiana aproximada

Ejemplo de ejecución: ./main rosenbrock_2.txt 1000 1e-3 1

*El programa aplicará el método BFGS con los parámetros indicados e imprimirá como resultados los valores solicitados en la descripción de la tarea, esto lo hará por cada iteración hasta llegar al punto final.
*Se anexan los archivos que contienen los puntos iniciales pedidos en la descripción de la tarea, tanto para la dimensión 2 como la 100.
*El valor de "h" se puede modificar en el archivo main.c en la línea 29.
*La implementación del método BFGS fue hecha como se indica en la clase 18.
