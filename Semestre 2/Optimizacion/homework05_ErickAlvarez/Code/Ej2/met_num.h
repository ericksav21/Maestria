#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double get_EPS();

double get_f(double **x, double *y, double *beta, int m, int n);

void get_gradient(double *g, double **x, double *y, double *beta, int m, int n);

double step_hess(double *gradient, double **Hessian, int n, double tol);

double step_aprox(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol);

double backtracking(double **x, double *y, double *beta, double *gradient, double last_alpha, int m, int n);

//double quadratic_interp(int ex_no, double *x, double *y, double *gradient, double lambda, double last_alpha, int n);

//double cubic_interp(int ex_no, double *x, double *y, double *gradient, double lambda, double last_alpha, int n);

double *gradient_descent(double *init, double **xi, double *yi, int m, int n, int iter, char *alpha_type, double tol_x, double tol_f, double tol_g);

double make_test(double *beta, int n1, int n2, int n);

void exec(char *trfn_x, char *trfn_y, int max_iter, double tol_x, double tol_f, double tol_g, char *alpha_type);

#endif