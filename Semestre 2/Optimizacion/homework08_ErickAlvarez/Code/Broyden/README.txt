Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un entero. El número de punto inicial a ejecutar [1, 4]. Los puntos iniciales vienen numerados a como se describió en la tarea. Ej: 1 - (0, 0, 0)^T, 2 - (1.1, 1.1, -1.1)^T, etc.
-Un entero. El número límite de iteraciones.

Ejemplo de ejecución: ./main 1 1000

*El programa aplicará el método de Broyden para el punto inicial indicado. En cada iteración se imprimirán los valores: k, x_k, ||F(x_k)|| y k(J(x_k)). Al final terminar el algoritmo se imprimirá la razón de término: Número de iteraciones alcanzadas, tolerancia alcanzada, errores, etc.
*La tolerancia con la que el algoritmo se detendrá es sqrt{Eps_m} donde 'Eps_m' es el épsilon de la máquina.
*El algoritmo usa la expresión analítica para calcular la matriz Jacobiana sólamente en la primer iteración.
*Para más información sobre la compilación ejecuta: 'make help' sin comillas.
