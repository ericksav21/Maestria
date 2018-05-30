Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un flotante: El valor de la tolerancia del algoritmo.
-Un flotante: El valor de v usado por LM.
-Un flotante: El valor de h para dif. finitas.
-Un entero: El número máximo de iteraciones.

Ejemplo de ejecución: ./main 1e-5 5 0.0001 10000

*El programa aplicará el método LM con el punto inicial dado como lo pide el examen, tras ejecutarse imprimirá los resultados de la última ejecución así como el valor del punto encontrado, los ángulos y la distancia.

Gracias por ser un gran docente!!!
