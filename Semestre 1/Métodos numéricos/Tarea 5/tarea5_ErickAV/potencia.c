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
			printf("%8.3f   ", mat[i][j]);
		}
		printf("\n");
	}
}

double* substract_vectors(double *v1, double *v2, double *x, int n) {
	for(int i = 0; i < n; i++) {
		x[i] = v1[i] - v2[i];
	}

	return x;
}

double* scale_vector(double *v, double *x, double alpha, int n) {
	for(int i = 0; i < n; i++) {
		x[i] = v[i] * alpha;
	}

	return x;
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

double get_norm(double *v, int n) {
	double sum = 0.0;
	for(int i = 0; i < n; i++) {
		sum += v[i] * v[i];
	}
	return sqrt(sum);
}

double* normalize(double *v, int n) {
	double norm = get_norm(v, n);

	for(int i = 0; i < n; i++) {
		v[i] /= norm;
	}

	return v;
}

double get_err(double **A, double *v, double vp, int nr, int nc) {
	double *aux1 = create_vector(nc, double);
	double *aux2 = create_vector(nc, double);
	double *aux3 = create_vector(nc, double);
	aux1 = mul_mat_vec(A, v, aux1, nr, nc);
	aux2 = scale_vector(v, aux2, vp, nc);
	aux3 = substract_vectors(aux1, aux2, aux3, nc);
	double err = get_norm(aux3, nc);

	free_vector(aux1);
	free_vector(aux2);
	free_vector(aux3);

	return err;
}

double power_iteration(double **A, double *v_ant, int nr, int nc, int iter, double tol) {
	double *v_act = create_vector(nc, double);
	double oldVp = 1, newVp = 0;
	double err = 1e10;
	int t = 0;
	for(int i = 0; i < nc; i++) {
		v_ant[i] = 1.0;
		v_act[i] = 0.0;
	}

	while(1) {
		newVp = 0;
		v_ant = normalize(v_ant, nc);
		v_act = mul_mat_vec(A, v_ant, v_act, nr, nc);

		for(int i = 0; i < nc; i++) {
			newVp += v_act[i] * v_ant[i];
		}

		err = get_err(A, v_act, newVp, nr, nc);
		if(err < tol || t >= iter)
			break;

		t++;
		for(int i = 0; i < nc; i++) {
			v_ant[i] = v_act[i];
		}
	}

	if(t >= iter)
		printf("El método se tuvo que detener debido al límite de iteraciones.\n");
	else
		printf("Método terminado.\n");
	
	printf("Número de Iteraciones realizadas: %d\n", t);
	printf("Error en la última iteración: %g\n", err);


	free_vector(v_act);
	return newVp;
}