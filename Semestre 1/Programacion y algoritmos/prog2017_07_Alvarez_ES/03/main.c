#include <stdio.h>
#include <stdlib.h>

#include "newton.h"

int main(int argc, char **argv) {
	if(argc < 4) {
		printf("Error. Ejecuta: %s [X inicial] [Tolerancia] [No. iteraciones]\n", argv[0]);
		return 0;
	}

	double x0 = atof(argv[1]);
	double eps = atof(argv[2]);
	int iter = atoi(argv[3]);

	double x = newton_raphson(x0, eps, iter);
	printf("La raíz es: %lf\n", x);

	return 0;
}