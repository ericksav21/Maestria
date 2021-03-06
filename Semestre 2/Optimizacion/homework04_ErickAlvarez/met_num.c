#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n) {
	d[0] = mat->b[0] * x[0] + mat->c[0] * x[1];
	d[n - 1] = mat->a[n - 1] * x[n - 2] + mat->b[n - 1] * x[n - 1];
	for(int i = 1; i < n - 1; i++) {
		d[i] = mat->a[i] * x[i - 1] + mat->b[i] * x[i] + mat->c[i] * x[i + 1];
	}
}

double get_f(int type, double *x, double *y, double lambda, int n) {
	if(type == 1) {
		return f_1(x);
	}
	else if(type == 2) {
		return f_2(x, n);
	}
	else if(type == 3) {
		return f_3(x);
	}
	else {
		return f_4(x, y, lambda, n);
	}
}

void get_gradient(int type, double *g, double *x, double *y, double lambda, int n) {
	if(type == 1) {
		get_gradient_1(g, x);
	}
	else if(type == 2) {
		get_gradient_2(g, x, n);
	}
	else if(type == 3) {
		get_gradient_3(g, x, n);
	}
	else {
		get_gradient_4(g, x, y, lambda, n);
	}
}

void get_Hessian(int type, double **H, double *x, int n) {
	if(type == 1) {
		get_Hessian_1(H, x);
	}
	else if(type == 3) {
		get_Hessian_3(H, x, n);
	}
}

double compute_alpha_1(double *gradient, double **Hessian, int n, double tol) {
	double *v_aux = create_vector(n, double);
	double aux1 = inner_product(gradient, gradient, n);
	v_aux = mul_mat_vector(Hessian, gradient, v_aux, n, n);
	double aux2 = inner_product(gradient, v_aux, n);

	if(fabs(aux2) < tol) {
		printf("Error al generar el alpha: División entre cero.\n");
		free_vector(v_aux);
		return -1;
	}

	free_vector(v_aux);
	return aux1 / aux2;
}

double compute_alpha_1_3d(double *gradient, MAT3D *Hessian, int n, double tol) {
	double *v_aux = create_vector(n, double);
	double aux1 = inner_product(gradient, gradient, n);
	mul_m_tridiagonal(Hessian, gradient, v_aux, n);
	double aux2 = inner_product(gradient, v_aux, n);

	if(fabs(aux2) < tol) {
		printf("Error al generar el alpha: División entre cero.\n");
		free_vector(v_aux);
		return -1;
	}

	free_vector(v_aux);
	return aux1 / aux2;
}

double compute_alpha_2() {
	//return 0.0001;
	return 0.000505;
}

double compute_alpha_3(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol) {
	double *v_aux = create_vector(n, double);
	double aux = inner_product(gradient, gradient, n);
	double num = aux * last_alpha * last_alpha;
	double den = 2.0 * (f_aprox - f + last_alpha * aux);

	if(fabs(den) < tol) {
		printf("Error al generar el alpha: División entre cero.\n");
		free_vector(v_aux);
		return -1;
	}

	free_vector(v_aux);
	return num / den;
}

