#include "potencia.h"

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

double* mul_mat_vec(double **A, double *v, double *x, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		double sum = 0.0;
		for(int j = 0; j < nc; j++) {
			sum += A[i][j] * v[j];
		}
		x[i] = sum;
	}

	return x;
}

double* normalize(double *v, int n) {
	double sum = 0.0;
	for(int i = 0; i < n; i++) {
		sum += v[i] * v[i];
	}
	sum = sqrt(sum);
	for(int i = 0; i < n; i++) {
		v[i] /= sum;
	}

	return v[i];
}

double power_iteration(double **A, double *v_ant, int nr, int nc) {
	double *v_act = create_vector(nc, double);
	for(int i = 0; i < nc; i++)
		v_act[i] = 0.0;



	free_vector(v_act);
}