Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se recibe un argumento obligatorio.

-Un string. EL nombre del archivo que contiene la información del triage.

Ejemplo de ejecución: ./main triage_sim.dat

Nota:
-El programa realizará el proceso de triage e imprimirá la información del mismo paciente por paciente, al final imprimirá la media y desviación estándar de los tiempos transcurridos en minutos.
-Para mayor información acerca del make, usar el comando 'make help' sin comillas.
