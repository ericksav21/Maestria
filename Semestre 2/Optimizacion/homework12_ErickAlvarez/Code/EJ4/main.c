#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	/*if(argc < 6) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones] [Tolerancia] [V] [h].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = atof(argv[3]);
	double v = atof(argv[4]);
	double h = atof(argv[5]);*/

	int n = 2;
	int m = 4;
	double *x = create_vector(n, double);
	x[0] = -15.0;
	x[1] = -10.0;
	QP(x, n, m, 0.1, 0.005, 1.0, 0.0001);

	free_vector(x);
	
	return 0;
}