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

/*----- Función 1 -----*/

void get_gradient_1(double *g, double *x) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[1] = 200.0 * (x[1] - x[0] * x[0]);
}

void get_Hessian_1(double **H, double *x) {
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[0][1] = H[1][0] = -400.0 * x[0];
	H[1][1] = 200.0;
}

double f_1(double *x) {
	return 100.0 * pow(x[1] - x[0] * x[0], 2) + pow(1.0 - x[0], 2);
}

/*----- Función 3 -----*/

void get_gradient_3(double *g, double *x, int n) {
	g[0] = 400.0 * (pow(x[0], 3) - x[0] * x[1]) + 2.0 * (x[0] - 1.0);
	g[1] = -200.0 * (x[0] * x[0] - x[1]) + 20.2 * (x[1] - 1.0) + 19.8 * (x[3] - 1.0);
	g[2] = 2.0 * (x[2] - 1.0) + 360.0 * (pow(x[2], 3) - x[2] * x[3]);
	g[3] = -180.0 * (x[2] * x[2] - x[3]) + 20.2 * (x[3] - 1.0) + 19.8 * (x[1] - 1.0);
}

void get_Hessian_3(double **H, double *x, int n) {
	H[0][0] = 400.0 * (3.0 * x[0] * x[0] - x[1]) + 2.0;
	H[1][1] = 220.2;
	H[2][2] = 2.0 + 360.0 * (3.0 * x[2] * x[2] - x[3]);
	H[3][3] = 200.2;

	H[0][1] = H[1][0] = -400.0 * x[0];
	H[0][2] = H[0][3] = H[2][0] = H[3][0] = H[1][2] = H[2][1] = 0.0;
	H[1][3] = H[3][1] = 19.8;
	H[2][3] = H[3][2] = -360 * x[2];
}

double f_3(double *x) {
	double p1 = 100.0 * pow((x[0] * x[0] - x[1]), 2) + pow(x[0] - 1.0, 2) + pow(x[2] - 1.0, 2) + 90.0 * pow(x[2] * x[2] - x[3], 2);
	double p2 = 10.1 * (pow(x[1] - 1.0, 2) + pow(x[3] - 1.0, 2)) + 19.8 * (x[1] - 1.0) * (x[3] - 1.0);

	return p1 + p2;
}

/*----- Función 4 -----*/
//Función de interés para este problema
void get_gradient_p(double *g, double *xi, double yi, double *beta, int n) {
	//Parcial con respecto a beta_k
	double aux1 = 0.0, pi = 0.0, ex = 0.0;
	aux1 = inner_product(xi, beta, n);
	ex = exp(-aux1 - beta[n]);
	pi = 1.0 / (1.0 + ex);

	double par = 0.0;
	for(int i = 0; i < n; i++) {
		par += (yi * pi * ex + (1 - yi) * (pi * ex - 1));
	}
	for(int k = 0; k < n; k++) {
		g[k] = (-1.0) * par * xi[k];
	}
	g[n] = (-1.0) * par;
}

double f_p(double *xi, double yi, double *beta, int n) {
	double aux1 = 0.0, pi = 0.0, ex = 0.0;
	aux1 = inner_product(xi, beta, n);
	ex = exp(-aux1 - beta[n]);
	pi = 1.0 / (1.0 + ex);

	double res = 0.0;
	for(int i = 0; i < n; i++) {
		res += (yi * log(pi)) + (1.0 - yi) * log(1.0 - pi);
	}

	return (-1.0) * res;
}