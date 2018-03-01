#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	srand(time(NULL));

	double tol_x = 1e-10;
	double tol_f = 1e-12;
	double tol_g = 1e-6;

	char files_name[30], alpha_type[15];
	double lambda = 1000;
	strcpy(files_name, argv[1]);
	strcpy(alpha_type, argv[2]);
	//smoothing(alpha_type, lambda, tol_x, tol_f, tol_g);
	wood(files_name, alpha_type, tol_x, tol_f, tol_g);

	return 0;
}