Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe varios argumentos:
	*Si se quiere generar un archivo con un caso de prueba:
		-Ejecute ./main 1 [N] [M] [Name]
		-'N' es el número de nodos que tengrá el árbol
		-'M' es el número de queries que tendrá el caso de prueba
		-'Name' es el nombre que tendrá el archivo de salida (se debe incluir la extensión)
		-Ejemplo: './main 1 1000 100 in.txt' esto generará un caso de prueba con un árbol de 1000 nodos y 100 queries

	*Si se quiere ejecutar los algoritmos de LCA:
		-Ejecute ./main 2 [Name]
		-'Name' es el nombre del archivo a procesar (se debe incluir la extensión)
		-Ejemplo: './main 2 in.txt'

El programa ejecutará ambos algoritmos y comparará los tiempos de ejecución por separado, al final este reportará dichos tiempos en segundos y
generará dos archivos: 'out_lca_naive.txt' y 'out_lca_optimized.txt' en donde por cada query se reportará el nodo que funge como LCA de u y de v.

Notas:
-Los nodos de los árboles que se generan y que procesan los algoritmos están indexados a cero.