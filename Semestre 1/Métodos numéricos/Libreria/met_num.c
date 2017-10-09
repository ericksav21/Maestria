#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

/*---------- EQUATION SYSTEM SOLVERS ----------*/

double *solve_mdiagonal(double *d, double *b, int n, double tol) {
	double *x = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		if(fabs(d[i]) < tol) {
			free_vector(x);
			return NULL;
		}
		x[i] = b[i] / d[i];
	}

	return x;
}

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

int cholesky(double **A, double ***L, double ***Lt, int n, double tol) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (i + 1); j++) {
			double aux = 0.0;
			for(int k = 0; k < j; k++) {
				aux += (*L)[i][k] * (*L)[j][k];
			}
			if(i == j) {
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

/*---------- END EQUATION SYSTEM SOLVERS ----------*/

/*---------- EIGENVALUES AND EIGENVECTORS ----------*/

/* 
	Realiza el método de la potencia a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada no necesariamente simétrica.
	-v_ant: Un vector vacío.
	-nr, nc: Las dimensiones de la matriz.
	-iter: El número de iteraciones máximo que realizará el algoritmo.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
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
		v_ant = normalize(v_ant, v_act, nc);
		v_act = mul_mat_vector(A, v_ant, v_act, nr, nc);

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

/* 
	Realiza el método de la potencia inversa a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada no necesariamente simétrica.
	-nr, nc: Las dimensiones de la matriz.
	-xk: Un vector de tamaño nc, el cual se convertirá en el eigenvector (Este vector inicialmente puede estar normalizado).
	-mu: El eigenvalor resultante.
	-delta: El valor delta al cual tenderá el eigenvalor, si delta vale cero entonces el método retornará el eigenvalor más pequeño.
	-iter: El número de iteraciones máximo que realizará el algoritmo.
	-k_res: El número de iteraciones que realizó el algoritmo.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
double inverse_power(double **A, int nr, int nc, double **xk, double *mu, double delta, int iter, int *k_res, double tol) {
	double **L = create_matrix(nr, nc, double);
	double **U = create_matrix(nr, nc, double);
	double **I = get_I(nr);
	double **AUX = create_matrix(nr, nc, double);
	I = scale_mat(I, I, nr, nc, delta);
	AUX = substract_mat(A, I, AUX, nr, nc);

	int t = 0;

	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			L[i][j] = U[i][j] = 0.0;
		}
	}

	int res = factorize_LU(AUX, &L, &U, nr, tol);
	if(res == 0) {
		printf("No se pudo resolver el sistema.\n");
		free_matrix(L);
		free_matrix(U);
		return -1;
	}

	double *r = create_vector(nc, double);
	double e = 0.0;

	while(1) {
		double *y = solve_mlower(L, *xk, nr, nc, tol);
		double *x = solve_mupper(U, y, nr, nc, tol);
		double *xp = create_vector(nc, double);
		double *w = create_vector(nc, double);
		double *ws = create_vector(nc, double);
		double nn = norm_p(x, nc, 2);

		for(int i = 0; i < nc; i++) {
			xp[i] = (x[i] / nn);
			w[i] = ((*xk)[i] / nn);
		}

		double rho = inner_product(xp, w, nc);
		*mu = rho + delta;
		ws = scale_vect(xp, ws, nc, rho);
		r = substract_vect(w, ws, r, nc);
		e = norm_p(r, nc, 2);

		free_vector(y);
		free_vector(x);
		free_vector(w);
		free_vector(ws);

		if(e < tol || t == iter) {
			free_vector(xp);
			break;
		}
		t++;
		for(int i = 0; i < nc; i++) (*xk)[i] = xp[i];
		free_vector(xp);
	}

	free_vector(r);
	free_matrix(AUX);
	free_matrix(I);
	free_matrix(L);
	free_matrix(U);

	*k_res = t;
	return e;
}

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

/*---------- END EIGENVALUES AND EIGENVECTORS ----------*/