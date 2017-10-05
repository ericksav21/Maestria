#ifndef FUNCIONES_MATRIZ_H
#define FUNCIONES_MATRIZ_H

#include <stdio.h>
#include <math.h>
#include "memo.h"

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

double **get_I(int n);

double *mul_mat_vector(double **A, double *v, double *x, int nr, int nc);

double **substract_mat(double **A, double **B, double **X, int nr, int nc);

double *substract_vect(double *v1, double *v2, double *x, int n);

double *scale_vect(double *x, double *v, int sz, double c);

double **scale_mat(double **A, double **X, int nr, int nc, double c);

double inner_product(double *x, double *v, int sz);

double norm(double *x, int sz);

double* normalize(double *x, int sz);

double norm_inf(double **A, int nr, int nc);

double get_EPS();

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double inverse_power(double **A, int nr, int nc, double **xk, double *mu, double delta, int iter, int *k_res, double tol);

void get_eigenpairs(double **A, int nr, int nc, int n);

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

#endif