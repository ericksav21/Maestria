Para compilar:
Ejecute el comando: "make help" para ver las opciones de compilación

Para ejecutar:
El archivo ejecutable se encuentra en la carpeta "bin". Ejecute el comando:
./main [nombre_libros_1] [cant_libros_1] [nombre_libros_2] [cant_libros_2] [Número de palabras] [Nfeat] [Npop] [Número de iteraciones] [metrica_calidad] [semilla]

Nota: La métrica de calidad es opcional.
Nota: Las métricas de calidad disponibles son: accuracy, sensitivity, specificity, precision, negative, balanced accuracy, f1 score.
Nota: El valor de la semilla es opcional.
Nota: En el nombre de los libros se escribe la base, sin el número ni la extensión.

Ejemplos:
./main OZ1 5 OZ2 5 550 20 30 100 sensitivity 78965
