#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <cfloat>
#include <algorithm>

#include "utils.hpp"

class Differential {
private:
	int pop_size, dim = 30;
	int iter_max;
	double linf, lsup;
	double cr = 0.8, F = 0.3;
	double tol = 1e-3;
	double best;
	string func_type;

	double get_f(vector<double> x);
	void print_pop(vector<pair<vector<double>, double > > pop);
	vector<pair<vector<double>, double > > generate_pop();
public:
	Differential(int pop_size, double linf, double lsup, string func_type, int iter_max);
	~Differential();
	double get_best();
	void set_CR(double CR);
	void run();
};

#endif
