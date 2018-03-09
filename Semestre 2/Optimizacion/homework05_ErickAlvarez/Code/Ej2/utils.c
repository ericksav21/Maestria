#include "utils.h"

void read_files(char *fn_x, char *fn_y, double **mat_x, double *vec_y, int n1, int n2, int *m, int *n) {
	FILE *file_x, *file_y;
	file_x = fopen(fn_x);
	file_y = fopen(fn_y);

	char x[2500], y[5];

	int i = 0;
	while(fgets(y, sizeof(line), file_y) != NULL) {
		fgets(x, sizeof(x), file_x);
		int yi = atoi(y);
		if(yi != n1 && yi != n2) {
			continue;
		}
		int j = 0;
		while(strtok(x, " ") != NULL) {

		}
	}

	fclose(fn_x);
	fclose(fn_y);
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

/*----- Función 1 -----*/

double f_1(double *x) {
	return 100.0 * pow(x[1] - x[0] * x[0], 2) + pow(1.0 - x[0], 2);
}

/*----- Función 2 -----*/

double f_2(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n - 1; i++) {
		res += (100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow(1.0 - x[i], 2));
	}

	return res;
}

/*----- Función 3 -----*/

double f_3(double *x) {
	double p1 = 100.0 * pow((x[0] * x[0] - x[1]), 2) + pow(x[0] - 1.0, 2) + pow(x[2] - 1.0, 2) + 90.0 * pow(x[2] * x[2] - x[3], 2);
	double p2 = 10.1 * (pow(x[1] - 1.0, 2) + pow(x[3] - 1.0, 2)) + 19.8 * (x[1] - 1.0) * (x[3] - 1.0);

	return p1 + p2;
}

/*----- Función 4 -----*/
void get_gradient_4(double *g, double *x, double *y, double lambda, int n) {
	g[0] = 2.0 * (x[0] - y[0]) - 2.0 * lambda * (x[1] - x[0]);
	g[n - 1] = 2.0 * (x[n - 1] - y[n - 1]) + 2.0 * lambda * (x[n - 1] - x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 2.0 * (x[i] - y[i]) + 2.0 * lambda * (x[i] - x[i - 1]) - 2.0 * lambda * (x[i + 1] - x[i]);
	}
}

double f_4(double *x, double *y, double lambda, int n) {
	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (x[i] - y[i]) * (x[i] - y[i]);
	}
	for(int i = 0; i < n - 1; i++) {
		res += lambda * pow((x[i + 1] - x[i]), 2);
	}

	return res;
}