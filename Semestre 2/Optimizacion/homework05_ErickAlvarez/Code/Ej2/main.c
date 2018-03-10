#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 7) {
		printf("Error, ejecute: '%s [Nombre base del archivo de entrenamiento] [Nombre base del archivo de prueba] [Máximo de iteraciones] [Tol G] [Tol X] [Tol F] [Tipo de alfa] [Alfa fijo]'", argv[0]);
		return 0;
	}

	/*char trfn_x[30], trfn_y[30];
	strcpy(trfn_x, argv[1]);
	strcpy(trfn_y, argv[2]);
	double **train_x = create_matrix(13000, 784, double);
	double *train_y = create_vector(13000, double);

	int m;
	read_files(trfn_x, trfn_y, train_x, train_y, 1, 8, &m);

	free_matrix(train_x);
	free_vector(train_y);*/

	double lambda = 0.0;
	double fixed_alpha = 1.0;
	char trfn_x[30], trfn_y[30];
	char alpha_type[30];

	strcpy(trfn_x, argv[1]);
	strcpy(trfn_y, argv[2]);
	int max_iter = atoi(argv[3]);
	double tol_g = atof(argv[4]);
	double tol_x = atof(argv[5]);
	double tol_f = atof(argv[6]);
	strcpy(alpha_type, argv[7]);
	
	if(strcmp(alpha_type, "StepFijo") == 0) {
		fixed_alpha = atof(argv[7]);
	}

	exec(trfn_x, trfn_y, alpha_type, fixed_alpha, lambda, max_iter, tol_x, tol_f, tol_g);

	return 0;
}