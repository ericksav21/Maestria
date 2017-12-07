#include "funciones.h"

double ej_1(double x) {
	double res = pow(x - 3.0, 3) / 20.0;
	double integral = eval_romb(fi, 8, 0, x);

	res += (10.0 * integral);
	res -= 3.0;

	return res;
}

double ej_2(double x, double h) {
	//Diferencias centrales
	double res = (ej_1(x + h) - ej_1(x - h)) / (2.0 * h);
	return res;
}

double ej_3(double x0, double h, double tol, int iter) {
	int t = 1;
	double xt = x0, xt1 = 0;
	while(1) {
		xt1 = xt - (ej_1(xt) / ej_2(xt, h));
		printf("Iteración %d - Valor de f(xt): %g, valor de xt: %lf\n", t, ej_1(xt1), xt1);
		if(fabs(ej_1(xt1)) < tol || t == iter)
			break;
		xt = xt1;
		t++;
	}

	return xt1;
}

double* particion(double xr) {
	double *v = create_vector(10, double);
	double a = xr - 4.0, b = xr + 4.0;
	printf("\nxr - 4: %lf, xr + 4: %lf\n", a, b);
	double dx = (b - a) / 9.0;
	for(int i = 0; i < 10; i++)
		v[i] = (a + i * dx);

	return v;
}

void save(double *x, double *y, int n, char *files_name) {
	FILE *out = fopen(files_name, "w");
	for(int i = 0; i < n; i++) {
		fprintf(out, "%lf %lf\n", x[i], y[i]);
	}

	fclose(out);
}

void ej_4() {
	double x0 = -2.0;
	double tol = sqrt(get_EPS());
	double h = 0.0;

	//Determinar el valor de h
	for(int i = 0; i < 99; i++) {
		double hi = 0.01 - ((double)i / 10000.0);
		if(fabs(ej_2(x0, (hi + 1e-4)) - ej_2(x0, hi)) < tol) {
			h = hi;
			break;
		}
	}
	printf("Valor de h: %g\n\n", h);

	printf("Cálculo de la raíz con Newton-Raphson:\n");
	double xr = ej_3(x0, h, tol, 100);
	printf("Raíz encontrada: %lf\n", xr);
	double* zk = particion(xr);
	double* fzk = create_vector(10, double);

	for(int i = 0; i < 10; i++) {
		fzk[i] = ej_1(zk[i]);
	}
	printf("Puntos ({zk, fzk}):\n");
	print_vector(zk, 10);
	print_vector(fzk, 10);

	double *M = generate_M(zk, fzk, 10, tol);
	int npuntos = 60;
	generate(zk, fzk, M, npuntos, 10, "spline.txt");
	save(zk, fzk, 10, "puntos.txt");
	printf("\nConjunto de puntos almacenados en el archivo: puntos.txt");
	printf("\nConjunto de puntos del Spline almacenados en el archivo: spline.txt\n");

	free_vector(zk);
	free_vector(fzk);
	free_vector(M);
}