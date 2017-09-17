#ifndef MATRIZ_DIAGONAL_H
#define MATRIZ_DIAGONAL_H

#include <stdio.h>
#include <math.h>
#include "memo.h"

double get_error(double *d, double *x, double *b, int n);

double *resuelve_m_diagonal(double *d, double *b, int n, double tol);

double get_EPS();

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

#endif