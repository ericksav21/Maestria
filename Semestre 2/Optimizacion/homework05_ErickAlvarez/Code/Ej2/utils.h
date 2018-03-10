#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

void read_files(char *fn_x, char *fn_y, double **mat_x, double *vec_y, int n1, int n2, int *m);

double *read_init_point(char *files_name, int *n);

/*Función 1*/

void get_gradient_1(double *g, double *x);

void get_Hessian_1(double **H, double *x);

double f_1(double *x);

/*Función 3*/

void get_gradient_3(double *g, double *x, int n);

void get_Hessian_3(double **H, double *x, int n);

double f_3(double *x);

/*Función Principal*/

void get_gradient_p(double *g, double *xi, double yi, double *beta, double beta0, int n);

double f_p(double *xi, double yi, double *beta, double beta0, int n);

#endif