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
	if(argc < 5) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Número de iteraciones] [Tolerancia] [V].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	int iter_max = atoi(argv[2]);
	double tol = atof(argv[3]);
	double v = atof(argv[4]);

	int nr, nc;
	double **data = read_matrix(files_name, &nr, &nc);
	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}
	//Punto inicial
	int n = 4, m = nr;
	double *p0 = create_vector(n, double);
	p0[0] = p0[1] = 0.0;
	p0[2] = 15.0;
	p0[3] = -2.0;
	p0[4] = 1.0;
	LM(p0, x, y, n, m, ri_adj, J_adj, v, iter_max, tol);
	write_output(x, y, p0, m);

	free_matrix(data);
	free_vector(x);
	free_vector(y);
	free_vector(p0);
	
	return 0;
}