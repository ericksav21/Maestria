#include "met_num.h"

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n) {
	d[0] = mat->b[0] * x[0] + mat->c[0] * x[1];
	d[n - 1] = mat->a[n - 1] * x[n - 2] + mat->b[n - 1] * x[n - 1];
	for(int i = 1; i < n - 1; i++) {
		d[i] = mat->a[i] * x[i - 1] + mat->b[i] * x[i] + mat->c[i] * x[i + 1];
	}
}

void get_gradient(double *g, double *x, int n) {
	get_gradient_2(g, x, n);
}

double get_f(double *x, int n) {
	return f_2(x, n);
}

double* PU(double *g, MAT3D *H3D, int n) {
	double *hg = create_vector(n, double);
	mul_m_tridiagonal(H3D, g, hg, n);
	double dk = inner_product(g, g, n);
	double ddk = inner_product(g, hg, n);

	double sc = -(dk / ddk);
	double *res = create_vector(n, double);
	res = scale_vect(g, res, n, sc);

	free_vector(hg);

	return res;
}

double* PB(double *g, MAT3D *H3D, int n) {
	double *gm = create_vector(n, double);
	gm = scale_vect(g, gm, n, -1.0);
	double *res = solve_m_tridiagonal(H3D, gm, 1e-3);

	free_vector(gm);

	return res;
}

double mk(int type, double *x, double *p, double *g, double **H, MAT3D *H3D, int n) {
	double *hp = create_vector(n, double);
	mul_m_tridiagonal(H3D, p, hp, n);

	double ddk = 0.5 * inner_product(p, hp, n);
	double gp = inner_product(g, p, n);
	double fp = get_f(x, n);

	free_vector(hp);

	return fp + gp + ddk;
}