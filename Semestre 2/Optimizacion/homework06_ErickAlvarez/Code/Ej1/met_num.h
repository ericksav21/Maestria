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

double* PU(double *g, MAT3D *H3D, int n);

double* PB(double *g, MAT3D *H3D, int n);

double mk(int type, double *x, double *p, double *g, double **H, MAT3D *H3D, int n);

#endif