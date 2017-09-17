#include "operacionesmatriz.h"

double *mul_mat_vector(double **A, double *v, double *x, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		double aux = 0.0;
		for(int j = 0; j < nc; j++) {
			aux += (A[i][j] * v[j]);
		}
		x[i] = aux;
	}

	return x;
}

double *resta_vect(double *v1, double *v2, double *x, int n) {
	for(int i = 0; i < n; i++) {
		x[i] = v2[i] - v1[i];
	}

	return x;
}

double norm(double *x, int sz) {
	double n = 0.0;
	for(int i = 0; i < sz; i++)
		n += pow(x[i], 2);

	return sqrt(n);
}

double get_error(double **A, double *x, double *b, int nr, int nc) {
	double *aux = create_vector(nc, double);
	aux = mul_mat_vector(A, x, aux, nr, nc);
	aux = resta_vect(aux, b, aux, nc);
	double n = norm(aux, nc);
	free_vector(aux);

	return n;
}

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

//Encuentra la solución de una matríz diagonal (en forma de vector)
double *resuelve_m_tinferior(double **A, double *b, int nr, int nc, double tol) {
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

//Encuentra la solución de una matríz diagonal (en forma de vector)
double *resuelve_m_tsuperior(double **A, double *b, int nr, int nc, double tol) {
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