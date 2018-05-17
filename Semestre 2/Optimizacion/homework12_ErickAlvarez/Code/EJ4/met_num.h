#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double Fletcher_Reeves(double *lst_gradient, double *gradient, int n);

double backtracking(double *x, double *g, double *p, double alpha_0, double mu, double dx, int n, int m);

double* conjugate_gradient(double *init, int n, int m, int iter, double tol_g, double mu, double dx);

void QP(double *init, int n, int m, double tao_k, double tao, double mu, double dx);

#endif