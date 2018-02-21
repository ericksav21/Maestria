#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"
#include "functions.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error, ejecuta: %s [Grado del polinomio].\n", argv[0]);
		return 0;
	}

	FILE *out1, *out2;
	out1 = fopen("samples.txt", "w");
	out2 = fopen("points.txt", "w");
	srand(time(NULL));
	int n = 4, dim = atoi(argv[1]);
	//Generar una discretización uniforme
	double a = 0.1, b = 10.0;
	double *x = create_vector(n, double);
	double dx = (b - a) / (double)(n - 1);
	for(int i = 0; i < n; i++) {
		x[i] = a + i * dx;
	}
	double *y = generate_samples(x, n);
	double *coef;
	coef = least_squares(x, y, n, dim);
	printf("Coeficientes:\n");
	for(int i = 0; i < dim + 1; i++) {
		printf("%lf\n", coef[i]);
	}

	for(int i = 0; i < n; i++) {
		double val = 0.0;
		for(int j = 0; j < (dim + 1); j++) {
			val += (coef[j] * pow(x[i], dim - j));
		}
		fprintf(out1, "%lf %lf\n", x[i], y[i]);
		fprintf(out2, "%lf %lf\n", x[i], val);
	}

	free(x);
	free(y);
	free(coef);

	return 0;
}