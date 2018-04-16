Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe cinco argumentos:
	*Un entero, el tamaño del sudoku.
	*Un string, el nombre de la instancia.
	*Un string, el nombre del archivo de salida.
	*Un flotante, el tiempo límite de la ejecución en segundos.
	*Un flotante, el valor de DI.

Ejemplo de ejecución:
./main 9 instances/Easy1.txt Easy_res.txt 300.0 20.0

Notas:
*El programa ejecutará el algoritmo memético a la instancia seleccionada con los parámetros indicados y generará archivos de salida con el nombre especificado.
*Para los archivos de salida se generará uno con los resultados finales y otro con la información de la población capturada cada 5 segundos.
*Se recomienda ampliamente compilar el programa de manera optimizada con el comando 'make release' sin comillas, esto para que las ejecuciones sean mucho más rápidas.
*El programa además imprimirá en consola la información de las generaciones además del mejor fitness encontrado en cada generación y de haber resulto el sudoku se imprimirá la solución encontrada.
