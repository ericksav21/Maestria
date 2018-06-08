Instrucciones sobre el código desarrollado:
*utils.py contiene algunas funciones para la generación de los datos (puntos aleatorios) en los diferentes experimentos.
*optimization.py contiene las funciones principales sobre la media generalizada, PCA y PCA robusto.
*mnist.py contiene funciones para usar el conjunto de datos MNIST.

*Es necesario tener python v 3.x instalada para poder ejecutar el código.
*Las siguientes librerías son necesarias para ejecutar el código:
	-Numpy
	-Matplotlib
	-Sklearn

Datos de los experimentos:
*example1.py contiene el experimento realizado con la media generalizada, basta ejecutar: 'python3 example1.py [p]' donde [p] es el valor de p que usa la media generalizada.
*example2.py contiene el experimento realizado con PCA y PCA robusto usando puntos en 2D en forma de elipse, basta ejecutar: 'python3 example2.py [p]' donde [p] es el valor de p que usa la media generalizada.
*example3.py contiene el experimento realizado con PCA y PCA robusto usando puntos en 2D como viene en el paper, basta ejecutar: 'python3 example3.py [p]' donde [p] es el valor de p que usa la media generalizada.
*example4.py contiene el código para generar la gráfica Ángulo-Función de costo que se mencionó en el paper, basta ejecutar: 'python3 example4.py [p]' donde [p] es el valor de p que usa la media generalizada.
*clustering.py contiene el experimento realizado para clusterizar datos proyectados usando PCA y PCA robusto, basta ejecutar: 'python3 clustering.py [m] [p]' donde [m] es la dimensión a la que se van a proyectar los datos y [p] es el valor de p que usa la media generalizada, para este experimento se usó el método de K-Means implementado por la librería sklearn.
