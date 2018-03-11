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

double backtracking(double **x, double *y, double *beta, double *gradient, double last_alpha, int m, int n);

double *gradient_descent(double *init, double **xi, double *yi, int m, int n, int iter, char *alpha_type, double tol_x, double tol_f, double tol_g);

void make_test(char *test, double *beta, int n1, int n2, int n);

void exec(char *train, char *test, int max_iter, double tol_x, double tol_f, double tol_g, int n1, int n2, int ts);

#endif