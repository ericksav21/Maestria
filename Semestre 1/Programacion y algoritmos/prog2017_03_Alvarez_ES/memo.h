#ifndef MEMO_H
#define MEMO_H

#include <stdio.h>
#include <stdlib.h>

/*  --------------- Arr2D Section ---------------  */

void** create_arr2d_by_chunks(int nr, int nc, size_t type_size);

void** create_arr2d_no_chunked(int nr, int nc, size_t type_size);

void** create_arr2d(int nr, int nc, size_t type_size, int *type_of_mat);

void delete_arr2d(void **mat, int nr, int is_chunked);

/*  --------------- Arr1D Section ---------------  */

void* create_arr1d(int n, size_t type_size);

void delete_arr1d(void *arr);

#endif