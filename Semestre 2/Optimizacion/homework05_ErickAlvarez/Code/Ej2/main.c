#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 7) {
		printf("Error, ejecute: '%s [Nombre archivo x0] [Máximo de iteraciones] [Tol G] [Tol X] [Tol F] [Tipo de alfa] [Alfa fijo]'", argv[0]);
		return 0;
	}

	double lambda = 0.0;
	double fixed_alpha = 1.0;
	char files_name[30], alpha_type[30];

	strcpy(files_name, argv[1]);
	int max_iter = atoi(argv[2]);
	double tol_g = atof(argv[3]);
	double tol_x = atof(argv[4]);
	double tol_f = atof(argv[5]);
	strcpy(alpha_type, argv[6]);
	
	if(strcmp(alpha_type, "StepFijo") == 0) {
		fixed_alpha = atof(argv[7]);
	}

	exec(files_name, alpha_type, fixed_alpha, lambda, max_iter, tol_x, tol_f, tol_g);

	return 0;
}