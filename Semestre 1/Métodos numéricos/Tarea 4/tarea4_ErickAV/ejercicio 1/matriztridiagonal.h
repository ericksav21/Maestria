#ifndef MATRIZ_TRIDIAGONAL_H
#define MATRIZ_TRIDIAGONAL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "memo.h"

typedef struct mat3d {
	double *a, *b, *c;
	int n;
} MAT3D;

MAT3D* create_mat_3d(int n);

MAT3D* free_mat_3d(MAT3D *src);

double get_norm(double *x, int n);

double get_error(double *x, double *b, int n);

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol);

double get_EPS();

void print_vector(double *vect, int n);

void print_matrix(double **mat, int nr, int nc);

#endif