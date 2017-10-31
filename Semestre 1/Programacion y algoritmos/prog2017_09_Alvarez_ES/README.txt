Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben tres argumentos obligatorios.

-Un entero. El número de nodos que tendrá el grafo aleatorio.
-Un caracter. El nodo origen al cual se creará la ruta más corta.
-Un caracter. El nodo destino al cual se creará la ruta más corta.

Los caracteres se denotan como letras que empiezan desde 'A' y terminan dependiendo el número de nodos del grado. Como ejemplo, si el grafo contiene 5 nodos, el rango de caracteres válido será [A, E].

Nota:
-Es necesario tener la librería de cairo instalada en el sistema.
-Al ejecutarse, el programa generará un grafo aleatorio con el número de nodos indicado, no necesariamente conexo en su totalidad. Se imprimirá en consola la composición del grafo en formato lista de adyacencia.
-Se ejecutará el algoritmo de Dijkstra para encontrar la ruta mínima y en caso de existir se imprimirá en consola el tamaño de la misma, así como los nodos que la componen.
-El programa generará cuatro imágenes, las dos primeras componen el grafo generado aleatoriamente y la ruta más corta, se mostrarán en colores distintos los nodos y aristas que componen dicha ruta. Las dos últimas imágenes contienen exactamente lo mismo que las primeras, exepto que éstas se encuentran en formato vectorial(PostScript).
-Para mayor información acerca del make, usar el comando 'make help' sin comillas.
