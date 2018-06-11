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
	*Un flotante, la probabilidad de mutación.
	*Un string, el directorio de salida dónde generar el archivo.

Ejemplo de ejecución:
./main ../instances/g1.txt 3 1 100 0.05 results/

Notas:
*El programa ejecutará el algoritmo genético usado para hacer el análisis de la diversidad a la población. Esta es la implementación más básica usando tanto la heurística constructiva como los operadores de cruza y mutación.
*El programa hará 20000 generaciones y cada 4 registrará en un archivo a la población y al mejor valor de aptitud.
*Se recomienda ampliamente compilar el programa de manera optimizada con el comando 'make release' sin comillas, esto para que las ejecuciones sean mucho más rápidas.

*De igual manera se adjunta el archivo 'analizer.py' que procesa los resultados del genético y genera las gráficas de evolución de diversidad y fitness.
	-Para ejecutarlo es necesario tener instalado numpy y matplotlib.
	-Es necesario cambiar el directorio de donde obtiene los archivos, eso se hace en la línea 10.
	-Ejecutar el script y este procesará todos los archivos en un directorio para generar las gráficas.
