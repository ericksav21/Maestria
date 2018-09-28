Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe varios argumentos:
	*Si se quiere generar un archivo con un caso de prueba:
		-Ejecute ./main 1 [N] [M] [Name]
		-'N' es el n�mero de nodos que tengr� el �rbol
		-'M' es el n�mero de queries que tendr� el caso de prueba
		-'Name' es el nombre que tendr� el archivo de salida (se debe incluir la extensi�n)
		-Ejemplo: './main 1 1000 100 in.txt' esto generar� un caso de prueba con un �rbol de 1000 nodos y 100 queries

	*Si se quiere ejecutar los algoritmos de LCA:
		-Ejecute ./main 2 [Name]
		-'Name' es el nombre del archivo a procesar (se debe incluir la extensi�n)
		-Ejemplo: './main 2 in.txt'

El programa ejecutar� ambos algoritmos y comparar� los tiempos de ejecuci�n por separado, al final este reportar� dichos tiempos en segundos y
generar� dos archivos: 'out_lca_naive.txt' y 'out_lca_optimized.txt' en donde por cada query se reportar� el nodo que funge como LCA de u y de v.

Notas:
-Los nodos de los �rboles que se generan y que procesan los algoritmos est�n indexados a cero.