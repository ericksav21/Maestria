#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol);

double N(double x, double *z, int k, int is_next);

int kronec(int i, int j);

double sumN(double *x, double *y, double *z, int m, int k, int coef, int type);

double* generate_phi(double *x, double *y, int m, int n, double lambda);

double phi_x(double *x, double *phi, double *z, double xm, int n);

void generate(double *x, double *y, int m, int n, double lambda, char *files_name);

#endif