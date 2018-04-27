Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe ocho argumentos:
	*Un entero, el tamaño de la población.
	*Un entero, el límite inferior del dominio de la función.
	*Un entero, el límite superior del dominio de la función.
	*Un string, el nombre de la función. Las funciones vienen numeradas de acuerdo a la descripción de la tarea: f1, f2, f3, f4, f5, f6 y f7.
	*Un entero, el número de ejecuciones que se realizará con el algoritmo a la función indicada, para cada ejecución se usa una nueva semilla aleatoria.
	*Un entero, el tipo de cruze usado por el algoritmo. 1: Cruza de un punto, 2: Cruza de dos puntos.
	*Un string, el directorio donde se almacenarán los archivos de salida, ej: results/

Ejemplos de ejecución:
./main 100 -600 600 f1 1 1 results/
./main 100 -20 20 f3 2 10 results/

Notas:
*El programa ejecutará el algoritmo genético a la función indicada con los parámetros indicados y generará archivos de salida en el directorio especificado.
*Para los archivos de salida se generará uno con la información de las N ejecuciones pedida en la tarea para el ejercicio 1.
*Se recomienda ampliamente compilar el programa de manera optimizada con el comando 'make release' sin comillas, esto para que las ejecuciones sean mucho más rápidas.
*El programa además imprimirá en consola la información de las generaciones además del mejor fitness encontrado en conjunto con el vector real que generó dicho fitness.
*Los parámetros que están por defecto en el programa son los indicados en la tarea, tales como número máximo de evaluaciones de la función, tolerancia del error, etc.
