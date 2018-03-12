Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe cuatro argumentos:
	*Un entero, el tamaño del sudoku.
	*Un string, el nombre del archivo que contiene la instancia del sudoku.
	*un string, el tipo de inicialización (heuristic, random).
	*Un string, el nombre del archivo de salida (para los resultados).

Ejemplos de ejecución:
./main 9 Easy1.txt random Results_Easy1.txt
./main 16 i16x161.txt heuristic Results_i16x161.txt

El programa generará un archivo de texto con los resultados de la ejecución.

Notas:
*Se ejecutarán las dos búsquedas locales sin importar el tipo de inicialización.
*El programa imprimirá los sudokus encontrados con las dos búsquedas locales.
*Se incluyen las instancias con las que se trabajó así como algunos resultados de 100 ejecuciones con cada una.
