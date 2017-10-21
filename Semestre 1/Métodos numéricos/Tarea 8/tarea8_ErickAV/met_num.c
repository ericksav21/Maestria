#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}


double *conjugate_gradient(double **A, double *x0, double *b, int n, int *iter, double tol) {
	double *r = create_vector(n, double);
	double *aux_1 = create_vector(n, double);
	double *p = create_vector(n, double);

	aux_1 = mul_mat_vector(A, x0, aux_1, n, n);
	r = substract_vect(aux_1, b, r, n);
	p = scale_vect(r, p, n, -1);

	int k = 0;
	while(k < 2 * n && norm_2(r, n) > tol) {
		//printf("Norma: %g\n", norm_2(r, n));
		double *w = create_vector(n, double);
		double *x1 = create_vector(n, double);
		double *r_1 = create_vector(n, double);
		double *p_1 = create_vector(n, double);
		double *p_s = create_vector(n, double);
		double *p_s2 = create_vector(n, double);
		double *w_s = create_vector(n, double);

		w = mul_mat_vector(A, p, w, n, n);
		double alpha = inner_product(r, r, n) / inner_product(p, w, n);
		p_s = scale_vect(p, p_s, n, alpha);
		w_s = scale_vect(w, w_s, n, alpha);

		x1 = add_vect(x0, p_s, x1, n);
		r_1 = add_vect(r, w_s, r_1, n);
		double beta = inner_product(r_1, r_1, n) / inner_product(r, r, n);
		p_s2 = scale_vect(p, p_s2, n, beta);
		p_1 = substract_vect(p_s2, r_1, p_1, n);

		r = copy_vector(r_1, r, n);
		p = copy_vector(p_1, p, n);
		x0 = copy_vector(x1, x0, n);
		k++;

		free_vector(w);
		free_vector(x1);
		free_vector(r_1);
		free_vector(p_1);
		free_vector(p_s);
		free_vector(p_s2);
		free_vector(w_s);
	}
	*iter = k;

	free_vector(aux_1);
	free_vector(p);
	free_vector(r);

	return x0;
}