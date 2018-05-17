Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string: El nombre del archivo binario donde se encuentra la matriz de datos xi yi.
-Un entero: El número de iteraciones máximas para el algoritmo.
-Un flotante: La tolerancia que se aplicará a la norma del gradiente.
-Un flotante: El valor de v.
-Un flotante: El valor de h.

Ejemplo de ejecución: ./main datos10.bin 1000 1e-3 1.25 0.001

*El programa aplicará el método LM con los parámetros indicados y usará una aproximación por diferencias finitas para la matriz Jacobiana usando el valor h indicado en los parámetros e imprimirá como resultados los valores solicitados en la descripción de la tarea, así como el vector resultante.
*Se generará el archivo res.txt en donde se encuentran los datos para generar la gráfica, la cual contiene la nube de puntos xi, yi, el valor de yi generado por la función basada en el punto incial y el valor de yi generado por la función basada con el punto encontrado por el algoritmo.
*Se adjuntará la gráfica generada por el archivo res.txt pero de igual manera para generarla es necesario tener GNUPlot instalado y correr en consola el comando 'gnuplot inst.gpl' donde inst.gpl se adjunta en conjunto con los demás archivos.
*Se anexan el archivo datos10.bin proporcionado en la tarea.
