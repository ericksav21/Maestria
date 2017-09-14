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