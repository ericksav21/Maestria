#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double backtracking(double *x, double *g, double *p, double last_alpha, int n);

void update_H(double **H, double *s, double *y, int n);

void BFGS(double *x0, double (*func_ptr)(double*, int), void (*grad_ptr)(double*, double*, int), double **H, int n, int iter_max, double tol);

#endif