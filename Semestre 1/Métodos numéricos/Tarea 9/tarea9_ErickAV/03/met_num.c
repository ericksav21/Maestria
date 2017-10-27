#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double newton(double *x, double xc, int i) {
	if(i == 0)
		return 1.0;
	double res = 1.0;
	for(int j = 0; j < i; j++) {
		res *= (xc - x[j]);
	}

	return res;
}

double** differences(double *x, double *y, int n) {
	double **A = create_matrix(n, n, double);
	for(int i = 0; i < n; i++) {
		A[i][0] = y[i];
	}
	for(int j = 1; j < n; j++) {
		for(int i = 0; i < n - j; i++) {
			A[i][j] = (A[i + 1][j - 1] - A[i][j - 1]) / (x[i + j] - x[i]);
		}
	}

	return A;
}

double evaluate_pol(double *x, double **A, double xc, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		//Hacer el producto
		double prod = newton(x, xc, i);
		res += (A[0][i] * prod);
	}

	return res;
}

void generate(double *x, double *y, int n, char *files_name) {
	printf("Generando puntos de interpolación...\n");
	int N = 4 * n;
	double dx = (x[n - 1] - x[0]) / (double)N;
	FILE *out = fopen(files_name, "w");
	double **A = differences(x, y, n);

	for(int i = 0; i <= N; i++) {
		double xp = x[0] + i * dx;
		double pn = evaluate_pol(x, A, xp, n);

		fprintf(out, "%lf %lf\n", xp, pn);
	}

	free_matrix(A);
	fclose(out);
	printf("Puntos generados en el archivo %s\n", files_name);
}