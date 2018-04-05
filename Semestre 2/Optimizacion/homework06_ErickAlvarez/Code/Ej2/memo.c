#include "memo.h"

void *create_matrix_1d(int sz, size_t type_size) {
	void *vector;
	vector = (void *)malloc(sz * type_size);
	return vector;
}

void **create_matrix_2d(int nr, int nc, size_t type_size) {
	void **mat;
	mat = (void **)malloc(nr * sizeof(void *));
	mat[0] = (void *)malloc(nr * nc * type_size);
	for(int i = 1; i < nr; i++)
		mat[i] = mat[i - 1] + nc * type_size;

	return mat;
}

void ***create_matrix_3d(int nm, int nr, int nc, size_t type_size) {
	void ***matrix = (void ***)malloc(nm * sizeof(void **));

	for(int i = 0; i < nm; i++) {
		matrix[i] = (void **)malloc(nr * sizeof(void *));
		matrix[i][0] = (void *)malloc(nr * nc * type_size);
		for(int j = 1; j < nr; j++) {
			matrix[i][j] = matrix[i][j - 1] + nc * type_size;
		}
	}

	return matrix;
}

void free_matrix_1d(void *v) {
	free(v);
}

void free_matrix_2d(void **m) {
	free(m[0]);
	free(m);
}

void free_matrix_3d(void ***m, int nm) {
	for(int i = 0; i < nm; i++) {
		free(m[i][0]);
		free(m[i]);
	}
	free(m);
}

double *copy_matrix_1d_d(double *src, double *dest, int sz) {
	for(int i = 0; i < sz; i++) {
		dest[i] = src[i];
	}

	return dest;
}