/*
	Método principal, descenso por gradiente usando diferentes alphas.
*/
double *gradient_descent(double *init, double *yi, double lambda, int n, int iter, char *alpha_type, double fixed_alpha, int ex_no, double tol_x, double tol_f, double tol_g) {
	//double tol = sqrt(get_EPS());
	//FILE *results;
	//results = fopen("Data_SL.txt", "w");
	double tol_a = pow(get_EPS(), 3.0 / 2.0);
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	int t = 0;

	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *v_aux = create_vector(n, double);
	double *v_scaled = create_vector(n, double);
	double *gradient = create_vector(n, double);
	double **Hessian = create_matrix(n, n, double);
	double last_alpha = 0.001;
	double f_aprox;

	MAT3D *Hessian_3d = create_mat_3d(n);

	double alpha = -1;
	if(strcmp(alpha_type, "StepFijo") == 0) {
		alpha = fixed_alpha;
	}

	while(1) {
		get_gradient(ex_no, gradient, x0, yi, lambda, n);
		if(strcmp(alpha_type, "StepHess") == 0) {
			if(ex_no == 2) {
				get_Hessian_2(Hessian_3d, x0, n);
			}
			else if(ex_no == 4) {
				get_Hessian_4(Hessian_3d, lambda, n);
			}
			else {
				get_Hessian(ex_no, Hessian, x0, n);
			}
		}
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = get_f(ex_no, x0, yi, lambda, n);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		if(strcmp(alpha_type, "StepHess") == 0) {
			if(ex_no == 2 || ex_no == 4) {
				alpha = compute_alpha_1_3d(gradient, Hessian_3d, n, tol_a);
			}
			else {
				alpha = compute_alpha_1(gradient, Hessian, n, tol_a);
			}
			if(alpha < 0) {
				alpha *= -1;
			}
		}
		else if(strcmp(alpha_type, "StepAprox") == 0) {
			v_aux = scale_vect(gradient, v_aux, n, last_alpha);
			x1 = substract_vect(x0, v_aux, x1, n);
			f_aprox = get_f(ex_no, x1, yi, lambda, n);
			alpha = compute_alpha_3(gradient, last_alpha, y, f_aprox, n, tol_a);
			last_alpha = alpha;
		}

		if(alpha == -1) {
			printf("No se indicó correctamente un método de selección del alpha.\n");
			break;
		}
		printf("Alpha: %g\n\n", alpha);

		//Calcular actualización
		v_scaled = scale_vect(gradient, v_scaled, n, alpha);
		x1 = substract_vect(x0, v_scaled, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		double xn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double ggn = get_f(ex_no, x0, yi, lambda, n);
		double gn2 = fabs(get_f(ex_no, x1, yi, lambda, n) - ggn) / max(1.0, fabs(ggn));

		if(xn < tol_x) {
			printf("Xi+1 muy cercano a Xi.\n");
			printf("||Xi+1 - Xi|| / ||Xi|| = %g\n", xn);
			break;
		}
		if(gn2 < tol_f) {
			printf("f(Xi+1) muy cercano a f(Xi).\n");
			printf("|f(Xi+1) - f(Xi)| / |f(Xi)| = %g\n", gn2);
			break;
		}

		t++;
		if(t == iter) {
			printf("Se alcanzó al número de iteraciones.\n");
			break;
		}
		//fprintf(results, "%lf %lf %lf\n", x0[0], x0[1], y);
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
		}

		//Imprimir el resultado de la ejecución en un archivo.
		//fprintf(results, "Iteración: %d, Norma de las x's: %g, Norma del gradiente: %g, Valor de la función: %g\n", t, xn, gn, y);
		printf("\n");
	}

	free_vector(v_aux);
	free_vector(v_scaled);
	free_vector(x1);
	free_vector(gradient);
	free_matrix(Hessian);
	Hessian_3d = free_mat_3d(Hessian_3d);
	free(Hessian_3d);
	//fclose(results);

	return x0;
}

void exec(char *files_name, char *method_name, char *alpha_type, double fixed_alpha, double lambda, int max_iter, double tol_x, double tol_f, double tol_g) {
	int n;
	double *y;
	double *x0;
	double *xk;

	if(strcmp(method_name, "rosembrock_2") == 0) {
		x0 = read_init_point(files_name, &n);
		xk = gradient_descent(x0, y, lambda, n, max_iter, alpha_type, fixed_alpha, 1, tol_x, tol_f, tol_f);
		printf("\nVector resultante (x^*):\n");
		print_vector(xk, n);
	}
	else if(strcmp(method_name, "rosembrock_n") == 0) {
		x0 = read_init_point(files_name, &n);
		xk = gradient_descent(x0, y, lambda, n, max_iter, alpha_type, fixed_alpha, 2, tol_x, tol_f, tol_f);
		printf("\nVector resultante (x^*):\n");
		print_vector(xk, n);
	}
	else if(strcmp(method_name, "wood") == 0) {
		x0 = read_init_point(files_name, &n);
		xk = gradient_descent(x0, y, lambda, n, max_iter, alpha_type, fixed_alpha, 3, tol_x, tol_f, tol_f);
		printf("\nVector resultante (x^*):\n");
		print_vector(xk, n);
	}
	else if(strcmp(method_name, "smoothing") == 0) {
		//Leer y
		//double *xi = create_vector(n, double);
		FILE *file;
		file = fopen(files_name, "r");
		if(!file) {
			printf("No se pudieron leer los y's\n");
			free_vector(x0);
			return;
		}
		fscanf(file, "%d", &n);
		x0 = create_vector(n, double);
		y = create_vector(n, double);
		for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &y[i]);
		}
		for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &x0[i]);
		}
		/*for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &xi[i]);
		}*/
		fclose(file);

		xk = gradient_descent(x0, y, lambda, n, max_iter, alpha_type, fixed_alpha, 4, tol_x, tol_f, tol_f);
		printf("\nVector resultante (x^*):\n");
		print_vector(xk, n);

		free_vector(y);
		//free_vector(xi);
	}
	else {
		printf("Método no identificado.\n");
		return;
	}

	free_vector(x0);
	free_vector(xk);
}
