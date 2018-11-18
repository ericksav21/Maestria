Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

También se puede compilar con los siguientes comandos sin comillas:
'g++ -O2 -c main.cpp'
'g++ -O2 -c utils.cpp'
'g++ -O2 -o main main.o utils.o'

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe varios argumentos:
	*Si se quiere generar un archivo con un caso de prueba:
		-Ejecute ./main 1 [Case no] [N] [lo] [hi]
		-'Case no' es el número de caso para el nombre del archivo. Ej.: Case no = 1 -> test_1.txt
		-'N' es el número de puntos a generar
		-'lo' es el límite inferior de X y de Y de los puntos
		-'hi' es el límite superior de X y de Y de los puntos
		-Ejemplo: './main 1 1 1000 -50 50' esto generará un caso de prueba con nombre test_1.txt que tenga 1000 puntos los cuales están entre (-50, 50) ambas coordenadas.

	*Si se quiere ejecutar los algoritmos de LCA:
		-Ejecute ./main 2 [Name]
		-'Name' es el nombre del archivo a procesar (se debe incluir la extensión)
		-Ejemplo: './main 2 test_1.txt'

El programa ejecutará ambos algoritmos y comparará los tiempos de ejecución por separado, al final este reportará dichos tiempos en segundos y
generará dos archivos: 'out_naive.txt' y 'out_DaC.txt' en donde por cada punto se mostrará su fuerza.

Notas:
-Se incluyen algunos archivos de prueba ya generados para realizar ejecuciones.