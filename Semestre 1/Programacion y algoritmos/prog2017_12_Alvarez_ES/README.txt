Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos obligatorios:

-Un string. EL nombre del archivo CSV que contiene el conjunto de datos.
-Un entero. El número de columna que contiene el conjunto de componentes X de los datos.
-Un entero. El número de columna que contiene el conjunto de componentes Y de los datos.
-Un entero. EL número de clusters a trabajar (Máximo 10).
-Un número decimal. La distancia de convergencia límite.
--Un entero. EL número máximo de iteraciones a ejecutar.

Ejemplo de ejecución: ./main Sacramentorealestatetransactions.csv 7 10 4 10 100

*Ahí le estamos diciendo al programa que tome las columnas 7 y 10 del archivo CSV, que genere sólo 4 clusters, que la distancia mínima de convergencia son 10 unidades y que el máximo número de iteraciones sea 100.

Notas:
-Para la generación de gráficos es necesario tener GNUPlot instalado en el sistema.
-El programa usa pipes para la generación de la gráfica, de la misma forma se utiliza el archivo inst.gpl
-Los archivos CSV deben cumplir que la primer fila de datos debe ser un header (tener texto) ya que esta se desprecia en la lectura.
-Las columnas de donde se obtienen los datos deben contener sólo información numérica ya sea enteros o punto flotante.
-Se adjuntan 3 conjuntos de datos a utilizar y para los cuales se mencionan el número de columnas que se utilizaron:
	-Sacramentorealestatetransactions.csv (Columnas 7 y 10).
	-MER_T06_02.csv (Columnas 2 y 3).
	-SalesJan2009.csv (Columnas 11 y 12).
-El programa al ejecutarse generará una gráfica de los puntos ya clasificados con sus diferentes centroides.
