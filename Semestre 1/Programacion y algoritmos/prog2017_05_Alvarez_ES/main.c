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
	char first_books_name[30], last_books_name[30], quality_metric[30] = "accuracy";
	int n_files_fb, n_files_lb, seed = time(NULL);

	if(!read_args(argc, argv, first_books_name, last_books_name, quality_metric, &n_files_fb, &n_files_lb, &seed))
		return 0;
	srand(seed);

	FOBJ *params = mem_obj_alloc(first_books_name, last_books_name, n_files_fb, n_files_lb);
	params = set_quality_metric(params, quality_metric);

	int *bin_vect;
	bin_vect = generate_bin_vector(params->no_words);

	printf("Realizando la clasificación.\n");
	double quality = metric_eval(params, bin_vect);

	//Liberar memoria
	params = free_obj_mem(params);
	printf("\nMétrica a usar: %s\n", quality_metric);
	printf("Calidad de la clasificación: %.0f%%\n", (quality * 100.0));
	free(params);
	delete_arr1d((void *)bin_vect);

	return 0;
}