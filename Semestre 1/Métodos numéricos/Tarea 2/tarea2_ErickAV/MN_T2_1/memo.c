#include "memo.h"

void *create_arr_1d(int n, int type_size) {
    void *arr;
    arr = (void *)malloc(n * type_size);

    return arr;
}

void delete_arr_1d(void *arr) {
    free(arr);
}

void **create_arr_2d(int nr, int nc, int type_size) {
    void **mat;
    mat = malloc(nr * sizeof(void *));
    mat[0] = (void *)malloc(nr * nc * type_size);
    for(int i = 1; i < nr; i++) {
        mat[i] = mat[i - 1] + nc * type_size;
    }

    return mat;
}

void delete_arr_2d(void **mat, int nr) {
    free(mat[0]);
    free(mat);
}
