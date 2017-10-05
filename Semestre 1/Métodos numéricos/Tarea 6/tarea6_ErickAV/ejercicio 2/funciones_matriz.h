#ifndef FUNCIONES_MATRIZ_H
#define FUNCIONES_MATRIZ_H

#include <stdio.h>
#include <math.h>
#include "memo.h"

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

double** get_I(int n);

double** transpose_matrix(double **A, double **X, int nr, int nc);

double* mul_mat_vector(double **A, double *v, double *x, int nr, int nc);

double** mul_mat_mat(double **A, double **B, double **X, int n);

double** substract_mat(double **A, double **B, double **X, int nr, int nc);

double* substract_vect(double *v1, double *v2, double *x, int n);

double* scale_vect(double *x, double *v, int sz, double c);

double** scale_mat(double **A, double **X, int nr, int nc, double c);

double inner_product(double *x, double *v, int sz);

double norm(double *x, int sz);

double* normalize(double *x, int sz);

double norm_inf(double **A, int nr, int nc);

int sign(double n);

double get_EPS();

double** Givens(int n, int i, int j, double s, double c);

double Jacobi(double ***A, double ***V, int nr, int nc, double tol, int M, int *k_res);

void get_eigenpairs(double **A, int nr, int nc, int n);

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

double** copy_matrix(double **A, double **B, int nr, int nc);

#endif