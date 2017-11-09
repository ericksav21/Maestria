#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

#include "memo.h"
#include "matriz_vector.h"
#include "reader.h"

void generate(double *x, double *y, int m, int n, char *files_name) {
	FILE *out = fopen(files_name, "w");
	double *xr = create_vector(m + 1, double);
	double *yr = create_vector(m + 1, double);

	gsl_interp_accel *my_accel_ptr = gsl_interp_accel_alloc();
	gsl_spline *spl = gsl_spline_alloc(gsl_interp_cspline, n);
	gsl_spline_init(spl, x, y, n);

	for(int i = 0; i <= m; i++) {
		xr[i] = x[0] + i * (x[n - 1] - x[0]) / (double)m;
		yr[i] = gsl_spline_eval(spl, xr[i], my_accel_ptr);
	}
	for(int i = 0; i <= m; i++) {
		fprintf(out, "%lf %lf\n", xr[i], yr[i]);
	}

	free_vector(xr);
	free_vector(yr);
	fclose(out);
}

int main(int argc, char **argv) {
	if(argc < 3) {
		printf("Error. Ejecuta: %s [Nombre del archivo] [M].\n", argv[0]);
		return 0;
	}
	int m = atoi(argv[2]);
	char files_name[30];

	strcpy(files_name, argv[1]);

	int nr, nc;
	double **data;

	data = read_matrix(files_name, &nr, &nc);

	double *x = create_vector(nr, double);
	double *y = create_vector(nr, double);
	for(int i = 0; i < nr; i++) {
		x[i] = data[i][0];
		y[i] = data[i][1];
	}
	generate(x, y, m, nr, "tabla.txt");
	printf("Tabla generada.\n");

	free_vector(x);
	free_vector(y);
	free_matrix(data);

	return 0;
}