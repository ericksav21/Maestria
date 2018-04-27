#include "met_num.h"

double backtracking(double *x, double *gradient, double last_alpha, int n) {
	double rho = 0.5;
	double c1 = 1e-4;
	double alpha = last_alpha;
	double *dk = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	dk = scale_vect(gradient, dk, n, -1.0);
	double bt = inner_product(gradient, dk, n);

	while(1) {
		v_aux = scale_vect(dk, v_aux, n, alpha);
		v_aux2 = add_vect(x, v_aux, v_aux2, n);
		if(rosenbrock(v_aux2, n) <= rosenbrock(x, n)) {
			break;
		}
		alpha *= rho;
	}

	free_vector(dk);
	free_vector(v_aux);
	free_vector(v_aux2);
	
	return alpha;
}

void BFGS(double *x0, double (*func_ptr)(double*, int), void (*grad_ptr)(double*, double*, int), double **H, int n, int iter_max, double tol) {
	int k = 0;
	double *pk = create_vector(n, double);
	double *g = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *xk = create_vector(n, double);
	double *xk1 = create_vector(n, double);
	double alpha = 1.0;

	for(int i = 0; i < n; i++) {
		xk[i] = x0[i];
	}
	while(true) {
		//Calcular la dirección pk
		grad_ptr(g, xk, n);
		pk = mul_mat_vector(H, g, pk, n, n);
		pk = scale_vect(pk, pk, n, -1.0);

		//Calcular el nuevo x
		double alpha_opt = backtracking(xk, g, alpha, n);
		v_aux = scale_vect(pk, v_aux, n, alpha_opt);
		xk1 = add_vect(xk, v_aux, xk1, n);
	}

	free_vector(pk);
	free_vector(g);
	free_vector(v_aux);
	free_vector(xk);
	free_vector(xk1);
}