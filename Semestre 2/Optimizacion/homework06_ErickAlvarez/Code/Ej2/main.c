#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 5) {
		printf("Error. Ejecuta: %s [Histograma de fondo] [Histograma del objeto] [Número de Gaussianas] [Sigma].\n", argv[0]);
		return 0;
	}
	
	//Puede ser conveniente usar alguna semilla en particular
	srand(time(NULL));

	int ng = atoi(argv[3]);
	double sigma = atof(argv[4]);
	solve(argv[1], argv[2], ng, sigma);

	return 0;
}