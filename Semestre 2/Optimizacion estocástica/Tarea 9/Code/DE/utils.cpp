#include "utils.hpp"

/*----- Functions section -----*/
double sphere(vector<double> x) {
	int d = x.size();
	double res = 0.0;

	for(int i = 0; i < d; i++) {
		res += (x[i] * x[i]);
	}

	return res;
}

double ellipsoid(vector<double> x) {
	int d = x.size();
	double res = 0.0;

	for(int i = 0; i < d; i++) {
		res += pow(10.0, 6.0 * (i / (double)d - 1)) * (x[i] * x[i]);
	}

	return res;
}

double zakharov(vector<double> x) {
	int d = x.size();
	double s1 = 0.0, s2 = 0.0;

	for(int i = 0; i < d; i++) {
		s1 += (x[i] * x[i]);
		s2 += 0.5 * (double)(i + 1) * x[i];
	}

	return s1 + (s2 * s2) + pow(s2, 4.0);
}

double rosenbrock(vector<double> x) {
	int d = x.size();
	double res = 0.0;

	for(int i = 0; i < d - 1; i++) {
		res += (pow(x[i] - 1.0, 2) + 100.0 * pow(x[i + 1] - x[i] * x[i], 2));
	}

	return res;
}

double ackley(vector<double> x) {
	int d = x.size();
	double sp = sphere(x);
	double cs = 0.0;
	double div = 1.0 / (double)d;
	for(int i = 0; i < d; i++) {
		cs += cos(2.0 * M_PI * x[i]);
	}

	return -20.0 * exp(-0.2 * sqrt(div * sp)) - exp(div * cs) + 20.0 + M_E;
}

double griewank(vector<double> x) {
	int d = x.size();
	double sum = 0.0;
	double prod = 1.0;

	for(int i = 0; i < d; i++) {
		sum += ((x[i] * x[i]) / 4000.0);
		prod *= cos(x[i] / sqrt((double)i + 1.0));
	}

	return sum - prod + 1.0;
}

double rastrigin(vector<double> x) {
	int d = x.size();
	double sum = 0.0;

	for(int i = 0; i < d; i++) {
		sum += (x[i] * x[i] - 10.0 * cos(2.0 * M_PI * x[i]));
	}

	return 10.0 * d + sum;
}
/*----- End Functions section -----*/

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

double get_median(vector<double> v) {
	vector<double> aux = v;
	sort(aux.begin(), aux.end());
	int mid = aux.size() / 2;
	if(aux.size() % 2 == 0) {
		return (aux[mid] + aux[mid - 1]) / 2.0;
	}
	else {
		return aux[mid];
	}
}