#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 4) {
		printf("Error. Ejecuta: %s [Límite inferior] [Límite superior] [N].\n", argv[0]);
		return 0;
	}
	int a = atoi(argv[1]), b = atoi(argv[2]), n = atoi(argv[3]);

	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}
	generate(x, y, nr, n, lambda, "tabla.txt");
	printf("Tabla generada.\n");

	free_vector(x);
	free_vector(y);

	return 0;
}