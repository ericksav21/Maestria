#include "linear.hpp"

LinearAlgebra::LinearAlgebra() {}

LinearAlgebra::~LinearAlgebra() {}

double LinearAlgebra::inner_product(vector<double> v1, vector<double> v2) {
	double res = 0.0;
	for(int i = 0; i < v1.size(); i++) {
		res += (v1[i] * v2[i]);
	}

	return res;
}

double LinearAlgebra::norm(vector<double> v) {
	return sqrt(inner_product(v, v));
}