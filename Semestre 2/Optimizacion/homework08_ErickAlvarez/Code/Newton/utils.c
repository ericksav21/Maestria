#include "utils.h"

double get_EPS() {
	double Eps = 1.0;

	while (1.0 + Eps / 2.0 != 1.0)
		Eps /= 2.0;

	return Eps;
}

/*----- Functions -----*/
void init_x0(double *res, int v1) {
	if(v1 == 1) {
		res[0] = res[1] = res[2] = 0.0;
	}
	else if(v1 == 2) {
		res[0] = res[1] = 1.1;
		res[2] = -1.1;
	}
	else if(v1 == 3) {
		res[0] = res[1] = -10.0;
		res[2] = 10.0;
	}
	else {
		res[0] = res[2] = 3.0;
		res[1] = -3.0;
	}
}

void F(double *x, double *res) {
	res[0] = 3.0 * x[0] - cos(x[1] * x[2]) - 0.5;
	res[1] = x[0] * x[0] - 81.0 * pow(x[1] + 0.1, 2) + sin(x[2]) + 1.06;
	res[2] = exp(-x[0] * x[1]) + 20.0 * x[2] + (10.0 * M_PI - 3.0) / 3.0;
}

void J(double *x, double **res) {
	double aux1 = -x[0] * x[1];
	double aux2 = x[1] * x[2];
	
	res[0][0] = 3.0;
	res[0][1] = x[2] * sin(aux2);
	res[0][2] = x[1] * sin(aux2);
	res[1][0] = 2.0 * x[0];
	res[1][1] = -162.0 * (x[1] + 0.1);
	res[1][2] = cos(x[2]);
	res[2][0] = -x[1] * exp(aux1);
	res[2][1] = -x[0] * exp(aux1);
	res[2][2] = 20.0;
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

/*----- Jacobi -----*/
void GAG(double ***A, double ***V, int n, int i, int j, double c, double s) {
	double n1, n2;

	//A*G
	for(int k = 0; k < n; k++) {
		n1 = (*A)[k][i] * c + (*A)[k][j] * s;
		n2 = -(*A)[k][i] * s + (*A)[k][j] * c;

		(*A)[k][i] = n1;
		(*A)[k][j] = n2;

		n1 = (*V)[k][i] * c + (*V)[k][j] * s;
		n2 = -(*V)[k][i] * s + (*V)[k][j] * c;

		(*V)[k][i] = n1;
		(*V)[k][j] = n2;
	}

	//Gt*A
	for(int k = 0; k < n; k++) {
		n1 = (*A)[i][k] * c + (*A)[j][k] * s;
		n2 = -(*A)[i][k] * s + (*A)[j][k] * c;

		(*A)[i][k] = n1;
		(*A)[j][k] = n2;
	}
}

/* 
	Realiza el método de Jacobi a la matriz A, los parámetros son los siguientes:
	-A: Puntero a una matriz cuadrada y simétrica, (Esta matriz se convierte en la de eigenvalores).
	-V: Puntero a una matriz que resultará ser la matriz de eigenvectores resultantes.
	-nr, nc: Las dimensiones de la matriz.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
	-xk: Un vector de tamaño nc, el cual se convertirá en el eigenvector (Este vector inicialmente puede estar normalizado).
	-M: El número de iteraciones máximo que realizará el algoritmo.
	-k_res: El número de iteraciones que realizó el algoritmo.
*/
double Jacobi(double ***A, double ***V, int nr, int nc, double tol, int M, int *k_res) {
	*V = get_I(nr);
	double mmax;
	int i;
	for(i = 0; i < M; i++) {
		//Encontrar el mayor elemento en valor absoluto
		int imax, jmax;
		mmax = -1.0;
		for(int col = 0; col < nc - 1; col++) {
			for(int row = col + 1; row < nr; row++) {
				double aux = fabs((*A)[row][col]);
				if(aux > mmax) {
					mmax = aux;
					imax = row;
					jmax = col;
				}
			}
		}

		if(fabs(mmax) < tol) {
			break;
		}

		double tetha = 0.5 * atan2(2 * (*A)[imax][jmax], ((*A)[imax][imax] - (*A)[jmax][jmax]));
		double c = cos(tetha);
		double s = sin(tetha);

		GAG(A, V, nr, imax, jmax, c, s);
	}

	*k_res = i;
	return mmax;
}