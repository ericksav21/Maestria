#ifndef ROMBERG_H
#define ROMBERG_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

double fi(double t);

double trap(double (*func)(double), int i, double a, double b, double r_ant);

double eval_romb(double (*func)(double), int n, double a, double b);

#endif