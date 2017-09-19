#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "memo.h"
#include "frecuencias.h"
#include "separador.h"
#include "funciones.h"
#include "metricas_calidad.h"

int main(int argc, char **argv) {
	char first_books_name[30], last_books_name[30];
	int n_files_fb, n_files_lb, seed = time(NULL);
	if(!read_args(argc, argv, first_books_name, last_books_name, &n_files_fb, &n_files_lb, &seed)) return 0;
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
	int *trying_set_c1 = (int *)create_arr1d(m1sz, sizeof(int));
	int *trying_set_c2 = (int *)create_arr1d(m2sz, sizeof(int));
	int *bin_vect;

	for(int i = 0; i < m1sz; i++) {
		trying_set_c1[i] = 0;
	}
	for(int i = 0; i < m2sz; i++) {
		trying_set_c2[i] = 0;
	}

	printf("Generando los conjuntos de entrenamiento y prueba.\n");
	trying_set_c1 = generate_trying_set(trying_set_c1, m1sz);
	trying_set_c2 = generate_trying_set(trying_set_c2, m2sz);
	bin_vect = generate_bin_vector(no_words);

	//Generar el objeto con los parámetros para la clasificación
	FOBJ *params = create_clasifier_params(trying_set_c1, trying_set_c2, frec_c1, frec_c2, m1sz, m2sz, no_words);
	//Ya no se necesita más a estos objetos
	close_items(trying_set_c1, trying_set_c2, frec_c1, frec_c2, frec, m1sz, m2sz, frec_size);

	printf("Realizando la clasificación.\n");
	clasify(params, bin_vect);

	//Liberar memoria
	params = free_obj_mem(params);
	free(params);
	delete_arr1d((void *)bin_vect);

	return 0;
}