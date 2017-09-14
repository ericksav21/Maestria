#ifndef MATRIZ_T_SUPERIOR_H
#define MATRIZ_T_SUPERIOR_H

#include <stdio.h>
#include <math.h>
#include "memo.h"

double *mul_mat_vector(double **A, double *v, double *x, int nr, int nc);

double *resta_vect(double *v1, double *v2, double *x, int n);

double norm(double *x, int sz);

double *resuelve_m_tsuperior(double **A, double *b, int nr, int nc, double tol);

double get_error(double **A, double *x, double *b, int nr, int nc);

#endif