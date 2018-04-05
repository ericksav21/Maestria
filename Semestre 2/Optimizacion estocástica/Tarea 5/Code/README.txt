Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe ocho argumentos:
	*Un entero, el tamaño del sudoku.
	*Un string, el nombre del archivo que contiene la instancia del sudoku.
	*un string, el tipo de inicialización (heuristic, random).
	*Un string, el nombre del archivo de salida (para los resultados).
	*Un flotante, el valor de la temperatura máxima (inicial).
	*Un flotante, el valor de la temperatura mínima (final).
	*Un flotante, el tiempo de durará la ejecución.
	*Un flotante, el valor de rho entre 0 y 1 para el estado de equilibrio (porcentaje de vecinos a tratar).

Ejemplos de ejecución:
./main 9 Easy1.txt random Easy1_res.txt 9 0.05 300 0.8
./main 16 i16x161.txt heuristic i16x161_res.txt 10 0.01 1200 0.8

El programa generará dos archivos de texto con los resultados de la ejecución y el progreso del fitness y la temperatura capturado cada 2 minutos.

Notas:
*El programa imprimirá el sudoku encontrado.
*Se incluyen las instancias con las que se trabajó así como todos los resultados obtenidos con respecto a las mismas.
