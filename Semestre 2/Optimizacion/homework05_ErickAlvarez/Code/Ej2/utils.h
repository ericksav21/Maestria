#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

void read_files(char *fn_x, char *fn_y, double **mat_x, double *vec_y, int n1, int n2, int *m);

double *read_init_point(char *files_name, int *n);

#endif