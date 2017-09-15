#include "matrizdiagonal.h"

double get_error(double *d, double *x, double *b, int n) {
	double err = 0.0;
	for(int i = 0; i < n; i++)
		err += pow(d[i] * x[i] - b[i], 2);

	return sqrt(err);
}

//Encuentra la solución de una matríz diagonal (en forma de vector)
double *resuelve_m_diagonal(double *d, double *b, int n, double tol) {
	double *x = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		if(fabs(d[i]) < tol) {
			free_vector(x);
			return NULL;
		}
		x[i] = b[i] / d[i];
	}

	return x;
}

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

void print_vector(double *vect, int n) {
	for(int i = 0; i < n; i++) {
		printf("%lf ", vect[i]);
	}
	printf("\n");
}

void print_matrix(double **mat, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			printf("%lf ", mat[i][j]);
		}
		printf("\n");
	}
}