Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Tambi�n se puede compilar con los siguientes comandos sin comillas:
'g++ -O2 -c main.cpp'
'g++ -O2 -c utils.cpp'
'g++ -O2 -o main main.o utils.o'

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe varios argumentos:
	*Si se quiere generar un archivo con un caso de prueba:
		-Ejecute ./main 1 [Case no] [N] [lo] [hi]
		-'Case no' es el n�mero de caso para el nombre del archivo. Ej.: Case no = 1 -> test_1.txt
		-'N' es el n�mero de puntos a generar
		-'lo' es el l�mite inferior de X y de Y de los puntos
		-'hi' es el l�mite superior de X y de Y de los puntos
		-Ejemplo: './main 1 1 1000 -50 50' esto generar� un caso de prueba con nombre test_1.txt que tenga 1000 puntos los cuales est�n entre (-50, 50) ambas coordenadas.

	*Si se quiere ejecutar los algoritmos de LCA:
		-Ejecute ./main 2 [Name]
		-'Name' es el nombre del archivo a procesar (se debe incluir la extensi�n)
		-Ejemplo: './main 2 test_1.txt'

El programa ejecutar� ambos algoritmos y comparar� los tiempos de ejecuci�n por separado, al final este reportar� dichos tiempos en segundos y
generar� dos archivos: 'out_naive.txt' y 'out_DaC.txt' en donde por cada punto se mostrar� su fuerza.

Notas:
-Se incluyen algunos archivos de prueba ya generados para realizar ejecuciones.