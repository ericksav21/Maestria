#ifndef SPLINE_H
#define SPLINE_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol);

double* generate_M(double *x, double *y, int n, double tol);

double evaluate_pol(double *x, double *y, double *M, double xm, int n);

void generate(double *x, double *y, double *M, int m, int n, char *files_name);

#endif