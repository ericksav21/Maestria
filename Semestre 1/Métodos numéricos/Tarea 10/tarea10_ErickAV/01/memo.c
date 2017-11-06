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

void free_matrix_1d(void *v) {
	free(v);
}

void free_matrix_2d(void **m) {
	free(m[0]);
	free(m);
}

double *copy_matrix_1d_d(double *src, double *dest, int sz) {
	for(int i = 0; i < sz; i++) {
		dest[i] = src[i];
	}

	return dest;
}

MAT3D* create_mat_3d(int n) {
	MAT3D *res = (MAT3D *)malloc(sizeof(MAT3D));
	res->a = create_vector(n, double);
	res->b = create_vector(n, double);
	res->c = create_vector(n, double);
	res->n = n;

	for(int i = 0; i < n; i++) {
		res->a[i] = res->b[i] = res->c[i] = 0.0;
	}

	return res;
}

MAT3D* free_mat_3d(MAT3D *src) {
	free_vector(src->a);
	free_vector(src->b);
	free_vector(src->c);
	src->a = NULL;
	src->b = NULL;
	src->c = NULL;
	src->n = 0;

	return src;
}