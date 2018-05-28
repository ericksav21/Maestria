#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <vector>

#include "cmaes.h"

using namespace std;

/*----- Functions section -----*/
double sphere(double const *x, int n);

double ellipsoid(double const *x, int n);

double zakharov(double const *x, int n);

double rosenbrock(double const *x, int n);

double ackley(double const *x, int n);

double griewank(double const *x, int n);

double rastrigin(double const *x, int n);
/*----- End Functions section -----*/

double fitfun(double const *x, int n, string ftype);

double get_median(vector<double> v);

void generate_ind(double *x, int n, double linf, double lsup);

double exec(int dim, string ftype, int eval_max, double linf, double lsup, double sd);

#endif