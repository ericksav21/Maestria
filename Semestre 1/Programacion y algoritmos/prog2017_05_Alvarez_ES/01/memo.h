#ifndef MEMO_H
#define MEMO_H

#include <stdio.h>
#include <stdlib.h>

/*  --------------- Arr2D Section ---------------  */

char** create_arr2d_by_chunks_c(int nr, int nc);

int** create_arr2d_by_chunks_i(int nr, int nc);

double** create_arr2d_by_chunks_d(int nr, int nc);

double** get_part_of_matrix(double **mat, int begin, int end,int nc);

void** create_arr2d_by_chunks(int nr, int nc, size_t type_size);

void** create_arr2d_no_chunked(int nr, int nc, size_t type_size);

void** create_arr2d(int nr, int nc, size_t type_size, int *type_of_mat);

void delete_arr2d(void **mat, int nr, int is_chunked);

void delete_arr2d_i(int **mat, int nr);

void delete_arr2d_c(char **mat, int nr);

void delete_arr2d_d(double **mat, int nr);

/*  --------------- Arr1D Section ---------------  */

void* create_arr1d(int n, size_t type_size);

void delete_arr1d(void *arr);

#endif