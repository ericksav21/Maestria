#include <stdio.h>
#include <string.h>

#include "memo.h"
#include "reader.h"
#include "operacionesmatriz.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta ./main [archivo 1] [archivo 2].\n");
		return 0;
	}
	double tol = pow(get_EPS(), 2.0/3.0);
	char mtriang_f[30], indep_f[30];
	strcpy(mtriang_f, argv[1]);
	strcpy(indep_f, argv[2]);

	int n, nr, nc;
	double **A = read_matrix(mtriang_f, &nr, &nc);
	double *b = read_vector(indep_f, &n);
	double **L = create_matrix(nr, nc, double);
	double **U = create_matrix(nr, nc, double);

	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			L[i][j] = U[i][j] = 0.0;
		}
	}

	printf("Matriz:\n");
	printf("%d %d\n", nr, nc);

	print_matrix(A, nr, nc);
	printf("\n");
	print_vector(b, n);
	printf("\n");

	int res = factorize_LU(A, &L, &U, nr, tol);
	if(res == 0) {
		printf("No se pudo factorizar el sistema.\n");
		free_matrix(L);
		free_matrix(U);
		free_matrix(A);
		free_vector(b);

		return 0;
	}

	printf("L:\n");
	print_matrix(L, nr, nc);
	printf("\nU:\n");
	print_matrix(U, nr, nc);
	printf("\n");

	double *y = resuelve_m_tinferior(L, b, nr, nc, tol);
	double *x = resuelve_m_tsuperior(U, y, nr, nc, tol);
	
	print_vector(x, nc);
	printf("\n");

	printf("Error: %10.20e\n", get_error(A, x, b, nr, nc));

	free_matrix(L);
	free_matrix(U);
	free_matrix(A);
	free_vector(y);
	free_vector(x);
	free_vector(b);

	return 0;
}