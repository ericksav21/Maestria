#include "utils.h"

void read_files(char *fn_x, char *fn_y, double **mat_x, double *vec_y, int n1, int n2, int *m) {
	FILE *file_x, *file_y;
	file_x = fopen(fn_x, "r");
	file_y = fopen(fn_y, "r");

	double xi[784];
	int yi;
	int i = 0;
	while(fscanf(file_y, "%d", &yi) != EOF) {
		for(int j = 0; j < 783; j++) {
			fscanf(file_x, "%lf,", &xi[j]);
		}
		fscanf(file_x, "%lf", &xi[783]);

		if(yi != n1 && yi != n2) {
			continue;
		}

		vec_y[i] = (float)yi;
		for(int j = 0; j < 784; j++) {
			mat_x[i][j] = xi[j];
		}
		i++;
	}
	(*m) = i;

	fclose(file_x);
	fclose(file_y);
}

double *read_init_point(char *files_name, int *n) {
	FILE *file;
	file = fopen(files_name, "r");

	double *x;
	if(file) {
		int nn;
		fscanf(file, "%d", &nn);
		(*n) = nn;
		x = create_vector(nn, double);
		for(int i = 0; i < nn; i++) {
			fscanf(file, "%lf", &x[i]);
		}

		fclose(file);
		return x;
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return NULL;
	}
}