#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *read_init_point(char *files_name, int *n);

/*----- Functions -----*/
void ri_rosenbrock(double *x, double *y, int n, int m);

void J_rosenbrock(double *x, double **J, int n, int m);

/*----- LU -----*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* LU_solver(double **A, double *d, int n);

double** get_inverse(double **A, int n);

#endif