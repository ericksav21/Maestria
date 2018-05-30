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
		printf("Error. Ejecuta: %s [Tolerancia] [v] [h] [Número de iteraciones].\n", argv[0]);
		return 0;
	}

	double *x = create_vector(4, double);
	double *y = create_vector(4, double);
	double *theta = create_vector(3, double);
	double *sigma = create_vector(4, double);

	int n = 2, m = 4;
	double d4 = 864.0;
	x[0] = 746.0;
	x[1] = 629.0;
	x[2] = 1571.0;
	x[3] = 155.0;

	y[0] = 1393.0;
	y[1] = 375.0;
	y[2] = 259.0;
	y[3] = 987.0;

	theta[0] = -0.0698132;
	theta[1] = 0.261799;
	theta[2] = 0.907571;

	sigma[0] = 0.139626;
	sigma[1] = 0.0802851;
	sigma[2] = 0.0575959;
	sigma[3] = 4.0;

	double tol = atof(argv[1]);
	double v = atof(argv[2]);
	double h = atof(argv[3]);
	int iter_max = atoi(argv[4]);

	//Punto inicial
	double *p0 = create_vector(n, double);
	double *pk = create_vector(n, double);
	double aux_x = 0.0, aux_y = 0.0;
	for(int i = 0; i < m; i++) {
		aux_x += x[i];
		aux_y += y[i];
	}
	p0[0] = aux_x / (double)m;
	p0[1] = aux_y / (double)m;
	pk[0] = p0[0];
	pk[1] = p0[1];

	printf("Punto inicial:\n");
	print_vector(p0, n);
	LM(pk, x, y, theta, d4, sigma, n, m, ri_adj, J_adj_aprox, v, iter_max, tol, h);

	//Ver los ángulos
	printf("Ángulos:\n");
	for(int i = 0; i < m - 1; i++) {
		printf("Theta_i: %g - Aprox. theta_i: %g\n", theta[i], atan2(pk[0] - x[i], pk[1] - y[i]));
	}
	printf("\nDistancia:\n");
	double d = pow(pk[0] - x[m - 1], 2) + pow(pk[1] - y[m - 1], 2);
	printf("D: %g - Aprox. D: %g\n", d4, sqrt(d));

	free_vector(x);
	free_vector(y);
	free_vector(theta);
	free_vector(sigma);
	free_vector(p0);
	free_vector(pk);
	
	return 0;
}