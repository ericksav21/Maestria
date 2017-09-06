#include "memo.h"

 /*  --------------- Arr2D Section ---------------  */

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