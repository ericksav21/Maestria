#ifndef MATRIZ_DIAGONAL_H
#define MATRIZ_DIAGONAL_H

#include <math.h>
#include "memo.h"

double get_error(double *d, double *x, double *b, int n);

double *resuelve_m_diagonal(double *d, double *b, int n, double tol);

#endif