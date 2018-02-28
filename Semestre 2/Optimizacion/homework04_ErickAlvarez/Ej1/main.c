#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	srand(time(NULL));

	int n = 2;
	double *x0 = create_vector(2, double);
	x0[0] = -0.2;
	x0[1] = 1.0;

	double *xk = gradient_descent(x0, n, 1000000, 1);
	print_vector(xk, n);

	printf("\n\nPunto inicial aleatorio:\n");
	x0[0] = (double)(rand() % 100 + 50);
	x0[1] = (double)(rand() % 100 + 50);
	xk = gradient_descent(x0, n, 1000000, 1);
	printf("\nXk:\n");
	print_vector(xk, n);
	printf("\nVector inicial:\n");
	print_vector(x0, n);

	free_vector(x0);
	free_vector(xk);
	return 0;
}