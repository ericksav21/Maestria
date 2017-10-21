#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

#include <gsl/gsl_math.h>
#include <gsl/gsl_ieee_utils.h>

int cmpfunc (const void * a, const void * b);

double **create_matrix_vander(int n);

void ej_2(double **A, int n);

double **ej_3(double **A, int n);

double ej_4(double **A, int n);

double ej_5(double **A, int n);

#endif