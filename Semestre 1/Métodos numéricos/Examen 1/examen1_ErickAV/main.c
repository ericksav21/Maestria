#include <stdio.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"
#include "funciones.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta %s [N].\n", argv[0]);
		return 0;
	}
	int n = atoi(argv[1]);
	double **mat = create_matrix_vander(n);
	double **X;

	printf("A:\n");
	print_matrix(mat, n, n);
	ej_2(mat, n);
	X = ej_3(mat, n);

	printf("\nInversa de A:\n");
	print_matrix(X, n, n);

	double k_inf = ej_4(mat, n) * ej_4(X, n);
	printf("\nk_inf: %g\n", k_inf);

	ej_5(mat, n);

	free_matrix(mat);
	free_matrix(X);

	return 0;
}