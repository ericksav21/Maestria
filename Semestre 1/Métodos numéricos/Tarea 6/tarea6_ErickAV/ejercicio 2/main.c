#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "funciones_matriz.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones]\n", argv[0]);
		return 0;
	}

	char files_name[30];
	int M, nr, nc;
	
	strcpy(files_name, argv[1]);
	M = atoi(argv[2]);
	double **A = read_matrix(files_name, &nr, &nc);
	printf("Matriz:\n");
	print_matrix(A, nr, nc);
	printf("\n");

	get_eigenpairs(A, nr, nc, M);

	free_matrix(A);
	return 0;
}