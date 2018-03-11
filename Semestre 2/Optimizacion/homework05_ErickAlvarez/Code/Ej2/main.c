#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 10) {
		printf("Error, ejecute: '%s [Nombre del archivo de entrenamiento] [Nombre del archivo de prueba] [Máximo de iteraciones] [Tol G] [Tol X] [Tol F] [N1] [N2] [Tamaño de muestra]\n'", argv[0]);
		return 0;
	}

	char train[30], test[30];
	strcpy(train, argv[1]);
	strcpy(test, argv[2]);
	int max_iter = atoi(argv[3]);
	double tol_g = atof(argv[4]);
	double tol_x = atof(argv[5]);
	double tol_f = atof(argv[6]);
	int n1 = atoi(argv[7]);
	int n2 = atoi(argv[8]);
	int tm = atoi(argv[9]);

	exec(train, test, max_iter, tol_x, tol_f, tol_g, n1, n2, tm);

	return 0;
}