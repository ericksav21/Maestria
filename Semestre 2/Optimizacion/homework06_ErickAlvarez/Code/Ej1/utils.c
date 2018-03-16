#include "utils.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double *read_init_point(char *files_name, int *n) {
	FILE *file;
	file = fopen(files_name, "r");

	double *x;
	if(file) {
		int nn;
		fscanf(file, "%d", &nn);
		(*n) = nn;
		x = create_vector(nn, double);
		for(int i = 0; i < nn; i++) {
			fscanf(file, "%lf", &x[i]);
		}

		fclose(file);
		return x;
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return NULL;
	}
}

/*----- Función 1 - Rosembrock 2 -----*/

void get_gradient_1(double *g, double *x) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[1] = 200.0 * (x[1] - x[0] * x[0]);
}

void get_Hessian_1(double **H, double *x) {
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[0][1] = H[1][0] = -400.0 * x[0];
	H[1][1] = 200.0;
}

double f_1(double *x) {
	return 100.0 * pow(x[1] - x[0] * x[0], 2) + pow(1.0 - x[0], 2);
}

/*----- Función 2 - Rosembrock 100 -----*/

void get_gradient_2(double *g, double *x, int n) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[n - 1] = 200.0 * (x[n - 1] - x[n - 2] * x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 200.0 * (x[i] - x[i - 1] * x[i - 1]) - 400.0 * x[i] * (x[i + 1] - x[i] * x[i]) - 2.0 * (1.0 - x[i]);
	}
}

void get_Hessian_2(double **H, double *x, int n) {
	for(int i = 0; i < n; i++) {
		if(i < n - 1) {
			H[i + 1][i] = -400.0 * x[i];
			H[i][i + 1] = -400.0 * x[i];
		}
		if(i > 0 && i < n - 1) {
			H[i][i] = 202.0 - 400.0 * (x[i + 1] - 3.0 * x[i] * x[i]);
		}
	}
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[n - 1][n - 1] = 200.0;
}

/*void get_Hessian_2(MAT3D *mat, double *x, int n) {
	double *a = create_vector(n, double);
	double *b = create_vector(n, double);
	double *c = create_vector(n, double);

	for(int i = 0; i < n; i++) {
		if(i > 0) {
			a[i] = -400.0 * x[i - 1];
		}
		if(i < n - 1) {
			c[i] = -400.0 * x[i];
		}
		if(i > 0 && i < n - 1) {
			b[i] = 202.0 - 400.0 * (x[i + 1] - 3.0 * x[i] * x[i]);
		}
	}

	a[0] = 0.0;
	c[n - 1] = 0.0;
	b[0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	b[n - 1] = 200.0;

	mat->a = copy_vector(a, mat->a, n);
	mat->b = copy_vector(b, mat->b, n);
	mat->c = copy_vector(c, mat->c, n);

	free_vector(a);
	free_vector(b);
	free_vector(c);

	return mat;
}*/

double f_2(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n - 1; i++) {
		res += (100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow(1.0 - x[i], 2));
	}

	return res;
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
		x = solve_mupper(U, b, n, n, tol);
	}

	free_vector(b);
	free_matrix(L);
	free_matrix(U);

	return x;
}

double *solve_m_tridiagonal(MAT3D *mat, double *d, double tol) {
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

int cholesky(double **A, double ***L, double ***Lt, int n, double tol) {
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
				(*Lt)[i][j] = (*L)[i][j];
			}
			else {
				if(fabs((*L)[j][j]) < tol) {
					return 0;
				}
				(*L)[i][j] = 1.0 / (*L)[j][j] * (A[i][j] - aux);
				(*Lt)[j][i] = (*L)[i][j];
			}
		}
	}

	return 1;
}