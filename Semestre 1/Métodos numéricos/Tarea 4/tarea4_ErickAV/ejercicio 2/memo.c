#include "memo.h"

void genera_tabla_txt(double *xi, double *phi_r, int n) {
	FILE *out;
	out = fopen("Resultados.txt", "w");
	for(int i = 1; i < n; i++) {
		fprintf(out, "%lf %lf %lf\n", xi[i], phi(xi[i]), phi_r[i - 1]);
	}

	fclose(out);
}

void *create_matrix_1d(int sz, size_t type_size) {
	void *vector;
	vector = (void *)malloc(sz * type_size);
	return vector;
}

double *copy_matrix_1d_d(double *src, double *dest, int sz) {
	for(int i = 0; i < sz; i++) {
		dest[i] = src[i];
	}

	return dest;
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