#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta %s [Archivo de datos] [N].\n", argv[0]);
		return 0;
	}

	double tol = sqrt(get_EPS());
	char files_name[30];
	int n;

	strcpy(files_name, argv[1]);
	n = atoi(argv[2]);
	double *x = create_vector(n + 1, double);
	double *y = create_vector(n + 1, double);
	double *c;

	int val = read_points(files_name, x, y, n);
	if(!val) {
		free_vector(x);
		free_vector(y);
		return 0;
	}

	double **mat = create_matrix_vander(x, n);
	c = solve_system(mat, y, n, tol);
	printf("\n");
	print_vector(c, n + 1);

	free_vector(x);
	free_vector(y);
	free_vector(c);
	free_matrix(mat);

	return 0;
}