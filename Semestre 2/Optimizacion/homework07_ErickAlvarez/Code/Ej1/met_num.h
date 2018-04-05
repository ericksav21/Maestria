#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"

double get_EPS();

double* conjugate_gradient(double *init, double *y, int n, double lambda, double tol_g, double tol_x, double tol_f);

void exec(char *files_name, double lambda, double tol_g, double tol_x, double tol_f);

#endif
