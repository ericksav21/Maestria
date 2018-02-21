#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

double rand_in_range(double a);

double rand_normal(double mean, double sigma);

double *generate_samples(double *x, int n);

double *least_squares(double *x, double *y, int n, int dim);

#endif