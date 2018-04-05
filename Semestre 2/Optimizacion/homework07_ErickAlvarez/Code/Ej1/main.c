#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "utils.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 6) {
		printf("Error. Ejecute: '%s [Nombre archivo de entrada] [Lambda] [Tol G] [Tol X] [Tol F]'\n", argv[0]);
		return 0;
	}

	srand(time(NULL));

	char files_name[30];

	strcpy(files_name, argv[1]);
	double lambda = atof(argv[2]);
	double tol_g = atof(argv[3]);
	double tol_x = atof(argv[4]);
	double tol_f = atof(argv[5]);
	
	exec(files_name, lambda, tol_g, tol_x, tol_f);

	return 0;
}