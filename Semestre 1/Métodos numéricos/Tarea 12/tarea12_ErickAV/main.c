#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 4) {
		printf("Error. Ejecuta: %s [Límite inferior] [Límite superior] [N].\n", argv[0]);
		return 0;
	}
	double a = atof(argv[1]), b = atof(argv[2]);
	int n = atoi(argv[3]);
	solve(a, b, n);	

	return 0;
}