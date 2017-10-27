#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double newton(double *x, double xc, int i);

double** differences(double *x, double *y, int n);

double evaluate_pol(double *x, double **A, double xc, int n);

void generate(double *x, double *y, int n, char *files_name);

#endif