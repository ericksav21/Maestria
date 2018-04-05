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

double get_f(double *x, char *func_type, int n);

void get_gradient(double *g, double *x, char *func_type, int n);

void get_Hessian(double **H, double *x, char *func_type, int n);

double backtracking(double *x, double *g, double *p, char *func_type, double alpha_0, int n);

double Fletcher_Reeves(double *lst_gradient, double *gradient, int n);

double Polak_Ribiere(double *lst_gradient, double *gradient, int n);

double Hestnes_Stiefel(double *lst_gradient, double *gradient, double *d, int n);

double FR_PR(double *lst_gradient, double *gradient, int n);

double get_Beta(double *lst_gradient, double *gradient, double *d, char *beta_type, int n);

double* conjugate_gradient(double *init, char *beta_type, char *func_type, int n, int iter, double tol_g, double tol_x, double tol_f);

void exec(char *files_name, char *beta_type, char *func_type, int iter, double tol_g, double tol_x, double tol_f);

#endif
