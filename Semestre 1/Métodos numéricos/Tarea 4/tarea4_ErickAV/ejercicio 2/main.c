#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "reader.h"
#include "matriztridiagonal.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta ./main [Número de nodos].\n");
		return 0;
	}

	int n;
	n = atoi(argv[1]);
	double tol = pow(get_EPS(), 2.0 / 3.0);
	int aa = 0, bb = 5;
	double dx = (double)(bb - aa) / (double)n;
	double k = 0.5;
	double *a, *b, *c, *d, *xi;
	a = create_vector(n + 1, double);
	b = create_vector(n + 1, double);
	c = create_vector(n + 1, double);
	d = create_vector(n + 1, double);
	xi = create_vector(n + 1, double);

	for(int i = 0; i <= n; i++) {
		a[i] = 1.0;
		b[i] = -2.0;
		c[i] = 1.0;
		xi[i] = aa + i * dx;
	}
	xi[n] = bb;
	d[0] = phi(aa);
	d[n] = phi(bb);
	a[0] = a[n] = 0.0;
	b[0] = b[n] = 1.0;
	c[0] = c[n] = 0.0;

	//Calcular el vector independiente
	for(int i = 1; i < n; i++) {
		d[i] = -q(xi[i], k) * pow(dx, 2) / k;
	}
	d[1] -= phi(aa);
	d[n - 1] -= phi(bb);

	MAT3D *mat = create_mat_3d(n - 1);
	mat->a = copy_matrix_1d_d(a + 1, mat->a, n - 1);
	mat->b = copy_matrix_1d_d(b + 1, mat->b, n - 1);
	mat->c = copy_matrix_1d_d(c + 1, mat->c, n - 1);

	/*printf("Matriz (diagonales diferentes de cero):\n");
	print_vector(mat->a + 1, n - 1);
	print_vector(mat->b + 1, n - 1);
	print_vector(mat->c + 1, n - 1);*/
	printf("b:\n");
	print_vector(d + 1, n - 1);
	printf("\nxi:\n");
	print_vector(xi + 1, n - 1);

	double *phi_r = resuelve_m_tridiagonal(mat, d + 1, tol);
	genera_tabla_txt(xi, phi_r, n);

	if(phi_r == NULL) {
		printf("El sistema no tiene solución.\n");
	}
	else {
		printf("\nphi (analítico):\n");
		for(int i = 1; i < n; i++) {
			printf("%lf ", phi(xi[i]));
		}

		printf("\n\nphi (numérico):\n");
		print_vector(phi_r, n - 1);

		printf("\nError: %10.20e\n", get_error(xi + 1, phi_r, n - 1));
	}

	mat = free_mat_3d(mat);
	free(mat);
	free_vector(a);
	free_vector(b);
	free_vector(c);
	free_vector(d);
	free_vector(xi);
	if(phi_r != NULL)
		free_vector(phi_r);

	return 0;
}