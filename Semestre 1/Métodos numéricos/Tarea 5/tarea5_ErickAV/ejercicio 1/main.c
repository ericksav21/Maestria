#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "potencia.h"

int main(int argc, char **argv) {
	char mat_name[30];
	int no_iter, nr, nc;
	double tol;

	if(argc < 4) {
		printf("Error. Ejecuta ./main [Matríz de datos] [Número de iteraciones] [Tolerancia].\n");
		return 0;
	}
	strcpy(mat_name, argv[1]);
	no_iter = atoi(argv[2]);
	tol = atof(argv[3]);

	double **A = read_matrix(mat_name, &nr, &nc);
	double *v_ant = create_vector(nc, double);



	free_matrix(A);
	free_vector(v_ant);

	return 0;
}