#include <stdio.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	double **A = create_matrix(5, 5, double);
	double *x = create_vector(5, double), *b = create_vector(5, double);
	int iter;

	printf("A:\n");
	double aux;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			scanf("%lf", &aux);
			A[i][j] = aux;
		}
	}
	printf("\nb:\n");
	for(int i = 0; i < 5; i++) {
		scanf("%lf", &aux);
		b[i] = aux;
		x[i] = 0.0;
	}

	int res = Jacobi_Iter(A, b, x, 5, 50, &iter, 1e-7);
	printf("\n");
	print_vector(x, 5);

	free_matrix(A);
	free_vector(x);
	free_vector(b);
	return 0;
}