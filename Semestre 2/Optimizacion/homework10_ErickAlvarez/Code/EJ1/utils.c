#include "utils.h"

double get_EPS() {
	double Eps = 1.0;

	while (1.0 + Eps / 2.0 != 1.0)
		Eps /= 2.0;

	return Eps;
}

double *read_init_point(char *files_name, int *n) {
	FILE *in;
	in = fopen(files_name, "r");
	int d;
	fscanf(in, "%d", &d);
	(*n) = d;
	double *res = create_vector(d, double);
	for(int i = 0; i < d; i++) {
		double aux;
		fscanf(in, "%lf", &aux);
		res[i] = aux;
	}

	fclose(in);

	return res;
}

/*----- Functions -----*/
//m = n
void ri_rosenbrock(double *x, double *y, int n, int m) {
	int k = n / 2;
	for(int i = 1; i <= k; i++) {
		int idx1 = 2 * i - 1;
		int idx2 = 2 * i;
		y[idx1 - 1] = 10.0 * (x[idx2 - 1] - (x[idx1 - 1] * x[idx1 - 1]));
		y[idx2 - 1] = 1.0 - x[idx1 - 1];
	}
}

void J_rosenbrock(double *x, double **J, int n, int m) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			J[i][j] = 0.0;
		}
	}
	for(int i = 0; i < n; i++) {
		if(i % 2 == 0) {
			J[i][i] = -20.0 * x[i];
			J[i + 1][i] = -1.0;
			J[i][i + 1] = 10.0;
		}
	}
}

/*----- LU -----*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol) {
	double *x = create_vector(nc, double);
	if(fabs(A[0][0]) < tol) {
		free_vector(x);
		if(b[0] == 0)
			printf("El sistema tiene infinitas soluciones.\n");
		else
			printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[0] = b[0] / A[0][0];
	for(int i = 1; i < nr; i++) {
		int flag = 0;
		for(int k = 0; k <= i; k++) {
			if(fabs(A[i][k]) > tol) {
				flag = 1;
				break;
			}
		}
		if(!flag) {
			free_vector(x);
			if(b[i] == 0)
				printf("El sistema tiene infinitas soluciones.\n");
			else
				printf("El sistema no tiene solución.\n");
			return NULL;
		}

		if(fabs(A[i][i]) < tol) {
			free_vector(x);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		double sum = 0.0;
		for(int j = 0; j < i; j++) {
			sum += (A[i][j] * x[j]);
		}
		x[i] = (b[i] - sum) / A[i][i];
	}

	return x;
}

double *solve_mupper(double **A, double *b, int nr, int nc, double tol) {
	double *x = create_vector(nc, double);
	if(fabs(A[nr - 1][nc - 1]) < tol) {
		free_vector(x);
		if(b[nc - 1] == 0)
			printf("El sistema tiene infinitas soluciones.\n");
		else
			printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[nc - 1] = b[nc - 1] / A[nr - 1][nc - 1];
	for(int i = nr - 2; i >= 0; i--) {
		int flag = 0;
		for(int k = nc - 1; k >= i; k--) {
			if(fabs(A[i][k]) > tol) {
				flag = 1;
				break;
			}
		}
		if(!flag) {
			free_vector(x);
			if(b[i] == 0)
				printf("El sistema tiene infinitas soluciones.\n");
			else
				printf("El sistema no tiene solución.\n");
			return NULL;
		}

		if(fabs(A[i][i]) < tol) {
			free_vector(x);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		double sum = 0.0;
		for(int j = nc - 1; j > i; j--) {
			sum += (A[i][j] * x[j]);
		}
		x[i] = (b[i] - sum) / A[i][i];
	}

	return x;
}

int factorize_LU(double **A, double ***L, double ***U, int n, double tol) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			double aux = 0.0;

			//Es una Li
			if(i > j) {
				if(fabs((*U)[j][j]) < tol) {
					return 0;
				}
				for(int k = 0; k < j; k++) {
					aux += ((*L)[i][k] * (*U)[k][j]);
				}
				(*L)[i][j] = (A[i][j] - aux) / (*U)[j][j];
			}
			else {
				for(int k = 0; k < i; k++) {
					aux += ((*L)[i][k] * (*U)[k][j]);
				}
				(*U)[i][j] = A[i][j] - aux;
			}

			if(i == j){
				(*L)[i][i] = 1.0;
			}
		}
	}

	return 1;
}

double* LU_solver(double **A, double *d, int n) {
	double tol = sqrt(get_EPS());
	double **L = create_matrix(n, n, double);
	double **U = create_matrix(n, n, double);
	double *b, *x;
	int c = factorize_LU(A, &L, &U, n, tol);
	if(c) {
		b = solve_mlower(L, d, n, n, tol);
		if(b == NULL) {
			free_matrix(L);
			free_matrix(U);
			return NULL;
		}
		x = solve_mupper(U, b, n, n, tol);
		if(x == NULL) {
			free_matrix(L);
			free_matrix(U);
			free_vector(b);
			return NULL;
		}
	}

	free_vector(b);
	free_matrix(L);
	free_matrix(U);

	return x;
}

double** get_inverse(double **A, int n) {
	double **X = create_matrix(n, n, double);
	double *e = create_vector(n, double);
	double tol = 1e-6;
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