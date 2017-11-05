#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [M].\n", argv[0]);
		return 0;
	}
	double tol = sqrt(get_EPS());
	int m = atoi(argv[2]);
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
	double *M = generate_M(x, y, nr, tol);
	generate(x, y, M, m, nr, "tabla.txt");

	return 0;
}