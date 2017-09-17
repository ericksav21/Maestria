#include <stdio.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "matrizdiagonal.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta ./main [archivo 1] [archivo 2].\n");
		return 0;
	}
	double tol = pow(get_EPS(), 2.0/3.0);
	char diagonal_f[30], indep_f[30];
	strcpy(diagonal_f, argv[1]);
	strcpy(indep_f, argv[2]);

	int n;
	double *d = read_vector(diagonal_f, &n);
	double *b = read_vector(indep_f, &n);

	printf("Matriz (diagonal):\n");
	print_vector(d, n);
	printf("\nb:\n");
	print_vector(b, n);
	printf("\n");

	double *x = resuelve_m_diagonal(d, b, n, tol);

	if(x == NULL) {
		printf("El sistema no tiene solución.\n");
		free_vector(d);
		free_vector(b);
		return 0;
	}
	else {
		printf("x:\n");
		print_vector(x, n);
		printf("\nTamaño de la matriz: %d %d\n", n, n);
		printf("Error: %10.20e\n", get_error(d, x, b, n));
	}

	free_vector(x);
	free_vector(d);
	free_vector(b);

	return 0;
}