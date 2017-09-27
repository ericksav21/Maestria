#ifndef POTENCIA_H
#define POTENCIA_H

#include <stdio.h>
#include <math.h>

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

double* mul_mat_vec(double **A, double *v, double *x, int nr, int nc);

double* normalize(double *v, int n);

double power_iteration(double **A, double *v_ant, int nr, int nc)

#endif