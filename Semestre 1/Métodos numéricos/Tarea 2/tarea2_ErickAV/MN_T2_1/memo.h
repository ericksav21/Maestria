#ifndef MEMO_H
#define MEMO_H

#include <stdlib.h>

void *create_arr_1d(int n, int type_size);

void delete_arr_1d(void *arr);

void **create_arr_2d(int nr, int nc, int type_size);

void delete_arr_2d(void **mat, int nr);

#endif
