#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

void initialize(double *px, double *py, double **A, double *y, int m);

double f(double x, double a, double b, double c);

void print_data(double *px, double *py, double *sol, int m, char *files_name);

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

#endif