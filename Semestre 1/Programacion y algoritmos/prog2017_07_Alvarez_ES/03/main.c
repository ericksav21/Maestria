#include <stdio.h>

#include "newton.h"

int main(int argc, char **argv) {
	double eps = 1e-5;
	int iter = 100;

	double x = newton_raphson(7.5, eps, iter);
	printf("La raíz es: %lf\n", x);

	return 0;
}