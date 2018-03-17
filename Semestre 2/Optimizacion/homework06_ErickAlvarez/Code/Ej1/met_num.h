#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n);

void get_gradient(double *g, double *x, int n);

double get_f(double *x, int n);

double* PU(double *g, double **H, int n);

double* PB(double *g, double **H, int n);

double* PC(double *g, double **H, double delta, int n);

double mk(double *x, double *p, double *g, double **H, int n);

double phi(double *x, double *ppk, double *g, double **H, int n);

double *dogleg(double *pu, double *pb, double delta, int n);

double *approx(double *x, double *g, double **H, double delta, int n);

void r_confidence(double *init, int max_iter, int n);

#endif