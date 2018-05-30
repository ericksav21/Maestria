#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

void LM(double *x0, double *d_x, double *d_y, double *theta, double d4, double *sigma, int n, int m,
	void (*f_ptr)(double*, double*, double*, double*, double, double*, double*, int, int),
	void (*J_ptr)(double*, double*, double*, double*, double, double*, double**J, int, int, double),
	double v, int iter_max, double tol, double h);

#endif