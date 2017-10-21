#include "funciones.h"

double **create_matrix_vander(int n) {
	double **mat = create_matrix(n, n, double);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			mat[i][j] = pow((double)(i + 1) / (double)n, j);
		}
	}

	return mat;
}

void ej_2(double **A, int n) {
	//printf("\n----------Ej. 2:----------");
	double **At = create_matrix(n, n, double);
	double **B = create_matrix(n, n, double);
	At = transpose_matrix(A, At, n, n);

	printf("\nAt:\n");
	print_matrix(At, n, n);

	printf("\nA*At:\n");
	B = mul_mat_mat(A, At, B, n);
	print_matrix(B, n, n);

	//Calcular los eigenvalores
	double **V = NULL;
	double **Borg = create_matrix(n, n, double);
	double tol = sqrt(DBL_EPSILON);
	int k_res, M = 20000;

	Borg = copy_matrix(B, Borg, n, n);
	double e = Jacobi(&B, &V, n, n, tol, M, &k_res);

	printf("\nEigenvalores:\n");
	double *eig = create_vector(n, double);
	double e_min = 100000.0;
	double e_max = -100000.0;

	for(int i = 0; i < n; i++) {
		eig[i] = B[i][i];
		if(eig[i] > e_max)
			e_max = eig[i];
		if(eig[i] < e_min)
			e_min = eig[i];

		printf("%g\n", eig[i]);
	}

	double s1 = sqrt(e_max);
	double sn = sqrt(e_min);
	double k2 = (s1 / sn);
	printf("\nS1: %g\n", s1);
	printf("Sn: %g\n", sn);
	printf("Cociente k2: %g\n", k2);

	free_matrix(At);
	free_matrix(B);
	free_matrix(Borg);
	free_matrix(V);
	free_vector(eig);
}

double **ej_3(double **A, int n) {
	double **X = create_matrix(n, n, double);
	double *e = create_vector(n, double);
	double tol = sqrt(DBL_EPSILON);
	for(int i = 0; i < n; i++) {
		e[i] = 0.0;
	}

	double **L = create_matrix(n, n, double);
	double **U = create_matrix(n, n, double);
	int res = factorize_LU(A, &L, &U, n, tol);

	for(int i = 0; i < n; i++) {
		e[i] = 1.0;
		double *y = solve_mlower(L, e, n, n, tol);
		double *x = solve_mupper(U, y, n, n, tol);

		//Copiar el resultado
		for(int j = 0; j < n; j++) {
			X[j][i] = x[j];
		}

		e[i] = 0.0;
		free_vector(y);
		free_vector(x);
	}

	free_matrix(L);
	free_matrix(U);
	free_vector(e);

	return X;
}

double ej_4(double **A, int n) {
	//Calcular la norma infinito
	double max = 0.0;
	for(int i = 0; i < n; i++) {
		double aux = 0.0;
		for(int j = 0; j < n; j++) {
			aux += fabs(A[i][j]);
		}
		if(aux > max)
			max = aux;
	}

	return max;
}

double ej_5(double **A, int n) {
	double *b = create_vector(n, double);
	double *c = create_vector(n, double);
	double tol = sqrt(DBL_EPSILON);

	for(int i = 0; i < n; i++) {
		b[i] = sin((double)(i + 1) / (double)n);
	}
	for(int i = 0; i < n; i++) {
		c[i] = b[i] + (pow(-1, i + 1) * 0.001);
	}

	double **L = create_matrix(n, n, double);
	double **U = create_matrix(n, n, double);
	int res = factorize_LU(A, &L, &U, n, tol);

	//Ax1 = b
	double *y1 = solve_mlower(L, b, n, n, tol);
	double *x1 = solve_mupper(U, y1, n, n, tol);

	//Ax2 = c
	double *y2 = solve_mlower(L, c, n, n, tol);
	double *x2 = solve_mupper(U, y2, n, n, tol);

	printf("\nx1:\n");
	print_vector(x1, n);
	printf("\nx2:\n");
	print_vector(x2, n);

	printf("\n||x1 - x2||: %0.20e\n", vect_err(x1, x2, n));

	free_vector(x1);
	free_vector(y1);
	free_vector(x2);
	free_vector(y2);
	free_vector(b);
	free_vector(c);
	free_matrix(L);
	free_matrix(U);
}