#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

/*Función 1*/

void get_gradient_1(double *g, double *x);

void get_Hessian_1(double **H, double *x);

double f_1(double *x);

/*Función 2*/

void get_gradient_2(double *g, double *x, int n);

void get_Hessian_2(MAT3D *mat, double *x, int n);

double f_2(double *x, int n);

#endif