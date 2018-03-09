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

double get_f(double *x, double *y, double lambda, int n);

void get_gradient(double *g, double *x, double *y, double lambda, int n);

double step_aprox(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol);

double backtracking(double *x, double *y, double *gradient, double lambda, double last_alpha, int n);

double quadratic_interp(double *x, double *y, double *gradient, double lambda, double last_alpha, int n);

double cubic_interp(double *x, double *y, double *gradient, double lambda, double last_alpha, int n);

double *gradient_descent(double *init, double *yi, double lambda, int n, int iter, char *alpha_type, double fixed_alpha, double tol_x, double tol_f, double tol_g);

void exec(char *files_name, char *alpha_type, double fixed_alpha, double lambda, int max_iter, double tol_x, double tol_f, double tol_g);

#endif
