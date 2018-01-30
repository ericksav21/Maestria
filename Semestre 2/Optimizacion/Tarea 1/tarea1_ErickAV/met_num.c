#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

int cholesky(double **A, double ***L, int n, double tol) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (i + 1); j++) {
			double aux = 0.0;
			for(int k = 0; k < j; k++) {
				aux += (*L)[i][k] * (*L)[j][k];
			}
			if(i == j) {
				if(A[i][i] - aux < 0) {
					return 0;
				}
				(*L)[i][j] = sqrt(A[i][i] - aux);
			}
			else {
				if(fabs((*L)[j][j]) < tol) {
					return 0;
				}
				(*L)[i][j] = (1.0 / (*L)[j][j]) * (A[i][j] - aux);
			}
		}
	}

	return 1;
}

double norm_1(double **A, int n) {
	double res = 0.0;
	//Columnas
	for(int i = 0; i < n; i++) {
		double aux = 0.0;
		for(int j = 0; j < n; j++) {
			aux += fabs(A[j][i]);
		}
		if(i == 0) {
			res = aux;
		}
		else {
			res = max(res, aux);
		}
	}

	return res;
}

void proc(double **A, int n) {
	//Calcular A^T
	double tol = sqrt(get_EPS());
	double **At = create_matrix(n, n, double);
	double **As = create_matrix(n, n, double);
	At = transpose_matrix(A, At, n, n);

	//Verificar si At es simétrica
	As = substract_mat(A, At, As, n, n);
	double norm = norm_1(As, n);
	printf("Norma 1 de A - At: %g\n", norm);
	if(norm > tol) {
		printf("La matriz no es simétrica y se sustituirá por 1/2(A + A^t).\n\n");
		A = add_mat(A, At, A, n, n);
		A = scale_mat(A, A, n, n, 0.5);
	}
	else {
		printf("La matriz es simétrica.\n");
	}

	int cont = 0;
	double lambda = 0.01;
	double **L = create_matrix(n, n, double);
	while(1) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				L[i][j] = 0.0;
			}
		}
		int res = cholesky(A, &L, n, tol);
		if(res == 0) {
			printf("No se pudo calcular la factorización de Cholesky. Se perturbará la matriz.\n");
			for(int i = 0; i < n; i++) {
				A[i][i] += lambda;
			}
		}
		else {
			printf("\nFactorización de Cholesky realizada correctamente, se tuvo que perturbar: %d veces.\n", cont);
			break;
		}
		cont++;
	}

	printf("Matriz L:\n");
	print_matrix(L, n, n);
	double **Lt = create_matrix(n, n, double);
	double **An = create_matrix(n, n, double);
	Lt = transpose_matrix(L, Lt, n, n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			An[i][j] = 0.0;
		}
	}
	An = mul_mat_mat(L, Lt, An, n);
	An = substract_mat(A, An, An, n, n);
	norm = norm_1(An, n);

	printf("\nNorma 1 de A - LL^T: %g\n", norm);

	free_matrix(At);
	free_matrix(As);
	free_matrix(An);
	free_matrix(L);
	free_matrix(Lt);
}