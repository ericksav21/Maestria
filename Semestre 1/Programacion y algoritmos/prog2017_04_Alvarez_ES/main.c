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
	int no_words = 0, frec_size = n_c_lb;
	double **frec = generate_frec("chunked", n_c_lb, &no_words);

	printf("%d %d\n", n_c_fb, n_c_lb);

	//Se generan las matrices de las clases 1 y 2
	printf("\n**---------- Clasificador de texto ----------**\n");
	printf("Generando las clases.\n");
	//Tamaño: n_c_fb
	double **frec_c1 = get_part_of_matrix(frec, 0, n_c_fb - 1, no_words);
	//Tamaño: n_c_lb
	double **frec_c2 = get_part_of_matrix(frec, n_c_fb, n_c_lb - 1, no_words);

	int m1sz = n_c_fb, m2sz = n_c_lb - n_c_fb;

	//Generar los conjuntos de entrenamiento y prueba
	//frec_size = Num de bloques en general
	int **trying_set_c1 = create_arr2d_by_chunks_i(m1sz, 2);
	int **trying_set_c2 = create_arr2d_by_chunks_i(m2sz, 2);
	int *bin_vect;

	for(int i = 0; i < m1sz; i++) {
		trying_set_c1[i][0] = 0;
		trying_set_c1[i][1] = 1;
	}
	for(int i = 0; i < m2sz; i++) {
		trying_set_c2[i][0] = 0;
		trying_set_c2[i][1] = 2;
	}

	printf("Generando los conjuntos de entrenamiento y prueba.\n");
	trying_set_c1 = generate_trying_set(trying_set_c1, m1sz);
	trying_set_c2 = generate_trying_set(trying_set_c2, m2sz);
	bin_vect = generate_bin_vector(no_words);



	printf("Realizando la clasificación.\n");
	clasify(trying_set_c1, trying_set_c2, bin_vect, frec_c1, frec_c2, m1sz, m2sz, no_words);

	delete_arr2d_i(trying_set_c1, m1sz);
	delete_arr2d_i(trying_set_c2, m2sz);
	delete_arr1d(bin_vect);
	delete_arr2d_d(frec_c1, m1sz);
	delete_arr2d_d(frec_c2, m2sz);
	delete_arr2d_d(frec, frec_size);

	return 0;
}