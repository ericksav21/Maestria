#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

double get_EPS();

double f1(double x);

double F1(double a, double b);

double f2(double x);

double F2(double a, double b);

double trap(double (*func)(double), int i, double a, double b, double r_ant);

double eval(double (*func)(double), int n, double a, double b);

#endif