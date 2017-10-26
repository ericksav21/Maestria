#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double lagrange(double *x, double xc, int i, int n) {
	double res = 1.0;
	for(int j = 0; j < n; j++) {
		if(i != j)
			res *= ((xc - x[j]) / (x[i] - x[j]));
	}

	return res;
}

double evaluate_pol(double *x, double *y, double xc, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (y[i] * lagrange(x, xc, i, n));
	}

	return res;
}

void generate(double *x, double *y, int n, char *files_name) {
	int N = 4 * n;
	double dx = (x[n - 1] - x[0]) / (double)N;
	FILE *out = fopen(files_name, "w");

	for(int i = 0; i <= N; i++) {
		double xp = x[0] + i * dx;
		double pn = evaluate_pol(x, y, xp, n);

		fprintf(out, "%lf %lf\n", xp, pn);
	}

	fclose(out);
}