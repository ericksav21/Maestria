#include "functions.h"

double rand_in_range(double a) {
	return (double)rand() / (double)(RAND_MAX / a);
}

double rand_normal(double mean, double sigma) {
	//Usar TLC
	double x = 0;
	int NSUM = 40;
	int i;
	for(i = 0; i < NSUM; i++)
		x += (double)rand() / RAND_MAX;

	//Normalizar
	x -= NSUM / 2.0;
	x /= sqrt(NSUM / 20.0);

	return mean + sigma * x;
}

double *generate_samples(double *x, int n) {
	double *y = create_vector(n, double);

	for(int i = 0; i < n; i++) {
		double eta = rand_normal(0, 0.1);
		y[i] = (sin(x[i]) / x[i]) /*+ eta*/;
	}

	return y;
}

double *least_squares(double *x, double *y, int n, int dim) {
	double tol = sqrt(get_EPS());
	double **A = create_matrix(n, dim + 1, double);
	double **At = create_matrix(dim + 1, n, double);
	double **AtA = create_matrix(dim + 1, dim + 1, double);
	double *Ay = create_vector(dim + 1, double);
	double *d, *v_aux;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < dim + 1; j++) {
			A[i][j] = pow(x[i], dim - j);
		}
	}
	At = transpose_matrix(A, At, n, dim + 1);
	AtA = mul_mat_mat(At, A, AtA, dim + 1, n);
	Ay = mul_mat_vector(At, y, Ay, dim + 1, n);

	double **L = create_matrix(dim + 1, dim + 1, double);
	double **U = create_matrix(dim + 1, dim + 1, double);

	int co = factorize_LU(AtA, &L, &U, dim + 1, tol);
	v_aux = solve_mlower(L, Ay, dim + 1, dim + 1, tol);
	d = solve_mupper(U, v_aux, dim + 1, dim + 1, tol);

	free_matrix(A);
	free_matrix(At);
	//free_matrix(AtA);
	free_matrix(L);
	free_matrix(U);
	//free_vector(Ay);
	free_vector(v_aux);

	return d;
}