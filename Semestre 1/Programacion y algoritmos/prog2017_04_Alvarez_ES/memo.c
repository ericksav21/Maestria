#include "memo.h"

 /*  --------------- Arr2D Section ---------------  */

char** create_arr2d_by_chunks_c(int nr, int nc) {
	char **mat;
	mat = (char **)malloc(nr * sizeof(char *));
	for(int i = 0; i < nr; i++) {
		mat[i] = (char *)malloc(nc * sizeof(char));
	}

	return mat;
}

int** create_arr2d_by_chunks_i(int nr, int nc) {
	int **mat;
	mat = (int **)malloc(nr * sizeof(int *));
	for(int i = 0; i < nr; i++) {
		mat[i] = (int *)malloc(nc * sizeof(int));
	}

	return mat;
}

double** create_arr2d_by_chunks_d(int nr, int nc) {
	double **mat;
	mat = (double **)malloc(nr * sizeof(double *));
	for(int i = 0; i < nr; i++) {
		mat[i] = (double *)malloc(nc * sizeof(double));
	}

	return mat;
}

//Toma como entrada una matriz y devuelve una submatriz partida
//por las filas de la original, incluyendo los límites
//Nota: Begin y end están indexados a cero
double** get_part_of_matrix(double **mat, int begin, int end, int nc) {
	int nr = end - begin + 1;
	double **res;
	res = create_arr2d_by_chunks_d(nr, nc);
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			res[i][j] = mat[begin + i][j];
		}
	}

	return res;
}

void** create_arr2d_by_chunks(int nr, int nc, size_t type_size) {
	void **mat;
	mat = malloc(nr * sizeof(void *));
	for(int i = 0; i < nr; i++) {
		mat[i] = (void *)malloc(nc * type_size);
	}

	return mat;
}

void** create_arr2d_no_chunked(int nr, int nc, size_t type_size) {
	void **mat;
	mat = malloc(nr * sizeof(void *));
	mat[0] = (void *)malloc(nr * nc * type_size);
	if(mat[0] == NULL)
		return NULL;
	for(int i = 1; i < nr; i++) {
		mat[i] = mat[i - 1] + nc * type_size;
	}

	return mat;
}

//1: chunked, 0: no chunked
void** create_arr2d(int nr, int nc, size_t type_size, int *type_of_mat) {
	int MB = 10 * 1000 * 1000;
	int sz = nr * nc * type_size;
	void **mat = NULL;
	if(sz < MB) {
		mat = create_arr2d_no_chunked(nr, nc, type_size);
		if(mat == NULL) {
			*type_of_mat = 1;
			return create_arr2d_by_chunks(nr, nc, type_size);
		}
		*type_of_mat = 0;
		return mat;
	}
	else {
		*type_of_mat = 1;
		return create_arr2d_by_chunks(nr, nc, type_size);
	}
}

void delete_arr2d(void **mat, int nr, int is_chunked) {
	if(mat != NULL) {
		if(is_chunked) {
			for(int i = 0; i < nr; i++) {
				free(mat[i]);
			}
			free(mat);
		}
		else {
			free(mat[0]);
			free(mat);
		}
	}
}

void delete_arr2d_i(int **mat, int nr) {
	if(mat != NULL) {
		for(int i = 0; i < nr; i++) {
			free(mat[i]);
		}
		free(mat);
	}
}

void delete_arr2d_c(char **mat, int nr) {
	if(mat != NULL) {
		for(int i = 0; i < nr; i++) {
			free(mat[i]);
		}
		free(mat);
	}
}

void delete_arr2d_d(double **mat, int nr) {
	if(mat != NULL) {
		for(int i = 0; i < nr; i++) {
			free(mat[i]);
		}
		free(mat);
	}
}

/*  --------------- Arr1D Section ---------------  */

void* create_arr1d(int n, size_t type_size) {
	void *arr;
	arr = malloc(n * type_size);
	return arr;
}

void delete_arr1d(void *arr) {
	if(arr != NULL) {
		free(arr);
	}
}