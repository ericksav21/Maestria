#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double *read_init_point(char *files_name, int *n);

double ***read_histogram(char *files_name, int *n);

double **vect_c(int nbins);

/*----- Función principal -----*/
double f_pexp(double *ck, double *mu, double sigma);

double f_psum(double *ck, double *alpha, double *mu, double sigma, int ng);

double f_prin(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng);

void g_alpha(double *grad, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng);

void g_mu(double *grad, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng);

void H_alpha(double **H, double **v_c, double *mu, double sigma, int nbins, int ng);

void H_mu(double **H, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng);

/*Función 2*/

void get_gradient_2(double *g, double *x, int n);

void get_Hessian_2(double **H, double *x, int n);

double f_2(double *x, int n);

/*LU*/

double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

double* LU_solver(double **A, double *d, int n);

int cholesky(double **A, double ***L, double ***Lt, int n, double tol);

#endif