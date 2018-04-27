#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double backtracking(double *x, double *gradient, double last_alpha, int n);

void BFGS(double *x0, double (*func_ptr)(double*, int), void (*grad_ptr)(double*, double*, int), int n, double **H, int iter_max, double tol);

#endif