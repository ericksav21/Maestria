#include <stdio.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	double **A = create_matrix(3, 3, double);
	double **L = create_matrix(3, 3, double);
	double **Lt = create_matrix(3, 3, double);
	double *b = create_vector(3, double);
	double *x;
	double *y;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			scanf("%lf", &A[i][j]);
	printf("\nB:\n");
	for(int i = 0; i < 3; i++)
		scanf("%lf", &b[i]);

	int res = cholesky(A, &L, &Lt, 3, 1e-7);
	y = solve_mlower(L, b, 3, 3, 1e-7);
	x = solve_mupper(Lt, y, 3, 3, 1e-7);

	printf("\nx:\n");
	print_vector(x, 3);

	free_matrix(A);
	free_matrix(L);
	free_matrix(Lt);
	free_vector(b);
	free_vector(x);
	free_vector(y);

	return 0;
}