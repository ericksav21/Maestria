#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

void get_gradient(double *g, double ***hc, double **v_c, double *alpha, double *mu, double sigma,
				int nbins, int ng, int optimice_mu);

double get_f(double ***hc, double **v_c, double *alpha, double *mu, double sigma,
			int nbins, int ng);

double get_Hessian(double **H, double ***hc, double **v_c, double *alpha, double *mu, double sigma,
				int nbins, int ng, int optimice_mu);

double* PU(double *g, double **H, int n);

double* PB(double *g, double **H, int n);

double* PC(double *g, double **H, double delta, int n);

double mk(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng,
			double *p, double *g, double **H, int optimice_mu);

double phi(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng,
			double *ppk, double *g, double **H, int optimice_mu);

double* dogleg(double *pu, double *pb, double delta, int n);

double* approx(double *x, double *g, double **H, double delta, int n);

double* r_confidence(double ***hc, double **v_c, double *alpha, double *mu, double sigma, 
				int nbins, int ng, int optimice_mu, int max_iter);

void optimice(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng);

void solve(char *bg_hist_fn, char *obj_hist_fn, int ng, double sigma);

#endif