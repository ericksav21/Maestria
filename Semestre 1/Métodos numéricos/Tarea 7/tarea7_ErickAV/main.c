#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "met_num.h"

int main(int argc, char **argv) {
	int m = 50;
	double tol = 1e-7;
	double *px = create_vector(m, double);
	double *py = create_vector(m, double);
	double **A = create_matrix(3, 3, double);
	double **L = create_matrix(3, 3, double);
	double **U = create_matrix(3, 3, double);
	double *x = create_vector(3, double);
	double *y = create_vector(3, double);
	double *v_aux = create_vector(3, double);
	double *sol = create_vector(m, double);

	for(int i = 0; i < m; i++) {
		px[i] = ((double)i * M_PI) / (double)(m - 1);
		py[i] = sin(px[i]);
	}

	initialize(px, py, A, y, m);
	factorize_LU(A, &L, &U, 3, tol);
	v_aux = solve_mlower(L, y, 3, 3, tol);
	x = solve_mupper(U, v_aux, 3, 3, tol);

	printf("a: %lf, b: %lf, c: %lf\n", x[0], x[1], x[2]);
	printf("Error: %g\n", get_err(A, x, y, 3, 3));

	for(int i = 0; i < m; i++)
		sol[i] = f(px[i], x[0], x[1], x[2]);

	//Imprimir los resultados en un archivo
	print_data(px, py, sol, m, "tabla.txt");

	free_vector(px);
	free_vector(py);
	free_vector(x);
	free_vector(y);
	free_vector(v_aux);
	free_vector(sol);
	free_matrix(A);
	free_matrix(L);
	free_matrix(U);

	return 0;
}