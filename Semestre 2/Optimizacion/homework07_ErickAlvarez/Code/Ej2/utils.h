#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

void generate_init_point(double *x, int n);

/*----- Función de Rosenbrock -----*/
void get_gradient_ros(double *g, double *x, int n);

void get_Hessian_ros(double **H, double *x, int n);

double f_ros(double *x, int n);

/*----- Función de Wood -----*/
void get_gradient_wood(double *g, double *x, int n);

void get_Hessian_wood(double **H, double *x, int n);

double f_wood(double *x);

/*----- Función convexa 1 -----*/
void get_gradient_cvx1(double *g, double *x, int n);

void get_Hessian_cvx1(double **H, double *x, int n);

double f_cvx1(double *x, int n);

/*----- Función convexa 2 -----*/
void get_gradient_cvx2(double *g, double *x, int n);

void get_Hessian_cvx2(double **H, double *x, int n);

double f_cvx2(double *x, int n);

#endif