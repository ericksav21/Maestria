Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string. El nombre del archivo de texto donde se encuentra el punto inicial.
-Un string. El nombre de la función a ejecutar: Rosenbrock, Wood, Convex1, Convex2.
-Un string. El tipo de beta a usar en el método de GC: Fletcher, Polak, Hestnes, FR_PR.
-Un entero. El número máximo de iteraciones.
-Un flotante. La tolerancia para la función gradiente.
-Un flotante. La tolerancia para la diferencia de x_i+1 y x_i.
-Un flotante. La tolerancia para la diferencia de las funciones.

Ejemplo de ejecución: ./main rosenbrock_100.txt Rosenbrock Polak 1000000 1e-6 1e-10 1e-12

*Use 'make help' sin comillas para más información de la compilación.
*En esta misma carpeta se encuentran los puntos iniciales mencionados en la descripción de la tarea para cada una de las funciones.
*El programa ejecutará el método de gradiente conjugado no lineal con la función y punto inicial indicados, imprimirá la información de cada una
de las iteraciones, al finalizar imprimirá el punto encontrado y el valor de la función en dicho punto.
*De la misma forma el programa generará un archivo llamado 'results.txt' mediante el cual se generaron las gráficas del reporte.

NOTA: El algoritmo de GC no lineal usa el método de backtracking para hacer la búsqueda del tamaño de paso con las condiciones fuertes de Wolfe.
Generalmente esto funciona muy bien para las funciones con la mayoría de puntos iniciales dados y la mayoría de las Betas exepto para la función
convexa 2 con las Betas de Polak, Hestnes y FR-PR, en esos casos el método irá descendiendo muy lento. Una configuración donde se optimiza de manera
muy rápida con estas Betas es usando sólamente las condiciones de Armijo y un alpha inicial de: 1.0.
Esta configuración se puede hacer de manera muy sencilla de la siguiente manera:

	-En la línea 64 del archivo met_num.c cambia el valor de la variable 'use_strong_wolfe' por 0.
	-En la línea 189 del archivo met_num.c cambia el valor de la variable 'alpha_init' por 1.0.

*Como tolerancias se pueden usar las siguientes:
-TolG: 1e-6
-TolX: 1e-10
-TolF: 1e-12
