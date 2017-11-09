#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Error. Ejecuta: %s [Límite inferior] [Límite superior] [N] [Funcion].\n", argv[0]);
		return 0;
	}
	double a = atof(argv[1]), b = atof(argv[2]);
	int n = atoi(argv[3]), ft = atoi(argv[4]);
	
	double area = 0.0;
	if(ft == 1) {
		area = eval(f1, n, a, b);
	}
	else {
		area = eval(f2, n, a, b);
	}

	printf("Estimación del área: %g\n", area);

	return 0;
}