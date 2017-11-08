Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben dos argumentos obligatorios.

-Un entero. El número de vectores de prueba que se usarán del conjunto de entrenamiento.
-Un entero. El número de capas ocultas que se usarán.

Ejemplo de ejecución: ./main 4 3

Nota:
-Es necesario tener la librería de cairo instalada en el sistema.
-El programa generará una red neuronal con el número de capas ocultas indicado y ellas con un número de neuronas aleatorio entre 2 y 6. Imprimirá los resultados del algoritmo de FordWard Propagation por cada vector de prueba y al final imprimirá la estructura de la red.
-El programa generará dos imágenes, las cuales son la arquitectura de la red en formato PNG y PS (Vectorial).
-Para mayor información acerca del make, usar el comando 'make help' sin comillas.
