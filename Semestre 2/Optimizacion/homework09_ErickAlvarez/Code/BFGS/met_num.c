#include "met_num.h"

double backtracking(double *x, double *g, double *p, double last_alpha, int n) {
	double rho = 0.5, c1 = 1e-2, c2 = 0.1;
	double alpha = last_alpha;
	double *g_aux = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);

	while(1) {
		v_aux = scale_vect(p, v_aux, n, alpha);
		v_aux2 = add_vect(x, v_aux, v_aux2, n);
		double f_k = rosenbrock(x, n);
		double fa_k = rosenbrock(v_aux2, n);

		get_gradient(g_aux, v_aux2, n);
		double gp = inner_product(g, p, n);
		double gap = inner_product(g_aux, p, n);

		if(fa_k <= f_k + (c1 * alpha * gp)/* && gap >= c2 * gp*/) {
			break;
		}
		alpha *= rho;
		//printf("%g\n", alpha);
	}

	free_vector(g_aux);
	free_vector(v_aux);
	free_vector(v_aux2);
	
	return alpha;
}

void update_H(double **H, double *s, double *y, int n) {
	double **H_n = create_matrix(n, n, double);
	double **ss = create_matrix(n, n, double);
	double **m_aux = create_matrix(n, n, double);
	double **m_t = create_matrix(n, n, double);
	double **m_aux2 = create_matrix(n, n, double);
	double **m_aux3 = create_matrix(n, n, double);

	double ys = inner_product(y, s, n);
	double rho = 1.0 / ys;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			ss[i][j] = rho * s[i] * s[j];
			if(i == j) {
				m_aux[i][j] = 1.0 - rho * s[i] * y[j];
			}
			else {
				m_aux[i][j] = 0.0;
			}
		}
	}
	m_aux2 = mul_mat_mat(m_aux, H, m_aux2, n);
	m_t = transpose_matrix(m_aux, m_t, n, n);
	m_aux3 = mul_mat_mat(m_aux2, m_t, m_aux3, n);
	H = add_mat(m_aux3, ss, H, n, n);

	free_matrix(H_n);
	free_matrix(ss);
	free_matrix(m_aux);
	free_matrix(m_t);
	free_matrix(m_aux2);
	free_matrix(m_aux3);
}

void BFGS(double *x0, double (*func_ptr)(double*, int), void (*grad_ptr)(double*, double*, int), double **H, int n, int iter_max, double tol) {
	int k = 0;
	double *pk = create_vector(n, double);
	double *g = create_vector(n, double);
	double *g1 = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *xk = create_vector(n, double);
	double *xk1 = create_vector(n, double);
	double *sk = create_vector(n, double);
	double *yk = create_vector(n, double);
	double alpha = 2.0;

	for(int i = 0; i < n; i++) {
		xk[i] = x0[i];
	}
	while(1) {
		//Calcular la dirección pk
		grad_ptr(g, xk, n);
		double g_n = norm_2(g, n);
		if(g_n <= tol) {
			printf("Gradiente de la función menor que la tolerancia: %g.\n", g_n);
			break;
		}

		pk = mul_mat_vector(H, g, pk, n, n);
		pk = scale_vect(pk, pk, n, -1.0);

		//Calcular el nuevo x
		double alpha_opt = backtracking(xk, g, pk, alpha, n);
		v_aux = scale_vect(pk, v_aux, n, alpha_opt);
		xk1 = add_vect(xk, v_aux, xk1, n);
		grad_ptr(g1, xk1, n);
		sk = substract_vect(xk1, xk, sk, n);
		yk = substract_vect(g1, g, yk, n);
		update_H(H, sk, yk, n);
		for(int i = 0; i < n; i++) {
			xk[i] = xk1[i];
		}

		k++;
		printf("Iteración %d\nNorma del gradiente: %g\nf(xk): %g\nXk:\n", k, g_n, func_ptr(xk, n));
		print_vector(xk, n);
		printf("\n");

		if(k == iter_max) {
			printf("Número de iteraciones alcanzado.\n");
			break;
		}
	}

	free_vector(pk);
	free_vector(g);
	free_vector(g1);
	free_vector(v_aux);
	free_vector(xk);
	free_vector(xk1);
	free_vector(sk);
	free_vector(yk);
}