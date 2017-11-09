#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol) {
	int n = mat->n;
	double *x = create_vector(n, double);
	double *_d = create_vector(n, double);
	MAT3D *aux = create_mat_3d(n);

	aux->b[0] = mat->b[0];
	aux->c[0] = mat->c[0];
	_d[0] = d[0];

	for(int i = 1; i < n; i++) {
		aux->b[i] = (aux->b[i - 1] * mat->b[i]) - (mat->a[i] * aux->c[i - 1]);
		aux->c[i] = aux->b[i - 1] * mat->c[i];
		_d[i] = (aux->b[i - 1] * d[i]) - (mat->a[i] * _d[i - 1]);
	}

	if(fabs(aux->b[n - 1]) < tol) {
		free_vector(x);
		free_vector(_d);
		aux = free_mat_3d(aux);
		free(aux);
		printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[n - 1] = _d[n - 1] / aux->b[n - 1];
	for(int i = n - 2; i >= 0; i--) {
		if(fabs(aux->b[i]) < tol) {
			free_vector(x);
			free_vector(_d);
			aux = free_mat_3d(aux);
			free(aux);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		x[i] = (_d[i] - aux->c[i] * x[i + 1]) / aux->b[i];
	}

	aux = free_mat_3d(aux);
	free(aux);
	free_vector(_d);
	return x;
}

double f1(double x) {
	return sin(2.0 * M_PI * x);
}

double f2(double x) {
	return 4.0 * pow(x, 3) - 2.0 * x + 1.0;
}

double eval_trap(double (*func)(double), int i, double r_i1) {

}