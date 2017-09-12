#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdlib.h>
#include <float.h>
#include "memo.h"
#include "separador.h"

int f_separate(char *first_books_name, int n_files_fb, int start_in);

int** generate_trying_set(int **set, int no_blocks);

int* generate_bin_vector(int n);

double distance(double *v1, double *v2, int *bin_vector, int no_words);

void clasify(int **trying_set1, int **trying_set2, int *bin_vector, double **m1, double **m2, int m1_sz, int m2_sz, int no_words);

#endif