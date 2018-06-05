Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe los siguientes argumentos:
	*Un string, el directorio donde se encuentran los archivos del algoritmo 1.
	*Un string, el directorio donde se encuentran los archivos del algoritmo 2.

Ejemplo de ejecución:
 ./main results/c1_10 results/c2_10

Notas:
*El programa ejecutará el algoritmo de bootstrap y el intervalo de confianza para cada uno de los conjuntos de datos de ambos algoritmos.
*Los archivos son comparados 1 a 1 y por lo cual deben llamarse f*.txt donde * es un número entre 1 y 7.
*EL programa asumirá que en el directorio existen 7 archivos por algoritmo a ser comparados.
*Se incluyen los archivos obtenidos al realizar las pruebas del ejercicio 2, mismas que fueron incluidas en el reporte.
*Al finalizar el programa generará el archivo "results.txt" el cual contiene los resultados de la prueba de hipótesis para cada algoritmo: si son iguales o cuál es mejor.
*Los resultados del intervalo de confianza se mostrarán en la consola.
