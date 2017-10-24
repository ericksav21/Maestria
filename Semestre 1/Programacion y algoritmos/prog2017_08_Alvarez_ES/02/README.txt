Para compilar:
-Usar el comando 'make' sin comillas. Generará los archivos .o en la carpeta obj y el ejecutable en la raíz.

Para ejecutar:
-Usar el comando './main [Nombre de la imagen]' sin comillas.
-Se recibe como parámetro un string, el nombre de la imagen binaria en formato pgm.

Ejemplo de ejecución: ./main CC.pgm

Notas:
-Para más información usar 'make help' sin comillas.
-Para compilar este programa se requiere que GCC tenga disponible el estándar c++11.
-El programa generará una imagen de salida, la cual contiene la componente más grande.
