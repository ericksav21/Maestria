#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#include "memo.h"
#include "matriz_vector.h"

double **read_matrix(char *files_name, int *nr, int *nc);

double **gslmat2array2d(gsl_matrix *mat);

#endif