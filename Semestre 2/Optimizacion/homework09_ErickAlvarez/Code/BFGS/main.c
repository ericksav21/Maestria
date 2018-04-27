#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 4) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones] [Tolerancia].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = atof(argv[3]);

	int n;
	double *x0 = read_init_point(files_name, &n);
	double **H = create_matrix(n, n, double);
	get_Hessian(H, x0, n);
	double **H_inv = get_inverse(H, n);

	BFGS(x0, rosenbrock, get_gradient, H_inv, n, iter_max, tol);

	free_vector(x0);
	free_matrix(H);
	free_matrix(H_inv);
	return 0;
}