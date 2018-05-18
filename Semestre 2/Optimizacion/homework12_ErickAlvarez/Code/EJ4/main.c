#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 6) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [Mu_0] [Tau] [Tau_0] [Dx].\n", argv[0]);
		return 0;
	}
	char files_name[30];
	strcpy(files_name, argv[1]);
	double mu = atof(argv[2]);
	double tau = atof(argv[3]);
	double tau_0 = atof(argv[4]);
	double dx = atof(argv[5]);

	int n;
	int m = 4;
	double *x = read_init_point(files_name, &n);
	QP(x, n, m, tau_0, tau, mu, dx);

	free_vector(x);
	
	return 0;
}