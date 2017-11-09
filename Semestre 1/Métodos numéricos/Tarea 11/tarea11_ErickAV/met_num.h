#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"

double get_EPS();

double f1(double x);

double f2(double x);

double trap(double (*func)(double), int i, double a, double b, double r_ant);

double eval(double (*func)(double), int n, double a, double b);

#endif