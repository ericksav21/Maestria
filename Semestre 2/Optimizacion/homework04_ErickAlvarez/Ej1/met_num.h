#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double get_EPS();

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n);

double compute_alpha_1(double *gradient, double **Hessian, int n, double tol);

double compute_alpha_1_3d(double *gradient, MAT3D *Hessian, int n, double tol);

double compute_alpha_2();

double compute_alpha_3(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol);

double *gradient_descent(double *init, int n, int iter, int alpha_type);

double *gradient_descent_2(double *init, int n, int iter, int alpha_type);

#endif
