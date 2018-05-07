#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

void LM(double *x0, int n, int m, void (*f_ptr)(double*, double*, int, int), void (*J_ptr)(double*, double**, int, int),
		double v, int iter_max, double tol);

#endif