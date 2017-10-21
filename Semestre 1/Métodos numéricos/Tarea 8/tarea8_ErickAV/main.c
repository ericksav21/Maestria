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

	double tol = sqrt(get_EPS());
	int nr, nc, n;
	double **A = read_matrix(argv[1], &nr, &nc);
	double *b = read_vector(argv[2], &n);
	double *x = create_vector(n, double);

	printf("Tamaño de la matriz: %d %d\n", n, n);

	for(int i = 0; i < n; i++) {
		x[i] = 1.0;
	}

	int iter;
	x = conjugate_gradient(A, x, b, n, &iter, tol);

	printf("\nX:\n");
	print_vector(x, n);

	printf("\nNúmero de iteraciones: %d\n", iter);
	printf("Error: %g\n", get_err(A, x, b, n, n));

	free_matrix(A);
	free_vector(b);
	free_vector(x);

	return 0;
}