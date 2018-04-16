#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double get_k2(double **Jac, int n, double tol);

void broyden(double *x0, void (*func_ptr)(double*, double*), void (*j_ptr)(double*, double**), int iter_max, double tol);

#endif