Para compilar:
-Use el comando: 'make' sin comillas en consola, el cual generará los archivos objeto en la carpeta 'obj' y el ejecutable llamado 'main'.

Para ejecutar:
-Use el comando: './main' sin comillas.

Para limpiar:
-Use el comando: 'make clean' sin comillas. EL cual borrará los archivos generados en compilación y el ejecutable.

NOTAS:
-Para más opciones de compilación use 'make help' sin comillas.
-El programa imprimirá lo solicitado en los 4 ejercicios:
*El valor de H.
*La búsqueda de la raíz de la función.
*Los puntos de la discretización.

-Al ejecutar el programa se generan dos conjuntos de puntos, uno es por la discretización y se guarda en el archivo 'puntos.txt' y el otro es el del Spline generado en el archivo 'spline.txt'.
-Estos archivos se generan en la raíz del documento.
-Se proporcionó un archivo de instrucciones para generar la gráfica con GNUPlot, el archivo se llama 'inst.gpl' y para realizar la gráfica sólo hay que ejecutar el comando 'gnuplot inst.gpl' sin comillas.

En los archivos funciones.h y funciones.c se encuentra el código programado en el examen. Los otros archivos surgen de la compilación de las tareas.
