#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

/*----- Functions -----*/
void init_x0(double *res, int v1);

void F(double *x, double *res);

void J(double *x, double **res);

/*----- LU -----*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* LU_solver(double **A, double *d, int n);

/*----- Jacobi -----*/
void GAG(double ***A, double ***V, int n, int i, int j, double c, double s);

double Jacobi(double ***A, double ***V, int nr, int nc, double tol, int M, int *k_res);

#endif