#include "memo.h"

 /*  --------------- Arr2D Section ---------------  */

double** create_matrix_d(int nr, int nc, double val) {
	double **mat = new double*[nr];
	for(int i = 0; i < nr; i++) {
		mat[i] = new double[nc];
		for(int j = 0; j < nc; j++) {
			mat[i][j] = val;
		}
	}

	return mat;
}

int** create_matrix_i(int nr, int nc, int val) {
	int **mat = new int*[nr];
	for(int i = 0; i < nr; i++) {
		mat[i] = new int[nc];
		for(int j = 0; j < nc; j++) {
			mat[i][j] = val;
		}
	}

	return mat;
}

void delete_matrix_d(double **mat, int nr) {
	if(mat != NULL) {
		for(int i = 0; i < nr; i++) {
			delete [] mat[i];
		}
		delete [] mat;
	}
}

void delete_matrix_i(int **mat, int nr) {
	if(mat != NULL) {
		for(int i = 0; i < nr; i++) {
			delete [] mat[i];
		}
		delete [] mat;
	}
}

/*  --------------- Arr1D Section ---------------  */

double* create_vector_d(int n, double val) {
	double *arr = new double[n];
	for(int i = 0; i < n; i++) {
		arr[i] = val;
	}

	return arr;
}

int* create_vector_i(int n, int val) {
	int *arr = new int[n];
	for(int i = 0; i < n; i++) {
		arr[i] = val;
	}

	return arr;
}

void delete_vector_d(double *arr) {
	if(arr != NULL) {
		delete [] arr;
	}
}

void delete_vector_i(int *arr) {
	if(arr != NULL) {
		delete [] arr;
	}
}