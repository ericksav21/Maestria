#include "met_num.h"

double get_EPS() {
	double Eps = 1.0;

	while (1.0 + Eps / 2.0 != 1.0)
		Eps /= 2.0;

	return Eps;
}

double get_f(double *x, char *func_type, int n) {
	if(strcmp(func_type, "Rosenbrock") == 0) {
		return f_ros(x, n);
	}
	else if(strcmp(func_type, "Wood") == 0) {
		return f_wood(x);
	}
	else if(strcmp(func_type, "Convex1") == 0) {
		return f_cvx1(x, n);
	}
	else {
		return f_cvx2(x, n);
	}
}

void get_gradient(double *g, double *x, char *func_type, int n) {
	if(strcmp(func_type, "Rosenbrock") == 0) {
		get_gradient_ros(g, x, n);
	}
	else if(strcmp(func_type, "Wood") == 0) {
		get_gradient_wood(g, x, n);
	}
	else if(strcmp(func_type, "Convex1") == 0) {
		get_gradient_cvx1(g, x, n);
	}
	else {
		get_gradient_cvx2(g, x, n);
	}
}

void get_Hessian(double **H, double *x, char *func_type, int n) {
	if(strcmp(func_type, "Rosenbrock") == 0) {
		get_Hessian_ros(H, x, n);
	}
	else if(strcmp(func_type, "Wood") == 0) {
		get_Hessian_wood(H, x, n);
	}
	else if(strcmp(func_type, "Convex1") == 0) {
		get_Hessian_cvx1(H, x, n);
	}
	else {
		get_Hessian_cvx2(H, x, n);
	}
}

double backtracking(double *x, double *g, double *p, char *func_type, double alpha_0, int n) {
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
		double f_k = get_f(x, func_type, n);
		double fa_k = get_f(v_aux2, func_type, n);
		
		get_gradient(g_aux, v_aux2, func_type, n);
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

double Fletcher_Reeves(double *lst_gradient, double *gradient, int n) {
	double num = inner_product(gradient, gradient, n);
	double den = inner_product(lst_gradient, lst_gradient, n);

	return num / den;
}

double Polak_Ribiere(double *lst_gradient, double *gradient, int n) {
	double *v_aux = create_vector(n, double);
	v_aux = substract_vect(gradient, lst_gradient, v_aux, n);
	double num = inner_product(gradient, v_aux, n);
	double den = inner_product(lst_gradient, lst_gradient, n);

	free_vector(v_aux);

	return max(0.0, num / den);
}

double Hestnes_Stiefel(double *lst_gradient, double *gradient, double *d, int n) {
	double *v_aux = create_vector(n, double);
	v_aux = substract_vect(gradient, lst_gradient, v_aux, n);
	double num = inner_product(gradient, v_aux, n);
	double den = inner_product(v_aux, d, n);

	free_vector(v_aux);

	return num / den;
}

/* Beta de Fletcher-Reeves y Polak-Ribiere */
double FR_PR(double *lst_gradient, double *gradient, int n) {
	double fr = Fletcher_Reeves(lst_gradient, gradient, n);
	double pr = Polak_Ribiere(lst_gradient, gradient, n);

	if(pr < -fr) {
		return fr;
	}
	else if(fabs(pr) <= fr) {
		return pr;
	}
	else if(pr > fr) {
		return fr;
	}
	else {
		printf("No se encontró la Beta adecuada.\n");
		return pr;
	}
}

double get_Beta(double *lst_gradient, double *gradient, double *d, char *beta_type, int n) {
	if(strcmp(beta_type, "Fletcher") == 0) {
		return Fletcher_Reeves(lst_gradient, gradient, n);
	}
	else if(strcmp(beta_type, "Polak") == 0) {
		return Polak_Ribiere(lst_gradient, gradient, n);
	}
	else if(strcmp(beta_type, "Hestnes") == 0) {
		return Hestnes_Stiefel(lst_gradient, gradient, d, n);
	}
	else if(strcmp(beta_type, "FR_PR") == 0) {
		return FR_PR(lst_gradient, gradient, n);
	}
	else {
		printf("Error. No se reconoció el tipo de Beta: %s.\n", beta_type);
		//En caso de no cumplirse los casos anteriores se regresa cero, esto puede causar
		//problemas por lo que hay que revisar muy bien el proceso de GC en la función.
		return 0.0;
	}
}

double* conjugate_gradient(double *init, char *beta_type, char *func_type, int n, int iter, double tol_g, double tol_x, double tol_f) {
	FILE *f_out = fopen("results.txt", "w");

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

	get_gradient(gradient, x0, func_type, n);
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
		double alpha_k = backtracking(x0, gradient, d, func_type, alpha_init, n);

		v_aux = scale_vect(d, v_aux, n, alpha_k);
		x1 = add_vect(x0, v_aux, x1, n);
		
		//Verificar diferencia en x's
		double xmn = norm_2(v_aux, n);
		double xn = norm_2(x0, n);
		double xn_dif = xmn / max(1.0, xn);
		if(xn_dif < tol_x) {
			printf("Norma de las x's menor que la tolerancia: %g\n", xn_dif);
			break;
		}

		//Verificar diferencia en f's
		double fn1 = get_f(x1, func_type, n);
		double fn = get_f(x0, func_type, n);
		fprintf(f_out, "%d %g %g %g\n", k + 1, fn, gn, norm_2(d, n));
		double fn_dif = fabs(fn1 - fn) / max(1.0, fabs(fn));
		if(fn_dif < tol_f) {
			printf("Norma de las funciones menor que la tolerancia: %g\n", fn_dif);
			break;
		}
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
			lst_gradient[i] = gradient[i];
		}
		get_gradient(gradient, x0, func_type, n);
		
		//Generar la beta
		double beta = get_Beta(lst_gradient, gradient, d, beta_type, n);

		//Generar la nueva dirección Q-conjugada
		v_aux = scale_vect(gradient, v_aux, n, -1.0);
		v_aux2 = scale_vect(d, v_aux2, n, beta);
		d = add_vect(v_aux, v_aux2, d, n);
		k++;

		//Imprimir datos
		printf("Iteración %d:\nAlpha: %g\n||g_k||:%g\n||xk+1 - xk||:%g\n|f_k+1 - f_k|:%g\n\n", k, alpha_k, gn, xn_dif, fn_dif);
		if(k == iter) {
			printf("Se alcanzó el límite de iteraciones.\n");
			break;
		}
	}

	printf("Gradiente conjutado terminado en %d iteraciones.\n", k + 1);

	free_vector(x1);
	free_vector(gradient);
	free_vector(lst_gradient);
	free_vector(d);
	free_vector(w);
	free_vector(v_aux);
	free_vector(v_aux2);
	fclose(f_out);

	return x0;
}

void exec(char *files_name, char *beta_type, char *func_type, int iter, double tol_g, double tol_x, double tol_f) {
	double *x0;
	int n;

	FILE *file;
	file = fopen(files_name, "r");

	if(file) {
		int nn;
		fscanf(file, "%d", &n);
		x0 = create_vector(n, double);

		double aux;
		for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &aux);
			x0[i] = aux;
		}

		double *xk = conjugate_gradient(x0, beta_type, func_type, n, iter, tol_g, tol_x, tol_f);

		printf("\nVector resultante:\n");
		print_vector(xk, n);
		printf("\nValor de la función en dicho punto: %g\n", get_f(xk, func_type, n));

		free_vector(xk);
		fclose(file);
		printf("Archivo de texto generado.\n");

		free_vector(x0);
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return;
	}
}