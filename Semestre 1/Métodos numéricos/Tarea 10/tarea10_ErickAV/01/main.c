#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 4) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [N] [Lambda].\n", argv[0]);
		return 0;
	}
	int n = atoi(argv[2]);
	double lambda = atof(argv[3]);
	char files_name[30];

	strcpy(files_name, argv[1]);

	int nr, nc;
	double **data;

	data = read_matrix(files_name, &nr, &nc);

	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}
	generate(x, y, nr, n, lambda, "tabla.txt");
	printf("Tabla generada.\n");

	free_vector(x);
	free_vector(y);
	free_matrix(data);

	return 0;
}