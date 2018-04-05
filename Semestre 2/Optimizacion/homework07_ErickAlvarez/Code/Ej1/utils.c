#include "utils.h"

void generate_init_point(double *x, int n) {
	int b = 3;
	for(int i = 0; i < n; i++) {
		x[i] = (double)(rand() % (b + 1));
	}
}

/*----- Función 4 -----*/
void get_gradient_sm(double *g, double *x, double *y, double lambda, int n) {
	g[0] = 2.0 * (x[0] - y[0]) - 2.0 * lambda * (x[1] - x[0]);
	g[n - 1] = 2.0 * (x[n - 1] - y[n - 1]) + 2.0 * lambda * (x[n - 1] - x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 2.0 * (x[i] - y[i]) + 2.0 * lambda * (x[i] - x[i - 1]) - 2.0 * lambda * (x[i + 1] - x[i]);
	}
}

void get_Hessian_sm(double **H, double lambda, int n) {
	for(int i = 0; i < n; i++) {
		if(i == 0 || i == n - 1) {
			H[i][i] = 2.0 + 2.0 * lambda;
		}
		else {
			H[i][i] = 2.0 + 4.0 * lambda;
		}
		if(i < n - 1) {
			H[i + 1][i] = H[i][i + 1] = -2.0 * lambda;
		}
	}
}

double f_sm(double *x, double *y, double lambda, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (x[i] - y[i]) * (x[i] - y[i]);
	}
	for(int i = 0; i < n - 1; i++) {
		res += lambda * pow((x[i + 1] - x[i]), 2);
	}

	return res;
}