#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double **create_matrix_vander(double *xs, int n);

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* solve_system(double *A, double *b, int n, double tol);

double evaluate_pol(double x, double *c, int n);

void generate(double *x, double *c, int n, char *files_name);

#endif