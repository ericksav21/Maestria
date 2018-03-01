#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double get_EPS();

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n);

double get_f(int type, double *x, double *y, double lambda, int n);

void get_gradient(int type, double *g, double *x, double *y, double lambda, int n);

void get_Hessian(int type, double **H, double *x, int n);

double compute_alpha_1(double *gradient, double **Hessian, int n, double tol);

double compute_alpha_1_3d(double *gradient, MAT3D *Hessian, int n, double tol);

double compute_alpha_2();

double compute_alpha_3(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol);

double *gradient_descent(double *init, double *yi, double lambda, int n, int iter, char *alpha_type, int ex_no, double tol_x, double tol_f, double tol_g);

void rosembrock_2(char *files_name, char *alpha_type, double tol_x, double tol_f, double tol_g);

void rosembrock_n(char *files_name, char *alpha_type, double tol_x, double tol_f, double tol_g);

void wood(char *files_name, char *alpha_type, double tol_x, double tol_f, double tol_g);

void smoothing(char *alpha_type, double lambda, double tol_x, double tol_f, double tol_g);

#endif
