#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta %s [Archivo de datos].\n", argv[0]);
		return 0;
	}

	double tol = sqrt(get_EPS());
	char files_name[30];
	int nr, nc;

	strcpy(files_name, argv[1]);
	double **data;

	data = read_matrix(files_name, &nr, &nc);
	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}

	double **mat = create_matrix_vander(x, nr);
	double *c = solve_system(mat, y, nr, tol);
	generate(x, c, nr, "tabla.txt");

	free_vector(x);
	free_vector(y);
	free_vector(c);
	free_matrix(mat);
	free_matrix(data);

	return 0;
}