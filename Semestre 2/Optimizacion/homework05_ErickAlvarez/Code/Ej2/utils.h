#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double *read_init_point(char *files_name, int *n);

/*Función 1*/

double f_1(double *x);

/*Función 2*/

double f_2(double *x, int n);

/*Función 3*/

double f_3(double *x);

/*Función 3*/

void get_gradient_4(double *g, double *x, double *y, double lambda, int n);

double f_4(double *x, double *y, double lambda, int n);

#endif