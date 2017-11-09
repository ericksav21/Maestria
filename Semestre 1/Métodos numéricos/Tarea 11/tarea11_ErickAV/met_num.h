#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol);

double f1(double x);

double f2(double x);

double eval_trap(double (*func)(double), int i, double r_i1);

#endif