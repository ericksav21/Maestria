#ifndef LINEAR_H
#define LINEAR_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LinearAlgebra {
public:
	LinearAlgebra();
	~LinearAlgebra();
	double inner_product(vector<double> v1, vector<double> v2);
	double norm(vector<double> v);
	void print_vector(vector<double> v);
};

#endif