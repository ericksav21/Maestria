#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 8) {
		printf("Error, ejecute: '%s [Nombre base del archivo de entrenamiento] [Nombre base del archivo de prueba] [Máximo de iteraciones] [Tol G] [Tol X] [Tol F] [Tipo de alfa]'", argv[0]);
		return 0;
	}

	char trfn_x[30], trfn_y[30], alpha_type[30];
	strcpy(trfn_x, argv[1]);
	strcpy(trfn_y, argv[2]);
	int max_iter = atoi(argv[3]);
	double tol_g = atof(argv[4]);
	double tol_x = atof(argv[5]);
	double tol_f = atof(argv[6]);
	strcpy(alpha_type, argv[7]);

	exec(trfn_x, trfn_y, max_iter, tol_x, tol_f, tol_g, alpha_type);

	return 0;
}