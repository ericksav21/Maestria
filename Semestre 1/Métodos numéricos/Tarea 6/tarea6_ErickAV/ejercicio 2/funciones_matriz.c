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

double frobenius_norm(double **A, int nr, int nc) {
	double res = 0.0;
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			res += pow(A[i][j], 2);
		}
	}

	return sqrt(res);
}

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
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

void get_eigenpairs(double **A, int nr, int nc, int M) {
	int k_res;
	double **V = NULL;
	double **Aorg = create_matrix(nr, nc, double);
	double tol = pow(get_EPS(), 1.0 / 2.0);

	Aorg = copy_matrix(A, Aorg, nr, nc);
	double e = Jacobi(&A, &V, nr, nc, tol, M, &k_res);
	printf("Algoritmo terminado, número de iteraciones %d.\n", k_res);
	printf("A:\n");
	print_matrix(A, nr, nc);
	printf("\n\nV:\n");
	print_matrix(V, nr, nc);
	printf("\nE: %g\n", e);

	double **AUX1 = create_matrix(nr, nc, double);
	double **AUX2 = create_matrix(nr, nc, double);
	double **AUX3 = create_matrix(nr, nc, double);

	AUX1 = mul_mat_mat(Aorg, V, AUX1, nr);
	AUX2 = mul_mat_mat(V, A, AUX2, nr);
	AUX3 = substract_mat(AUX1, AUX2, AUX3, nr, nc);

	printf("\n");
	printf("Error: %g\n", frobenius_norm(AUX3, nr, nc));

	free_matrix(AUX1);
	free_matrix(AUX2);
	free_matrix(AUX3);
	free_matrix(Aorg);
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
