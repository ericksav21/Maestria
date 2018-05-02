#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *read_init_point(char *files_name, int *n);

void write_output(double *d_x, double *d_y, double *p0, double *pk, int m);

/*----- Functions -----*/
void ri_adj(double *x, double *y, double *p, double *r, int n, int m);

void J_adj(double *x, double *p, double **J, int n, int m);

/*----- LU -----*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* LU_solver(double **A, double *d, int n);

double** get_inverse(double **A, int n);

#endif