#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

/*Función de suavizado*/

void generate_init_point(double *x, int n);

void get_gradient_sm(double *g, double *x, double *y, double lambda, int n);

void get_Hessian_sm(double **H, double lambda, int n);

double f_sm(double *x, double *y, double lambda, int n);

#endif