#include "met_num.h"

double Fletcher_Reeves(double *lst_gradient, double *gradient, int n) {
	double num = inner_product(gradient, gradient, n);
	double den = inner_product(lst_gradient, lst_gradient, n);

	return num / den;
}

double backtracking(double *x, double *g, double *p, double alpha_0, double mu, double dx, int n, int m) {
	//Rho de escalamiento para el alpha, c1 y c2 para las condiciones de Wolfe
	double rho = 0.5, c1 = 1e-2, c2 = 0.9;
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	double *g_aux = create_vector(n, double);
	//Máximo número de iteraciones. Por defecto se usan las condiciones fuertes de Wolfe
	int iter = 50, use_strong_wolfe = 1;
	double alpha_k = alpha_0;
	int k = 0;
	while(1) {
		v_aux = scale_vect(p, v_aux, n, alpha_k);
		v_aux2 = add_vect(x, v_aux, v_aux2, n);
		double f_k = Q(x, mu, n, m);
		double fa_k = Q(v_aux2, mu, n, m);
		
		grad_aprox(v_aux2, g_aux, mu, dx, n, m);
		double gp = inner_product(g, p, n);
		double gap = inner_product(g_aux, p, n);

		if(use_strong_wolfe) {
			if(fa_k <= f_k + (c1 * alpha_k * gp) && fabs(gap) <= c2 * fabs(gp) || k == iter) {
				break;
			}
		}
		else {
			//Se usan las condiciones de Armijo
			if(fa_k <= f_k + (c1 * alpha_k * gp) || k == iter) {
				break;
			}
		}

		alpha_k *= rho;
		k++;
	}

	free_vector(v_aux);
	free_vector(v_aux2);
	free_vector(g_aux);

	return max(alpha_k, 1e-6);
}

double* conjugate_gradient(double *init, int n, int m, int iter, double tol_g, double mu, double dx) {

	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *gradient = create_vector(n, double);
	double *lst_gradient = create_vector(n, double);
	double *d = create_vector(n, double);
	double *w = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);

	grad_aprox(x0, gradient, mu, dx, n, m);
	d = scale_vect(gradient, d, n, -1.0);
	//Alpha inicial en backtracking
	double alpha_init = 0.5;
	int k = 0;
	while(1) {
		double gn = norm_2(gradient, n);
		if(gn < tol_g) {
			printf("Norma del gradiente menor que la tolerancia: %g\n", gn);
			break;
		}
		double alpha_k = backtracking(x0, gradient, d, alpha_init, mu, dx, n, m);

		v_aux = scale_vect(d, v_aux, n, alpha_k);
		x1 = add_vect(x0, v_aux, x1, n);
		
		//Verificar diferencia en x's
		double xmn = norm_2(v_aux, n);
		double xn = norm_2(x0, n);
		double xn_dif = xmn / max(1.0, xn);
		/*if(xn_dif < tol_x) {
			printf("Norma de las x's menor que la tolerancia: %g\n", xn_dif);
			break;
		}*/

		//Verificar diferencia en f's
		double fn1 = Q(x1, mu, n, m);
		double fn = Q(x0, mu, n, m);
		double fn_dif = fabs(fn1 - fn) / max(1.0, fabs(fn));
		double fk = get_f(x0, n);
		/*if(fn_dif < tol_f) {
			printf("Norma de las funciones menor que la tolerancia: %g\n", fn_dif);
			break;
		}*/
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
			lst_gradient[i] = gradient[i];
		}
		grad_aprox(x0, gradient, mu, dx, n, m);
		
		//Generar la beta
		double beta = Fletcher_Reeves(lst_gradient, gradient, n);

		//Generar la nueva dirección Q-conjugada
		v_aux = scale_vect(gradient, v_aux, n, -1.0);
		v_aux2 = scale_vect(d, v_aux2, n, beta);
		d = add_vect(v_aux, v_aux2, d, n);
		k++;

		//Imprimir datos
		printf("Iteración %d:\nAlpha: %g\n||g_k||: %g\n||xk+1 - xk||: %g\n|f_k+1 - f_k|: %g\nf_k: %g\n\n", k, alpha_k, gn, xn_dif, fn_dif, -fk);
		if(k == iter) {
			printf("Se alcanzó el límite de iteraciones.\n");
			break;
		}
	}

	printf("Gradiente conjugado terminado en %d iteraciones.\n\n", k + 1);

	free_vector(x1);
	free_vector(gradient);
	free_vector(lst_gradient);
	free_vector(d);
	free_vector(w);
	free_vector(v_aux);
	free_vector(v_aux2);

	return x0;
}

void QP(double *init, int n, int m, double tao_k, double tao, double mu, double dx) {
	double *xk = create_vector(n, double);
	double *h = create_vector(m, double);
	double *h_aux = create_vector(m, double);

	double mu_factor = 3.0;
	int max_iter = 10000;
	for(int i = 0; i < n; i++) {
		xk[i] = init[i];
	}
	int i = 1;
	while(1) {
		printf("Valor de la función: %g\n", get_f(xk, n));
		double *xk1 = conjugate_gradient(xk, n, m, max_iter, tao_k, mu, dx);
		for(int i = 0; i < n; i++) {
			xk[i] = xk1[i];
		}
		free_vector(xk1);
		get_h(xk, h, m);
		/*for(int i = 0; i < m; i++) {
			h_aux[i] = max(0.0, h[i]);
		}
		double p = inner_product(h_aux, h_aux, m);*/
		double p = inner_product(h, h, m);
		double f_eval = Q(xk, mu, n, m);

		if(p < tao) {
			printf("Algoritmo de penalización cuadrática terminado: %g.\n", p);
			break;
		}
		i++;
		mu *= mu_factor;
		tao_k = 1.0 / (double)i;
	}

	printf("Número de iteraciones realizadas: %d\n\n", i);
	printf("Vector resultante:\n");
	print_vector(xk, n);
	printf("\nValor de la función f(x): %g\n", -get_f(xk, n));
	get_h(xk, h, m);
	for(int j = 0; j < m; j++) {
		printf("g(x)_%d: %g\n", (j + 1), h[j] * h[j]);
	}

	free_vector(xk);
	free_vector(h);
}