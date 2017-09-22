#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "matriztridiagonal.h"

int main(int argc, char **argv) {
	/*if(argc < 4) {
		printf("Error. Ejecuta ./main [Matriz tridiagonal(1)] [Matriz tridiagonal(2)] [Matriz tridiagonal(3)] [Vector independiente].\n");
		return 0;
	}

	char tridiagonal_f1[30], tridiagonal_f2[30], tridiagonal_f3[30], indep_f[30];
	strcpy(tridiagonal_f1, argv[1]);
	strcpy(tridiagonal_f2, argv[2]);
	strcpy(tridiagonal_f3, argv[3]);
	strcpy(indep_f, argv[4]);

	int n1, n2, n3, nb;
	double *a = read_vector(tridiagonal_f1, &n1);
	double *b = read_vector(tridiagonal_f2, &n2);
	double *c = read_vector(tridiagonal_f3, &n3);
	double *d = read_vector(indep_f, &nb);*/
	double tol = pow(get_EPS(), 2.0/3.0);
	int n = 12;
	double *a, *b, *c, *d, *x, *s;
	a = create_vector(n, double);
	b = create_vector(n, double);
	c = create_vector(n, double);
	d = create_vector(n, double);
	x = create_vector(n, double);
	s = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		a[i] = -1;
		b[i] = 0;
		c[i] = 1;
		x[i] = (double)i / (double)(n - 1);
		s[i] = exp(pow(x[i], 2));
	}
	a[0] = 0;
	b[0] = -1;
	a[n - 1] = 0;
	b[n - 1] = 1;
	c[n - 1] = 0;

	//Calcular el vector independiente
	d[0] = 0;
	d[n - 1] = M_E;
	for(int i = 1; i < n - 1; i++) {
		d[i] = (4.0 * x[i] * s[i]) / (double)(n - 1);
	}

	MAT3D *mat = create_mat_3d(n);
	mat->a = copy_matrix_1d_d(a, n);
	mat->b = copy_matrix_1d_d(b, n);
	mat->c = copy_matrix_1d_d(c, n);

	printf("Matriz (diagonales diferentes de cero):\n");
	print_vector(mat->a, n);
	print_vector(mat->b, n);
	print_vector(mat->c, n);
	printf("\nb:\n");
	print_vector(d, n);
	printf("\n");

	double *phi = resuelve_m_tridiagonal(mat, d, tol);

	if(x == NULL) {
		printf("El sistema no tiene solución.\n");
	}
	else {
		printf("phi:\n");
		print_vector(phi, n);
		printf("\ns:\n");
		print_vector(s, n);

		printf("\nError: %10.20e\n", get_error(phi, s, n));
	}

	mat = free_mat_3d(mat);
	free(mat);
	free_vector(a);
	free_vector(b);
	free_vector(c);
	free_vector(d);
	free_vector(x);
	free_vector(s);
	if(phi != NULL)
		free_vector(phi);

	return 0;
}