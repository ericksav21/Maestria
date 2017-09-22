#include "matriztridiagonal.h"

MAT3D* create_mat_3d(int n) {
	MAT3D *res = (MAT3D *)malloc(sizeof(MAT3D));
	res->a = create_vector(n, double);
	res->b = create_vector(n, double);
	res->c = create_vector(n, double);
	res->n = n;

	for(int i = 0; i < n; i++) {
		res->a[i] = res->b[i] = res->c[i] = 0.0;
	}

	return res;
}

MAT3D* free_mat_3d(MAT3D *src) {
	free(src->a);
	free(src->b);
	free(src->c);
	src->a = NULL;
	src->b = NULL;
	src->c = NULL;
	src->n = 0;

	return src;
}

double get_norm(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += pow(x[i], 2);
	}
	return sqrt(res);
}

double get_error(double *x, double *b, int n) {
	double *aux = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		aux[i] = x[i] - b[i];
	}
	double err = get_norm(aux, n);
	free_vector(aux);

	return err;
}

//Encuentra la solución de una matríz tridiagonal
//Se asume que las diagonales 1 y 3 tienen longitud nd - 1
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
		aux = free_mat_3d(aux);
		free(aux);
		printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[n - 1] = _d[n - 1] / aux->b[n - 1];
	for(int i = n - 2; i >= 0; i--) {
		if(fabs(aux->b[i]) < tol) {
			free_vector(x);
			aux = free_mat_3d(aux);
			free(aux);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		x[i] = (_d[i] - aux->c[i] * x[i + 1]) / aux->b[i];
	}

	aux = free_mat_3d(aux);
	free(aux);
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