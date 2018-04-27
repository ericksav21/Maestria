#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Vector inicial] [Número de iteraciones].\n", argv[0]);
		return 0;
	}
	int v1 = atoi(argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = sqrt(get_EPS());

	double *x0 = create_vector(3, double);
	init_x0(x0, v1);
	newton(x0, F, J, iter_max, tol);

	free_vector(x0);
	return 0;
}