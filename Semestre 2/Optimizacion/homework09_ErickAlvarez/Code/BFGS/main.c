#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones] [Tolerancia] [Tipo de Hessiana].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = atof(argv[3]);
	int hess_type = atoi(argv[4]);

	int n;
	double *x0 = read_init_point(files_name, &n);
	double **H = create_matrix(n, n, double);
	if(hess_type == 1) {
		get_Hessian(H, x0, n);
	}
	else {
		Hessian_aprox(H, x0, 0.00001, n);
	}
	double **H_inv = get_inverse(H, n);

	BFGS(x0, rosenbrock, get_gradient, H_inv, n, iter_max, tol);

	free_vector(x0);
	free_matrix(H);
	free_matrix(H_inv);
	return 0;
}