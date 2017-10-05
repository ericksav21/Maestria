#include "funciones_matriz.h"

double** get_I(int n) {
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

double** transpose_matrix(double **A, double **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nr; j++) {
			X[j][i] = A[i][j];
		}
	}

	return X;
}

double* mul_mat_vector(double **A, double *v, double *x, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		double aux = 0.0;
		for(int j = 0; j < nc; j++) {
			aux += (A[i][j] * v[j]);
		}
		x[i] = aux;
	}

	return x;
}

//Se asume que las matrices son cuadradas
double** mul_mat_mat(double **A, double **B, double **X, int n) {
	for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double aux = 0;
            for(int k = 0; k < n; k++) {
                aux += (A[i][k] * B[k][j]);
            }
            X[i][j] = aux;
        }
    }

    return X;
}

double** substract_mat(double **A, double **B, double **X, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			X[i][j] = A[i][j] - B[i][j];
		}
	}

	return X;
}

double* substract_vect(double *v1, double *v2, double *x, int n) {
	for(int i = 0; i < n; i++) {
		x[i] = v2[i] - v1[i];
	}

	return x;
}

double* scale_vect(double *x, double *v, int sz, double c) {
	for(int i = 0; i < sz; i++) {
		v[i] = c * x[i];
	}

	return v;
}

double** scale_mat(double **A, double **X, int nr, int nc, double c) {
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

int sign(double n) {
	if(n == 0)
		return 0;
	if(n < 0)
		return -1;
	return 1;
}

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double** Givens(int n, int i, int j, double s, double c) {
	double **G = get_I(n);
	G[i][i] = G[j][j] = c;
	G[i][j] = s;
	G[j][i] = -s;

	return G;
}

double Jacobi(double ***A, double ***V, int nr, int nc, double tol, int M, int *k_res) {
	*V = get_I(nr);
	double mmax;
	int i;
	for(i = 0; i < M; i++) {
		//Encontrar el mayor elemento en valor absoluto
		int imax, jmax;
		mmax = -1.0;
		for(int x = 0; x < nr; x++) {
			for(int y = 0; y < nc; y++) {
				if(x == y)
					continue;
				double aux = fabs((*A)[x][y]);
				if(aux > mmax) {
					mmax = aux;
					imax = x;
					jmax = y;
				}
			}
		}

		if(fabs(mmax) < tol) {
			break;
		}

		double delta = ((*A)[jmax][jmax] - (*A)[imax][imax]) / (2.0 * mmax);
		double t = sign(delta) / (fabs(delta) + sqrt(1.0 + delta * delta));
		double c = 1.0 / sqrt(1.0 + t * t);
		double s = c * t;

		//Calcular la rotación de Givens
		double **G = Givens(nr, imax, jmax, s, c);
		double **Gt = create_matrix(nr, nc, double);
		double **AUX1 = create_matrix(nr, nc, double);
		double **AUX2 = create_matrix(nr, nc, double);
		double **AUX3 = create_matrix(nr, nc, double);

		Gt = transpose_matrix(G, Gt, nr, nc);
		AUX1 = mul_mat_mat(Gt, *A, AUX1, nr);
		AUX2 = mul_mat_mat(AUX1, G, AUX2, nr);
		*A = copy_matrix(AUX2, *A, nr, nc);

		AUX3 = mul_mat_mat(*V, G, AUX3, nr);
		*V = copy_matrix(AUX3, *V, nr, nc);

		/*print_matrix(*V, nr, nc);
		printf("\n");*/

		free_matrix(G);
		free_matrix(Gt);
		free_matrix(AUX1);
		free_matrix(AUX2);
		free_matrix(AUX3);
	}

	*k_res = i;
	return mmax;
}

void get_eigenpairs(double **A, int nr, int nc, int M) {
	int k_res;
	double **V = NULL;
	double tol = pow(get_EPS(), 1.0 / 2.0);
	double e = Jacobi(&A, &V, nr, nc, tol, M, &k_res);
	printf("Algoritmo terminado, número de iteraciones %d.\n", k_res);
	printf("A:\n");
	print_matrix(A, nr, nc);
	printf("\n\nV:\n");
	print_matrix(V, nr, nc);
	printf("\nE: %g\n", e);

	free_matrix(V);
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

double** copy_matrix(double **A, double **B, int nr, int nc) {
	for(int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			B[i][j] = A[i][j];
		}
	}

	return B;
}