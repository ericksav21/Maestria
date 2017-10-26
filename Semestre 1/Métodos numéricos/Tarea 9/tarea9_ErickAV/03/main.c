#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"
#include "met_num.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta %s [Archivo de datos].\n", argv[0]);
		return 0;
	}

	char files_name[30];
	int nr, nc;

	strcpy(files_name, argv[1]);
	double **data;

	data = read_matrix(files_name, &nr, &nc);
	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}

	//generate(x, y, nr, "tabla.txt");

	free_vector(x);
	free_vector(y);
	free_matrix(data);

	return 0;
}