#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "memo.h"

double *read_vector(char *cfile, int *nr);

double **read_matrix(char *cfile, int *nr, int *nc);

int write_vector(double *vec, int dim, char *cfile);

int write_matrix(double **mat, int nr, int nc, char *cfile);

#endif