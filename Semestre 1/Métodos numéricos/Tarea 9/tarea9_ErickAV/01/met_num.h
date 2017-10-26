#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

int read_points(char *files_name, double *x, double *y, int n);

double **create_matrix_vander(double *xs, int n);

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* solve_system(double *A, double *b, int n, double tol);

#endif