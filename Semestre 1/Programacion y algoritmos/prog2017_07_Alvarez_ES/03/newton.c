#include "newton.h"

double f(double x) {
	//return x * x - 25.0;
	return pow(tan(x + 2), 2) / pow(x, 3);
}

double fp(double x, double h) {
	return (f(x + h) - f(x - h)) / (2.0 * h);
}

double newton_raphson(double x, double eps, int iter) {
	double fx = f(x);
	if(iter == 0) {
		printf("No se encontró la raíz.\n");
		return -1;
	}
	if(fabs(fx) < eps)
		return x;

	x = x - fx / fp(x, eps);
	return newton_raphson(x, eps, iter - 1);
}
