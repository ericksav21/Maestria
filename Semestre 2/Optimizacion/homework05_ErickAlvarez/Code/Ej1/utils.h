#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double *read_init_point(char *files_name, int *n);

/*Función 1*/

void get_gradient_1(double *g, double *x);

void get_Hessian_1(double **H, double *x);

double f_1(double *x);

/*Función 2*/

void get_gradient_2(double *g, double *x, int n);

void get_Hessian_2(MAT3D *mat, double *x, int n);

double f_2(double *x, int n);

/*Función 3*/

void get_gradient_3(double *g, double *x, int n);

void get_Hessian_3(double **H, double *x, int n);

double f_3(double *x);

/*Función 3*/

void get_gradient_4(double *g, double *x, double *y, double lambda, int n);

void get_Hessian_4(MAT3D *mat, double lambda, int n);

double f_4(double *x, double *y, double lambda, int n);

#endif