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
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones] [Tolerancia] [V].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = atof(argv[3]);
	double v = atof(argv[4]);

	int n;
	double *x0 = read_init_point(files_name, &n);
	int m = n;
	LM(x0, n, m, ri_rosenbrock, J_rosenbrock, v, iter_max, tol);

	free_vector(x0);
	
	return 0;
}