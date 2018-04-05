Para compilar:
Usar el comando 'make' sin comillas, éste generará los archivos objeto en la carpeta 'obj' y el archivo binario en la raíz.

Para ejecutar:
Usar el comando './main' sin comillas en la terminal. En conjunto con el comando se reciben los siguientes argumentos:

-Un string. El nombre del archivo del histograma de fondo.
-Un string. El nombre del archivo del histograma del objeto.
-Un entero. El número de Gaussianas para la mezcla.
-Un flotante. El valor de sigma.

Ejemplo de ejecución: ./main H_0.txt H_1.txt 4 1.0

*En esta misma carpeta se encuentran algunas imágenes así como dos histogramas de 3 bins correspondientes a la imagen de las rosas.
*El programa generará un archivo llamado 'res.txt' que contiene la información de las alphas y las mu encontrada, dicho archivo será procesado por el programa validator.py.
*Use 'make help' sin comillas para más información de la compilación.
*El programa validator.py generará la validación de la imagen que se generará con los parámetros encontrados con la generada por el histograma, es necesario tener la imagen
y los archivos de histograma en la misma carpeta del archivo.
*En el programa valitator.py hay que cambiar el nombre de la imagen y de los histogramas por los que se trabajará, dichos cambios están en las líneas 55 y 59.
NOTA: Es posible que el programa optimizador no genere un buen resultado para alguna imagen, ya que es necesario ajustar varios parámetros hasta encontrar la configuración adecuada.
