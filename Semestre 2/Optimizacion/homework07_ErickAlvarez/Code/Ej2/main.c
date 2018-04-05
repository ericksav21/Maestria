#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "utils.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 8) {
		printf("Error. Ejecute: '%s [Nombre archivo de entrada] [Nombre de la función] [Tipo de beta] [Max. iter.] [Tol G] [Tol X] [Tol F]'\n", argv[0]);
		return 0;
	}

	srand(time(NULL));

	char files_name[30], beta_type[30], func_type[30];

	strcpy(files_name, argv[1]);
	strcpy(func_type, argv[2]);
	strcpy(beta_type, argv[3]);
	int iter = atoi(argv[4]);
	double tol_g = atof(argv[5]);
	double tol_x = atof(argv[6]);
	double tol_f = atof(argv[7]);
	
	exec(files_name, beta_type, func_type, iter, tol_g, tol_x, tol_f);

	return 0;
}