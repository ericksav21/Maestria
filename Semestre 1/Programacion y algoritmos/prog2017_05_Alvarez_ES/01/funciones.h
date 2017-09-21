#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "memo.h"
#include "separador.h"
#include "metricas_calidad.h"

int read_args(int argc, char **argv, char fbname[30], char lbname[30], char quality_metric[30], int *nff, int *nfl, int *seed);

int f_separate(char *first_books_name, int n_files_fb, int start_in);

int* generate_trying_set(int no_blocks);

int* generate_bin_vector(int n);

double distance(double *v1, double *v2, int *bin_vector, int no_words);

void train(int i, double **m1, double **m2, int *bin_vector, int *trying_set, int m_sz, int val_to_set, double *d_min, int *c_dat, int no_words);

//void clasify(int **trying_set1, int **trying_set2, int *bin_vector, double **m1, double **m2, int m1_sz, int m2_sz, int no_words);
void clasify(FOBJ *params, int *bin_vector, int *P, int *N, int *TP, int *TN);

double metric_eval(FOBJ *params, int *bin_vector);

void close_items(int *tsc1, int *tsc2, double **fc1, double **fc2, double **frec, int m1sz, int m2sz, int frec_size);

#endif