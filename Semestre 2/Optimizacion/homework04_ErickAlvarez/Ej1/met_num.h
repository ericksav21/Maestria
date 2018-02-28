#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double f(double *x);

void get_gradient(double *g, double *x);

void get_Hessian(double **H, double *x);

double compute_alpha_1(double *gradient, double **Hessian, int n, double tol);

double compute_alpha_2();

double *gradient_descent(double *init, int n, int iter, int alpha_type);

#endif
