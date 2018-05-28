#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double **PCA(double **X, int nr, int nc, int noEig);

void compResiduals(double **X_c, double **U, double *residuals, int nr, int nc);

double **PCA_g(double **X, double *m, int nr, int nc, int noEig, double p);

#endif