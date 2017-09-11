#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "memo.h"
#include "frecuencias.h"
#include "separador.h"
#include "funciones.h"

int main(int argc, char **argv) {
	//Validar argumentos
	if(argc < 5) {
		printf("Ingrese los siguientes argumentos:\n");
		printf("[Nombre base de los primeros libros] [Numero de libros (1)] ");
		printf("[Nombre base de los ultimos libros] [Numero de libros (2)] ");
		printf("[Semilla (opcional)]\n");
		return 0;
	}

	char first_books_name[30], last_books_name[30];
	int n_files_fb, n_files_lb, seed = time(NULL);

	strcpy(first_books_name, argv[1]);
	strcpy(last_books_name, argv[3]);
	n_files_fb = atoi(argv[2]);
	n_files_lb = atoi(argv[4]);

	if(argc >= 6)
		seed = atoi(argv[5]);

	srand(seed);

	//Fabricamos los bloques de archivos
	int n_c_fb, n_c_lb;
	printf("**---------- Separador de archivos ----------**\n");
	n_c_fb = f_separate(first_books_name, n_files_fb, 1);
	n_c_lb = f_separate(last_books_name, n_files_lb, n_c_fb + 1);

	//Generamos la tabla de frecuencias
	printf("\n**---------- Generador de frecuencias ----------**\n");
	int frec_size = 0;
	double **frec = generate_frec("chunked", n_c_lb, &frec_size);

	printf("%d %d\n", n_c_fb, n_c_lb);

	//Se generan las matrices de las clases 1 y 2
	/*double **frec_c1 = get_part_of_matrix(frec, 0);
	double **frec_c2 = get_part_of_matrix(frec);*/

	delete_arr2d_d(frec, frec_size);
	return 0;
}