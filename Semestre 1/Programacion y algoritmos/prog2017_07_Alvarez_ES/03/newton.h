#ifndef NEWTOW_RAPHSON_H
#define NEWTOW_RAPHSON_H

#include <stdio.h>
#include <math.h>

double f(double x);

double fp(double x, double h);

double newton_raphson(double x, double eps, int iter);

#endif