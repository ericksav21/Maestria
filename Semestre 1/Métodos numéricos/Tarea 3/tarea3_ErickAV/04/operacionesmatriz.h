#ifndef OPERACIONES_MATRIZ_H
#define OPERACIONES_MATRIZ_H

#include <stdio.h>
#include <math.h>
#include "memo.h"

double *mul_mat_vector(double **A, double *v, double *x, int nr, int nc);

double *resta_vect(double *v1, double *v2, double *x, int n);

double norm(double *x, int sz);

double get_error(double **A, double *x, double *b, int nr, int nc);

double *resuelve_m_tinferior(double **A, double *b, int nr, int nc, double tol);

double *resuelve_m_tsuperior(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

#endif