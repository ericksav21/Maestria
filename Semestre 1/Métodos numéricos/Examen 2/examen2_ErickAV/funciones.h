#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"
#include "romberg.h"
#include "spline.h"

//Función con integral
double ej_1(double x);

//Diferencias centrales
double ej_2(double x, double h);

//Newton-Raphson
double ej_3(double x0, double h, double tol, int iter);

//Partición uniforme de 10 puntos
double* particion(double xr);

//Guarda un conjunto de puntos en un archivo
void save(double *x, double *y, int n, char *files_name);

//Genera un Spline Cúbico calculando un intervalo con 10 puntos
void ej_4();

#endif