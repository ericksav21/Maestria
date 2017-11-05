#ifndef MEMO_H
#define MEMO_H

#include <cstddef>

 /*  --------------- Arr2D Section ---------------  */

double** create_matrix_d(int nr, int nc, double val);

int** create_matrix_i(int nr, int nc, int val);

void delete_matrix_d(double **mat, int nr);

void delete_matrix_i(int **mat, int nr);

/*  --------------- Arr1D Section ---------------  */

double* create_vector_d(int n, double val);

int* create_vector_i(int n, int val);

void delete_vector_d(double *arr);

void delete_vector_i(int *arr);

#endif