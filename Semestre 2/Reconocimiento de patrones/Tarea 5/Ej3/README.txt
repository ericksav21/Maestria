Aquí se adjunta el código del ejercicio 5, en donde se separa las variantes de la optimización por archivo, es decir, en el archivo P1 encontraremos el algoritmo donde se optimizan los 3 parámetros de la función, y en el archivo P2 se encuentra la variante donde se estima sigma y mu y se optimiza sobre beta.

Para correr los programas simplemente ejecute todo el código de alguno de los dos archivos, y el algoritmo empezará a optimizar y finalmente hará la clasificación para todos los elementos del conjunto de prueba, tal como se menciona en el reporte.

NOTA: Como comentario importante, hay ocaciones en las que se producen errores a la hora de optimizar, y esto es gracias a que inicialmente se calculan los primeros valores de los tres parámetros de forma aleatoria con datos de una normal, esto produce valores de gradientes muy altos que tienden a infinito. Simplemente vuelve a correr el código una vez mas hasta ver que el algoritmo está minimizando los parámetros.
