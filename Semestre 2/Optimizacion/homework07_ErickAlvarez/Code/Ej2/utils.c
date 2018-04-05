#include "utils.h"

void generate_init_point(double *x, int n) {
	int b = 3;
	for(int i = 0; i < n; i++) {
		x[i] = (double)(rand() % (b + 1));
	}
}

/*----- Función de Rosenbrock -----*/
void get_gradient_ros(double *g, double *x, int n) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[n - 1] = 200.0 * (x[n - 1] - x[n - 2] * x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 200.0 * (x[i] - x[i - 1] * x[i - 1]) - 400.0 * x[i] * (x[i + 1] - x[i] * x[i]) - 2.0 * (1.0 - x[i]);
	}
}

void get_Hessian_ros(double **H, double *x, int n) {
	for(int i = 0; i < n; i++) {
		if(i < n - 1) {
			H[i + 1][i] = -400.0 * x[i];
			H[i][i + 1] = -400.0 * x[i];
		}
		if(i > 0 && i < n - 1) {
			H[i][i] = 202.0 - 400.0 * x[i + 1] + 1200.0 * x[i] * x[i];
		}
	}
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[n - 1][n - 1] = 200.0;
}

double f_ros(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n - 1; i++) {
		res += (100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow(1.0 - x[i], 2));
	}

	return res;
}

/*----- Función de Wood -----*/
void get_gradient_wood(double *g, double *x, int n) {
	g[0] = 400.0 * (pow(x[0], 3) - x[0] * x[1]) + 2.0 * (x[0] - 1.0);
	g[1] = -200.0 * (x[0] * x[0] - x[1]) + 20.2 * (x[1] - 1.0) + 19.8 * (x[3] - 1.0);
	g[2] = 2.0 * (x[2] - 1.0) + 360.0 * (pow(x[2], 3) - x[2] * x[3]);
	g[3] = -180.0 * (x[2] * x[2] - x[3]) + 20.2 * (x[3] - 1.0) + 19.8 * (x[1] - 1.0);
}

void get_Hessian_wood(double **H, double *x, int n) {
	H[0][0] = 400.0 * (3.0 * x[0] * x[0] - x[1]) + 2.0;
	H[1][1] = 220.2;
	H[2][2] = 2.0 + 360.0 * (3.0 * x[2] * x[2] - x[3]);
	H[3][3] = 200.2;

	H[0][1] = H[1][0] = -400.0 * x[0];
	H[0][2] = H[0][3] = H[2][0] = H[3][0] = H[1][2] = H[2][1] = 0.0;
	H[1][3] = H[3][1] = 19.8;
	H[2][3] = H[3][2] = -360 * x[2];
}

double f_wood(double *x) {
	double p1 = 100.0 * pow((x[0] * x[0] - x[1]), 2) + pow(x[0] - 1.0, 2) + pow(x[2] - 1.0, 2) + 90.0 * pow(x[2] * x[2] - x[3], 2);
	double p2 = 10.1 * (pow(x[1] - 1.0, 2) + pow(x[3] - 1.0, 2)) + 19.8 * (x[1] - 1.0) * (x[3] - 1.0);

	return p1 + p2;
}

/*----- Función convexa 1 -----*/
void get_gradient_cvx1(double *g, double *x, int n) {
	for(int i = 0; i < n; i++) {
		g[i] = exp(x[i]) - 1.0;
	}
}

void get_Hessian_cvx1(double **H, double *x, int n) {
	for(int i = 0; i < n; i++) {
		H[i][i] = exp(x[i]);
	}
}

double f_cvx1(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (exp(x[i]) - x[i]);
	}

	return res;
}

/*----- Función convexa 2 -----*/
void get_gradient_cvx2(double *g, double *x, int n) {
	for(int i = 0; i < n; i++) {
		g[i] = (exp(x[i]) - 1.0) * ((double)(i + 1) / (double)n);
	}
}

void get_Hessian_cvx2(double **H, double *x, int n) {
	for(int i = 0; i < n; i++) {
		H[i][i] = exp(x[i]) * ((double)(i + 1) / (double)n);
	}
}

double f_cvx2(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (exp(x[i]) - x[i]) * ((double)(i + 1) / (double)n);
	}

	return res;
}