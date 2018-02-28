#include "utils.h"

/*Función 1*/

void get_gradient_1(double *g, double *x) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[1] = 200.0 * (x[1] - x[0] * x[0]);
}

void get_Hessian_1(double **H, double *x) {
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[0][1] = H[1][0] = -400.0 * x[0];
	H[1][1] = 200.0;
}

double f_1(double *x) {
	return 100.0 * pow(x[1] - x[0] * x[0], 2) + pow(1.0 - x[0], 2);
}

/*Función 2*/

void get_gradient_2(double *g, double *x, int n) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[n - 1] = 200.0 * (x[n - 1] - x[n - 2] * x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 200.0 * (x[i] - x[i - 1] * x[i - 1]) - 400.0 * x[i] * (x[i + 1] - x[i] * x[i]) - 2.0 * (1.0 - x[i]);
	}
}

void get_Hessian_2(MAT3D *mat, double *x, int n) {
	double *a = create_vector(n, double);
	double *b = create_vector(n, double);
	double *c = create_vector(n, double);

	for(int i = 0; i < n; i++) {
		if(i > 0) {
			a[i] = -400.0 * x[i - 1];
		}
		if(i < n - 1) {
			c[i] = -400.0 * x[i];
		}
		if(i > 0 && i < n - 1) {
			b[i] = 202.0 - 400.0 * (x[i + 1] - 3.0 * x[i] * x[i]);
		}
	}

	a[0] = 0.0;
	c[n - 1] = 0.0;
	b[0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	b[n - 1] = 200.0;

	mat->a = copy_vector(a, mat->a, n);
	mat->b = copy_vector(b, mat->b, n);
	mat->c = copy_vector(c, mat->c, n);

	free_vector(a);
	free_vector(b);
	free_vector(c);

	return mat;
}

double f_2(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n - 1; i++) {
		res += (100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow(1.0 - x[i], 2));
	}

	return res;
}