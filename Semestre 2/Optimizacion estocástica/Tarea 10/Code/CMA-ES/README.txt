Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe los siguientes argumentos:
	*Un entero, la dimensión del problema.
	*Un flotante, el límite inferior del dominio de la función.
	*Un flotante, el límite superior del dominio de la función.
	*Un string, el nombre de la función. Las funciones vienen numeradas de acuerdo a la descripción de la tarea: f1, f2, f3, f4, f5, f6 y f7.
	*Un entero, el número máximo de iteraciones.
	*Un entero, el número máximo de ejecuciones que hará el algoritmo.
	*Un flotante, el valor de sigma inicial para la matriz de covarianza.
	*Un string, el directorio donde se almacenarán los archivos de salida, ej: results/

Ejemplo de ejecución:
./main 10 -600 600 f1 10000 1 0.3 results/

Notas:
*El programa ejecutará el algoritmo CMA-ES a la función indicada con los parámetros indicados y generará archivos de salida en el directorio especificado.
*Para los archivos de salida se generará uno con la información de las N ejecuciones pedidas en la tarea para el ejercicio 1 y otro con los mejores valores de aptitud encontrados.
*Se recomienda ampliamente no dar un valor alto de iteraciones máximas porque puede que el algoritmo empiece a dar Nan's.
