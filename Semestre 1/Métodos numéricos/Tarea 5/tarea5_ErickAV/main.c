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
	int print_m;
	double tol;

	if(argc < 4) {
		printf("Error. Ejecuta ./main [Matríz de datos] [Número de iteraciones] [Tolerancia] [Imprime matriz (Opcional)].\n");
		return 0;
	}

	strcpy(mat_name, argv[1]);
	no_iter = atoi(argv[2]);
	tol = atof(argv[3]);
	if(argc >= 5) {
		print_m = atoi(argv[4]);
	}

	double **A = read_matrix(mat_name, &nr, &nc);
	double *v_ant = create_vector(nc, double);

	printf("Tamaño de la matriz: %d %d\n", nr, nc);

	if(print_m == 1)
		print_matrix(A, nr, nc);

	printf("Obteniendo el eigenvalor...\n");
	double eigenvalue = power_iteration(A, v_ant, nr, nc, no_iter, tol);

	printf("Eigenvalor encontrado: %lf\n", eigenvalue);

	free_matrix(A);
	free_vector(v_ant);

	return 0;
}