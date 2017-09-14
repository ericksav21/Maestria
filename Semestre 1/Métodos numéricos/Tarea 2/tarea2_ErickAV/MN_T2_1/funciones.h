#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void fill_arr_randomly(double *arr, int n);

void tiempoTranscurrido(struct timeval t1, struct timeval  t2);

void funcion_1(double *a, double *b, double *c, int n);

void funcion_2(double *a, double *b, double *c, int n);

double funcion_3(double *a, double *b, int n);

void funcion_4(double **A, double *x, double *b, int n);

void funcion_5(double **P, double **Q, double **R, int n);

#endif
