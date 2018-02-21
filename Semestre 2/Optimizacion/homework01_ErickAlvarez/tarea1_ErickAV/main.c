#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta: %s [Nombre del archivo].\n", argv[0]);
		return 0;
	}

	char files_name[30];

	strcpy(files_name, argv[1]);

	int nr, nc;
	double **A;

	A = read_matrix(files_name, &nr, &nc);
	printf("Matriz A:\n");
	print_matrix(A, nr, nr);
	printf("\n");

	proc(A, nr);

	free_matrix(A);

	return 0;
}