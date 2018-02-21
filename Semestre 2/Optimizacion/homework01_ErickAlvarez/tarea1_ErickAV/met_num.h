#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

#define max(a, b) (a > b ? a : b)

double get_EPS();

/*
	Calcula la factorización Cholesky de una matriz simétrica
	definida positiva, regresa 1 si dicha factorización se hizo.
	De caso contrario regresa 0.
*/
int cholesky(double **A, double ***L, int n, double tol);

/*
	Calcula la norma 1 de una matriz, la cual es la máxima suma en
	valor absoluto de las columnas de una matriz
*/
double norm_1(double **A, int n);

/*
	Procedimiento que describe la tarea.
*/
void proc(double **A, int n);

#endif