Para ejecutar el programa: 'python main.py [Parámetros]' sin comillas.

Nota: Antes de ejecutar el programa main.py adapta la variable 'path' a tu PC.
*Path: Indica dónde se encuentran los archivos para hacer las pruebas (Archivos de instancias).

Parámetros:
-Calcular entropías:
	Ejecutar: 'python main.py entropy' sin comillas.
	Calcula las entropías medias de las corridas encontradas en la instancia GECCO.
	
	Nota: Hay archivos que no tienen suficiente información para calcular su entropía, por 			lo cual su entropía siempre será cero.

	Si se quiere calcular la entropía de una corrida en particular ejecuta: 'python main.py entropy [No. de corrida]'
	Se generarán los archivos correspondientes a la entropía de cada método en relación al tiempo t (horas) y su gráfica.

-Calcular fitness:
	Ejecutar: 'python main.py fitness' sin comillas.
	Calcula la evolución de la calidad media de las corridas encontradas en la instancia GECCO.
	Se generarán los archivos correspondientes a los fitness de cada método en relación al tiempo t (horas) y su gráfica.

-Graficar entropías calculadas en archivos .entropyEvolution:
	Ejecutar: 'python main.py prec_entropy' sin comillas.

-Generar los test estadísticos:
	Ejecutar: 'python main.py statistical' sin comillas.
	Busca los archivos almacenados en la carpeta 'best_fitness' y aplica los test estadísticos.

	Nota: Los archivos deben estar en carpetas nombradas igual a las proporcionadas. Ej.: 'GECCO-contest', 'instance_10_10_400_0.05_7', etc.

	Se generan los archivos con los scores calculados. Con cada método indicando cuántas victorias, derrotas y empates tuvo. También se incluye el score.
