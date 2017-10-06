#include "funciones_matriz.h"

double **get_I(int n) {
	double **I = create_matrix(n, n, double);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j)
				I[i][j] = 1.0;
			else
				I[i][j] = 0.0;
		}
	}

	return I;
}

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

double **substract_mat(double **A, double **B, double **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] - B[i][j];
		}
	}

	return X;
}

double *substract_vect(double *v1, double *v2, double *x, int n) {
	for(int i = 0; i < n; i++) {
		x[i] = v2[i] - v1[i];
	}

	return x;
}

double *scale_vect(double *x, double *v, int sz, double c) {
	for(int i = 0; i < sz; i++) {
		v[i] = c * x[i];
	}

	return v;
}

double **scale_mat(double **A, double **X, int nr, int nc, double c) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] * c;
		}
	}

	return X;
}

double inner_product(double *x, double *v, int sz) {
	double res = 0.0;
	for(int i = 0; i < sz; i++) {
		res += x[i] * v[i];
	}

	return res;
}

double norm(double *x, int sz) {
	double n = 0.0;
	for(int i = 0; i < sz; i++) {
		n += pow(x[i], 2);
	}

	return sqrt(n);
}

double* normalize(double *x, int sz) {
	double n = norm(x, sz);
	for(int i = 0; i < sz; i++) {
		x[i] /= n;
	}

	return x;
}

double norm_inf(double **A, int nr, int nc) {
	double *x = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		double aux = 0.0;
		for(int j = 0; j < nc; j++) {
			aux += fabs(A[i][j]);
		}
		x[i] = aux;
	}
	double res = x[0];
	for(int i = 1; i < nr; i++) {
		res = max(res, x[i]);
	}

	free_vector(x);
	return res;
}

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
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
		double nn = norm(x, nc);

		for(int i = 0; i < nc; i++) {
			xp[i] = (x[i] / nn);
			w[i] = ((*xk)[i] / nn);
		}

		double rho = inner_product(xp, w, nc);
		*mu = rho + delta;
		ws = scale_vect(xp, ws, nc, rho);
		r = substract_vect(w, ws, r, nc);
		e = norm(r, nc);

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

void get_eigenpairs(double **A, int nr, int nc, int n) {
	double d = norm_inf(A, nr, nc);
	printf("Norma inf: %lf\n\n", d);
	double mu_0 = -10.0 * d;
	double tol = pow(get_EPS(), 1.0 / 2.0);
	int iter = 1000, k_res;
	double *x = create_vector(nc, double);

	for(int k = 0; k <= 2 * n; k++) {
		double mu = 0.0;
		double dd = d / (double)n;
		double delta = -d + k * dd;
		for(int i = 0; i < nc; i++) x[i] = 1.0;
		x = normalize(x, nc);

		double e = inverse_power(A, nr, nc, &x, &mu, delta, iter, &k_res, tol);

		if(e < tol && fabs(mu_0 - mu) > 1.0e-4) {
			printf("Eigenpar encontrado con %d iteraciones y con un error de %g:\nmu: %g\nx: ", k_res, e, mu);
			print_vector(x, nc);
			printf("\n");
		}

		mu_0 = mu;
	}

	free_vector(x);
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