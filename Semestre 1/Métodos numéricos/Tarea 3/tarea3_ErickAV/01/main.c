#include <stdio.h>
#include <string.h>

#include "memo.h"
#include "reader.h"
#include "matrizdiagonal.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta ./main [archivo 1] [archivo 2].\n");
		return 0;
	}
	double tol = 1e-7;
	char diagonal_f[30], indep_f[30];
	strcpy(diagonal_f, argv[1]);
	strcpy(indep_f, argv[2]);

	int n;
	double *d = read_vector(diagonal_f, &n);
	double *b = read_vector(indep_f, &n);

	double *x = resuelve_m_diagonal(d, b, n, tol);

	if(x == NULL) {
		printf("El sistema no tiene solución.\n");
		free_vector(d);
		free_vector(b);
		return 0;
	}
	else {
		printf("Tamaño de la matriz: %dx%d\n", n, n);
		printf("Error: %lf\n", get_error(d, x, b, n));
	}

	free_vector(x);
	free_vector(d);
	free_vector(b);

	return 0;
}