#include "romberg.h"

double fi(double t) {
	double aux = (-pow(t - 5.0, 2) / 4.0);
	return exp(aux);
}

double trap(double (*func)(double), int i, double a, double b, double r_ant) {
	double res = 0.0;
	double lim = pow(2, i);
	double h = (b - a) / lim;
	for(int k = 1; k <= pow(2, i - 1); k++) {
		double aux = a + (2.0 * k - 1.0) * h;
		res += func(aux);
	}
	res *= h;
	return (0.5 * r_ant) + res;
}

double eval_romb(double (*func)(double), int n, double a, double b) {
	double **R = create_matrix(n + 1, n + 1, double);
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			R[i][j] = 0.0;
		}
	}
	//R_00
	R[0][0] = ((b - a) / 2.0) * (func(a) + func(b));
	//R_i0
	for(int i = 1; i <= n; i++) {
		R[i][0] = trap(func, i, a, b, R[i - 1][0]);
	}
	//R_ij
	//Columnas
	for(int j = 1; j <= n; j++) {
		//Filas
		for(int i = j; i <= n; i++) {
			double aux = (1.0 / (pow(4.0, j) - 1)) * (R[i][j - 1] - R[i - 1][j - 1]);
			R[i][j] = R[i][j - 1] + aux;
		}
	}

	double res = R[n][n];
	free_matrix(R);

	return res;
}