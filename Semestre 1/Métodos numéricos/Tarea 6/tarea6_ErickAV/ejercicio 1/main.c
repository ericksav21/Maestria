#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "funciones_matriz.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [N]\n", argv[0]);
		return 0;
	}

	char files_name[30];
	int n, nr, nc;
	
	strcpy(files_name, argv[1]);
	n = atoi(argv[2]);
	double **A = read_matrix(files_name, &nr, &nc);
	printf("Matriz:\n");
	print_matrix(A, nr, nc);
	printf("\n");

	get_eigenpairs(A, nr, nc, n);

	free_matrix(A);
	return 0;
}