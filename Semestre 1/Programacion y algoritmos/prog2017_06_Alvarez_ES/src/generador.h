#ifndef GENERADOR_H
#define GENERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "funciones.h"
#include "frecuencias.h"
#include "metricas_calidad.h"

int *generate_bv(int *bv, double *P, int n, int nfeat);

double vb_xnorm(double *P, int n);

int *get_best_bv(ARGSOBJ *args, FOBJ *params);

#endif