#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

/*----- Functions section -----*/

double sphere(vector<double> x);

double ellipsoid(vector<double> x);

double zakharov(vector<double> x);

double rosenbrock(vector<double> x);

double ackley(vector<double> x);

double griewank(vector<double> x);

double rastrigin(vector<double> x);

/*----- End Functions section -----*/

int rand_in_range(int a, int b);

double bin_to_real(vector<int> bin, int a, int b);

#endif