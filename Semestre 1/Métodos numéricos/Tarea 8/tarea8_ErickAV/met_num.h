#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *conjugate_gradient(double **A, double *x0, double *b, int n, int *iter, double *err, double tol);

#endif