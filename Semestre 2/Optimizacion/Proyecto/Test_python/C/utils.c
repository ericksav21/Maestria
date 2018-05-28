#include "utils.h"

double **read_matrix(char *files_name, int *nr, int *nc) {
	FILE *f = fopen(files_name, "r");
	int a, b;
	fscanf(f, "%d %d", &a, &b);
	(*nr) = a;
	(*nc) = b;
	double **mat = create_matrix(a, b, double);
	for(int i = 0; i < a; i++) {
		for(int j = 0; j < b; j++) {
			double aux;
			fscanf(f, "%lf", &aux);
			mat[i][j] = aux;
		}
	}

	fclose(f);

	return mat;
}

double **gslmat2array2d(gsl_matrix *mat) {
    double **array2d;

    array2d = create_matrix(mat->size1, mat->size2, double);
    for(int i = 0; i < mat->size1; i++) {
    	for(int j = 0; j < mat->size2; j++) {
    		array2d[i][j] = gsl_matrix_get(mat, i, j);
    	}
    }

    return array2d;
}