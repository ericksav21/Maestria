#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *read_init_point(char *files_name, int *n);

/*Función 1*/

void get_gradient_1(double *g, double *x);

void get_Hessian_1(double **H, double *x);

double f_1(double *x);

/*Función 2*/

void get_gradient_2(double *g, double *x, int n);

void get_Hessian_2(double **H, double *x, int n);

//void get_Hessian_2(MAT3D *mat, double *x, int n);

double f_2(double *x, int n);

/*LU*/

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* LU_solver(double **A, double *d, int n);

double *solve_m_tridiagonal(MAT3D *mat, double *d, double tol);

int cholesky(double **A, double ***L, double ***Lt, int n, double tol);

#endif