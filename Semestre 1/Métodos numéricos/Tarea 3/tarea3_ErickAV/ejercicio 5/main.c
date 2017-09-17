#include <stdio.h>
#include <string.h>

#include "memo.h"
#include "reader.h"
#include "matriztsuperior.h"

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

	printf("Matriz:\n");
	print_matrix(A, nr, nc);
	printf("\nb:\n");
	print_vector(b, nc);
	printf("\n");

	double *x = resuelve_m_tsuperior(A, b, nr, nc, tol);

	if(x == NULL) {
		free_matrix(A);
		free_vector(b);
		return 0;
	}
	else {
		printf("x:\n");
		print_vector(x, nc);
		printf("Tamaño de la matriz: %d %d\n", nr, nc);
		printf("Error: %10.20e\n", get_error(A, x, b, nr, nc));
	}

	free_matrix(A);
	free_vector(x);
	free_vector(b);

	return 0;
}