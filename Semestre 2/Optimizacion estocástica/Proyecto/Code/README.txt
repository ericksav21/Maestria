Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe los siguientes argumentos:
	*Un string, el nombre del archivo de la instancia.
	*Un flotante, el valor K, la restricción de las capacidades.
	*Un flotante, el valor de capacidad en cada nodo del árbol.
	*Un entero, el tamaño de la población.
	*Un flotante, el valor de DI.
	*Un flotante, la probabilidad de cruza.
	*Un flotante, la probabilidad de mutación.
	*Un flotante, el tiempo límite para terminar el algoritmo (en segundos).
	*Un string, el directorio de salida dónde generar el archivo.

Ejemplo de ejecución:
./main instances/g1.txt 3 1 100 10.0 0.8 0.5 10.0 results/

Notas:
*El programa ejecutará el algoritmo genético a la instancia seleccionada con los parámetros indicados y generará archivos de salida con el nombre especificado.
*Se recomienda ampliamente compilar el programa de manera optimizada con el comando 'make release' sin comillas, esto para que las ejecuciones sean mucho más rápidas.
*El programa además imprimirá en consola la información de las generaciones además del mejor fitness encontrado en cada generación.
