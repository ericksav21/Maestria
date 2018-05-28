#include "met_num.h"

double **PCA(double **X, int nr, int nc, int noEig) {
	double **X_c = create_matrix(nr, nc, double);
	double **XT = create_matrix(nc, nr, double);
	double **C = create_matrix(nc, nc, double);
	//Obtener la media
	double m[2];
	m[0] = m[1] = 0.0;
	for(int j = 0; j < nc; j++) {
		for(int i = 0; i < nr; i++) {
			m[j] += X[i][j];
		}
		m[j] /= (double)nr;
	}
	for(int j = 0; j < nc; j++) {
		for(int i = 0; i < nr; i++) {
			X_c[i][j] = (X[i][j] - m[j]);
		}
	}
	XT = transpose_matrix(X_c, XT, nr, nc);
	C = mul_mat_mat(XT, X_c, C, nc, nr);
	for(int i = 0; i < nc; i++) {
		for(int j = 0; j < nc; j++) {
			C[i][j] /= (double)nr;
		}
	}
	//SVD
	gsl_matrix *mat, *mat2;
	mat = gsl_matrix_alloc(nc, nc);
	mat2 = gsl_matrix_alloc(nc, nc);
	gsl_vector *vec1 = gsl_vector_alloc(nc);
	gsl_vector *vec2 = gsl_vector_alloc(nc);

	for(int i = 0; i < nc; i++) {
		for(int j = 0; j < nc; j++) {
			gsl_matrix_set(mat, i, j, C[i][j]);
		}
	}
	gsl_linalg_SV_decomp(mat, mat2, vec1, vec2);
	double **S = gslmat2array2d(mat);

	free_matrix(X_c);
	free_matrix(XT);
	free_matrix(C);
    gsl_matrix_free(mat);
    gsl_matrix_free(mat2);
    gsl_vector_free(vec1);
    gsl_vector_free(vec2);

	return S;
}

void compResiduals(double **X_c, double **U, double *residuals, int nr, int nc) {
	double **X_proj = create_matrix(nr, nc, double);
	double **XT = create_matrix(nc, nr, double);
	double **X_projT = create_matrix(nc, nr, double);
	double **M_aux1 = create_matrix(nr, nr, double);
	double **M_aux2 = create_matrix(nr, nr, double);
	double **M_aux3 = create_matrix(nr, nr, double);

	X_proj = mul_mat_mat(X_c, U, X_proj, nr, nc);
	XT = transpose_matrix(X_c, XT, nr, nc);
	X_projT = transpose_matrix(X_proj, X_projT, nr, nc);

	M_aux1 = mul_mat_mat(X_c, XT, M_aux1, nr, nc);
	M_aux2 = mul_mat_mat(X_proj, X_projT, M_aux2, nr, nc);
	M_aux3 = substract_mat(M_aux1, M_aux2, M_aux3, nr, nr);

	for(int i = 0; i < nr; i++) {
		residuals[i] = M_aux3[i][i];
	}

	/*free_matrix(X_proj);
	free_matrix(XT);
	free_matrix(X_projT);
	free_matrix(M_aux1);
	free_matrix(M_aux2);
	free_matrix(M_aux3);*/
}

double **PCA_g(double **X, double *m, int nr, int nc, int noEig, double p) {
	double **X_c = create_matrix(nr, nc, double);
	double **XT = create_matrix(nc, nr, double);
	double **C = create_matrix(nc, nc, double);

	int maxIter = 100;
	double threDiff = 1e-5;
	double ratio = 0.01;
	double delta = 1e-10;

	for(int j = 0; j < nc; j++) {
		for(int i = 0; i < nr; i++) {
			X_c[i][j] = (X[i][j] - m[j]);
		}
	}

	double **W_PCA = PCA(X, nr, nc, noEig);
	double *residuals = create_vector(nr, double);
	compResiduals(X_c, W_PCA, residuals, nr, nc);
	print_vector(residuals, nr);
	double objF = 0.0;
	for(int i = 0; i < nr; i++) {
		objF += pow(residuals[i] + delta, p);
		printf("%g\n", pow(residuals[i] + delta, p));
	}
	printf("Obj: %g\n", objF);

	free_matrix(X_c);
	free_matrix(XT);
	free_matrix(C);
	free_matrix(W_PCA);
	free_vector(residuals);
}