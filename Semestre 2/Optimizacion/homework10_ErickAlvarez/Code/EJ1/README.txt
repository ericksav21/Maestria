Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string: El nombre del archivo donde se encuentra el punto inicial y la dimensión de la función.
-Un entero: El número de iteraciones máximas para el algoritmo.
-Un flotante: La tolerancia que se aplicará a la norma del gradiente.
-Un flotante: El valor de v.

Ejemplo de ejecución: ./main rosenbrock_2.txt 1000 1e-3 1.25

*El programa aplicará el método LM con los parámetros indicados e imprimirá como resultados los valores solicitados en la descripción de la tarea, esto lo hará en la primera y última iteración.
*Se anexan los archivos que contienen los puntos iniciales pedidos en la descripción de la tarea, tanto para la dimensión 2 como la 50.
*La implementación del método BFGS fue hecha como se indica en la clase 18.
*Para ver más opciones de compilación use 'make help' sin comillas.
