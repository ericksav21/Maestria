#include <stdio.h>

#include "memo.h"
#include "reader.h"

int main() {
	char tipo;
	int n, nr, nc;
	printf("Tipo: ");
	scanf("%c", &tipo);

	if(tipo == 'm' || tipo == 'M') {
		char cfile[] = "mat.bin";
		printf("Matriz\nDimensiones: ");
		scanf("%d %d", &nr, &nc);
		printf("Ingresa los valores:\n");

		double **mat = create_matrix(nr, nc, double);
		for(int i = 0; i < nr; i++) {
			for(int j = 0; j < nc; j++) {
				scanf("%lf", &mat[i][j]);
			}
		}
		write_matrix(mat, nr, nc, cfile);

		free_matrix(mat);
	}
	else if(tipo == 'v' || tipo == 'V') {
		char cfile[] = "vect.bin";
		printf("Vector\nDimension: ");
		scanf("%d", &n);
		printf("Ingresa los valores:\n");

		double *vect = create_vector(n, double);
		for(int i = 0; i < n; i++) {
			scanf("%lf", &vect[i]);
		}
		write_vector(vect, n, cfile);

		free_vector(vect);
	}
	else {
		printf("Tipo incorrecto.\n");
	}

	return 0;
}