#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta %s [Matríz de datos] [Vector de datos].\n", argv[0]);
		return 0;
	}

	double tol = get_EPS();
	int nr, nc, n;
	double **A = read_matrix(argv[1], &nr, &nc);
	double *b = read_vector(argv[2], &n);
	double *x = create_vector(n, double);

	printf("A:\n");
	print_matrix(A, n, n);
	printf("\nB:\n");
	print_vector(b, n);

	for(int i = 0; i < n; i++) {
		x[i] = 1.0;
	}

	printf("\n");
	x = conjugate_gradient(A, x, b, n, tol);

	printf("\nX:\n");
	print_vector(x, n);

	free_matrix(A);
	free_vector(b);
	free_vector(x);

	return 0;
}