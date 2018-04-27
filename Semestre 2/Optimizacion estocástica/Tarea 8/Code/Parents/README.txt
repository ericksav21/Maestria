Este ejercicio tiene 2 partes.

Parte en C++.
Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas.

*El programa calculará todos hijos con cruza de 1 y 2 puntos y los guardará en los archivos "offspring_1p.txt" y "offspring_2p.txt" los cuales sirven para generar las gráficas con el script hecho en python.
*La única parte que hay que modificar es cómo generar los padres que se cruzarán, esto ocurre en el archivo main.cpp. Los padres se generarán en su versión binaria. Actualmente se colocó como ejemplo una configuración donde los padres están en el eje 'Y'.

Parte en python.
Para ejecutar:
Desde consola escribir 'python graphic.py' sin comillas.
*El script tomará uno de los archivos generados por el programa en C++ y generará su respectiva gráfica con matplotlib con el nombre 'Grafica.png'.
*Cambiar el valor de la variable 'file' en la línea 19 para decirle al script qué archivo tomar.
