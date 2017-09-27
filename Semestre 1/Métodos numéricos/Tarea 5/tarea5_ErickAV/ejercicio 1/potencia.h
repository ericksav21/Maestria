#ifndef POTENCIA_H
#define POTENCIA_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

double* substract_vectors(double *v1, double *v2, double *x, int n);

double* scale_vector(double *v, double *x, double alpha, int n);

double* mul_mat_vec(double **A, double *v, double *x, int nr, int nc);

double get_norm(double *v, int n);

double* normalize(double *v, int n);

double get_err(double **A, double *v, double vp, int nr, int nc);

double power_iteration(double **A, double *v_ant, int nr, int nc, int iter, double tol);

#endif