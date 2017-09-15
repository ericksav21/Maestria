#include <stdio.h>
#include <string.h>

#include "memo.h"
#include "reader.h"
#include "matriztinferior.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta ./main [archivo 1] [archivo 2].\n");
		return 0;
	}
	double tol = 1e-7;
	char mtriang_f[30], indep_f[30];
	strcpy(mtriang_f, argv[1]);
	strcpy(indep_f, argv[2]);

	int n, nr, nc;
	double **A = read_matrix(mtriang_f, &nr, &nc);
	double *b = read_vector(indep_f, &n);

	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int j = 0; j < nc; j++) {
		printf("%lf ", b[j]);
	}
	printf("\n");

	double *x = resuelve_m_tinferior(A, b, nr, nc, tol);

	for(int i = 0; i < nc; i++)
		printf("%lf ", x[i]);
	printf("\n");

	if(x == NULL) {
		free_matrix(A);
		free_vector(b);
		return 0;
	}
	else {
		printf("Tamaño de la matriz: %dx%d\n", nr, nc);
		printf("Error: %lf\n", get_error(A, x, b, nr, nc));
	}

	free_matrix(A);
	free_vector(x);
	free_vector(b);

	return 0;
}