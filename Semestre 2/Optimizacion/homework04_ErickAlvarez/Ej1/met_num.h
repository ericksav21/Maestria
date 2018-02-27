#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double f(double x1, double x2);

double *get_gradient(double x1, double x2);

double **get_Hessian(double x1, double x2);

#endif
