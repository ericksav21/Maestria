Para compilar:
-Use el comando: 'make' sin comillas en consola, el cual generará los archivos objeto y el ejecutable llamado 'main'. Es necesario tener GSL instalado para compilar.

Para ejecutar:
-Use el comando: './main [n]' sin comillas.
-[n] Representa un entero, el tamaño que tomará la matriz A.

Ejemplo de ejecución: './main 8'

Para limpiar:
-Use el comando: 'make clean' sin comillas. EL cual borrará los archivos generados en compilación y el ejecutable.

-NOTAS:
El programa imprimirá lo solicitado en los 5 ejercicios y alguna información extra:
*La matriz A.
*La transpuesta de A (At).
*El producto A * At.
*Los eigenvalores del producto anterior.
*El valor de S1, Sn y K2(M).
*La inversa de la matriz A.
*K_inf.
*Los vectores solución x1 y x2.
*El error ||x1 - x2||.

En los archivos funciones.h y funciones.c se encuentra el código programado en el examen. Los otros archivos surgen de la compilación de las tareas.
