Para compilar:
Use el comando 'make' sin comillas.
Use el comando 'make help' sin comillas para ver todas las opciones.

Para ejecutar:
Una vez compilado use el comando './main' sin comillas
-El programa recibe dos argumentos:
	*Un string, el nombre del archivo de tareas a ejecutar.
	*Un string, el nombre del archivo de los procesos del cluster que utilizará.

Ejemplo de ejecución:
./main tasks.txt machinefile.txt

El programa generará archivos de log correspondientes a los sucesos transcurridos con los nodos hijos.

Notas:
Se incluyen el programa de números aleatorios que se usó como prueba en el cluser así como el generador del archivo tasks para 1000 tareas. Dichos programan se encuentran en las carpetas 'test' y 'generator'.
Se incluyen el archivo tasks.txt y machinefile.txt utilizados en la prueba con el cluster.
