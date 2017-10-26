#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double lagrange(double *x, double xc, int i, int n);

double evaluate_pol(double *x, double *y, double xc, int n);

void generate(double *x, double *y, int n, char *files_name);

#endif