#include "utils.h"

double *read_init_point(char *files_name, int *n) {
	FILE *file;
	file = fopen(files_name, "r");

	double *x;
	if(file) {
		int nn;
		fscanf(file, "%d", &nn);
		(*n) = nn;
		x = create_vector(nn, double);
		for(int i = 0; i < nn; i++) {
			fscanf(file, "%lf", &x[i]);
		}

		fclose(file);
		return x;
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return NULL;
	}
}

/*----- Función 1 -----*/

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

/*----- Función 2 -----*/

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

/*----- Función 3 -----*/

void get_gradient_3(double *g, double *x, int n) {
	g[0] = 400.0 * (pow(x[0], 3) - x[0] * x[1]) + 2.0 * (x[0] - 1.0);
	g[1] = -200.0 * (x[0] * x[0] - x[1]) + 20.2 * (x[1] - 1.0) + 19.8 * (x[3] - 1.0);
	g[2] = 2.0 * (x[2] - 1.0) + 360.0 * (pow(x[2], 3) - x[2] * x[3]);
	g[3] = -180.0 * (x[2] * x[2] - x[3]) + 20.2 * (x[3] - 1.0) + 19.8 * (x[1] - 1.0);
}

void get_Hessian_3(double **H, double *x, int n) {
	H[0][0] = 400.0 * (3.0 * x[0] * x[0] - x[1]) + 2.0;
	H[1][1] = 220.2;
	H[2][2] = 2.0 + 360.0 * (3.0 * x[2] * x[2] - x[3]);
	H[3][3] = 200.2;

	H[0][1] = H[1][0] = -400.0 * x[0];
	H[0][2] = H[0][3] = H[2][0] = H[3][0] = H[1][2] = H[2][1] = 0.0;
	H[1][3] = H[3][1] = 19.8;
	H[2][3] = H[3][2] = -360 * x[2];
}

double f_3(double *x) {
	double p1 = 100.0 * pow((x[0] * x[0] - x[1]), 2) + pow(x[0] - 1.0, 2) + pow(x[2] - 1.0, 2) + 90.0 * pow(x[2] * x[2] - x[3], 2);
	double p2 = 10.1 * (pow(x[1] - 1.0, 2) + pow(x[3] - 1.0, 2)) + 19.8 * (x[1] - 1.0) * (x[3] - 1.0);

	return p1 + p2;
}

/*----- Función 4 -----*/
void get_gradient_4(double *g, double *x, double *y, double lambda, int n) {
	g[0] = 2.0 * (x[0] - y[0]) - 2.0 * lambda * (x[1] - x[0]);
	g[n - 1] = 2.0 * (x[n - 1] - y[n - 1]) + 2.0 * lambda * (x[n - 1] - x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 2.0 * (x[i] - y[i]) + 2.0 * lambda * (x[i] - x[i - 1]) - 2.0 * lambda * (x[i + 1] - x[i]);
	}
}

void get_Hessian_4(MAT3D *mat, double lambda, int n) {
	double *a = create_vector(n, double);
	double *b = create_vector(n, double);
	double *c = create_vector(n, double);

	for(int i = 0; i < n; i++) {
		a[i] = c[i] = -2.0 * lambda;
		b[i] = 2.0 + 4.0 * lambda;
	}

	a[0] = 0.0;
	c[n - 1] = 0.0;
	b[0] = b[n - 1] = 2.0 + 2.0 * lambda;

	mat->a = copy_vector(a, mat->a, n);
	mat->b = copy_vector(b, mat->b, n);
	mat->c = copy_vector(c, mat->c, n);

	free_vector(a);
	free_vector(b);
	free_vector(c);
}

double f_4(double *x, double *y, double lambda, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (x[i] - y[i]) * (x[i] - y[i]);
	}
	for(int i = 0; i < n - 1; i++) {
		res += lambda * pow((x[i + 1] - x[i]), 2);
	}

	return res;
}