#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double get_f(double *x, double *y, double lambda, int n) {
	return f_4(x, y, lambda, n);
}

void get_gradient(double *g, double *x, double *y, double lambda, int n) {
	get_gradient_4(g, x, y, lambda, n);
}

double step_aprox(double *gradient, double last_alpha, double f, double f_aprox, int n, double tol) {
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

double backtracking(double *x, double *y, double *gradient, double lambda, double last_alpha, int n) {
	double rho = 0.2;
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
		if(get_f(v_aux2, y, lambda, n) <= get_f(x, y, lambda, n) + (c1 * alpha * bt)) {
			break;
		}
		alpha *= rho;
	}

	free_vector(dk);
	free_vector(v_aux);
	free_vector(v_aux2);
	
	return alpha;
}

double quadratic_interp(double *x, double *y, double *gradient, double lambda, double last_alpha, int n) {
	double *dk = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);

	dk = scale_vect(gradient, dk, n, -1.0);
	double c1 = 1e-4;
	double alpha0 = last_alpha;
	double b = inner_product(gradient, dk, n); //phi prima de cero
	double c = get_f(x, y, lambda, n); //phi de cero
	v_aux = scale_vect(dk, v_aux, n, alpha0);
	v_aux2 = add_vect(x, v_aux, v_aux2, n);

	double phi_a = get_f(v_aux2, y, lambda, n);
	double num = -(alpha0 * alpha0) * b;
	double den = 2.0 * (phi_a - b * alpha0 - c);
	double alpha1 = num / den;

	while(1) {
		v_aux = scale_vect(dk, v_aux, n, alpha1);
		v_aux2 = add_vect(x, v_aux, v_aux2, n);
		double phi_a = get_f(v_aux2, y, lambda, n);
		if(phi_a <= c + c1 * alpha1 * b) {
			break;
		}
		alpha0 = alpha1;
		num = -(alpha0 * alpha0) * b;
		den = 2.0 * (phi_a - b * alpha0 - c);
		alpha1 = num / den;
	}

	free_vector(dk);
	free_vector(v_aux);
	free_vector(v_aux2);

	return alpha1;
}

double cubic_interp(double *x, double *y, double *gradient, double lambda, double last_alpha, int n) {
	double *dk = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);

	double c1 = 1e-4;
	double alpha0 = last_alpha;
	double alpha1 = quadratic_interp(x, y, gradient, lambda, alpha0, n);

	dk = scale_vect(gradient, dk, n, -1.0);
	double c = inner_product(gradient, dk, n); //phi prima de cero
	double d = get_f(x, y, lambda, n); //phi de cero

	//Phi de alpha cero
	v_aux = scale_vect(dk, v_aux, n, alpha0);
	v_aux2 = add_vect(x, v_aux, v_aux2, n);
	double phi_a0 = get_f(v_aux2, y, lambda, n);

	//Phi de alpha uno
	v_aux = scale_vect(dk, v_aux, n, alpha1);
	v_aux2 = add_vect(x, v_aux, v_aux2, n);
	double phi_a1 = get_f(v_aux2, y, lambda, n);

	//Calcular constantes a y b
	double aux = 1.0 / (alpha1 * alpha1 * alpha0 * alpha0 * (alpha1 - alpha0));
	double **mat = create_matrix(2, 2, double);
	double *v1 = create_vector(2, double);
	double *v2 = create_vector(2, double);
	mat[0][0] = aux * (alpha0 * alpha0);
	mat[0][1] = -aux * (alpha1 * alpha1);
	mat[1][0] = -aux * (alpha0 * alpha0 * alpha0);
	mat[1][1] = aux * alpha1 * alpha1 * alpha1;
	v1[0] = phi_a1 - c * alpha1 - d;
	v1[1] = phi_a0 - c * alpha0 - d;

	v2 = mul_mat_vector(mat, v1, v2, 2, 2);
	double a = v2[0];
	double b = v2[1];

	//Algoritmo de interpolación cúbica
	print_matrix(mat, 2, 2);
	printf("\n");
	print_vector(v1, 2);
	double alpha2 = (-b + sqrt(b * b - 3.0 * a * c)) / (3.0 * a);
	while(phi_a1 > d + c1 * alpha1 * c) {
		alpha0 = alpha1;
		alpha1 = alpha2;
		alpha2 = (-b + sqrt(b * b - 3.0 * a * c)) / (3.0 * a);

		v_aux = scale_vect(dk, v_aux, n, alpha1);
		v_aux2 = add_vect(x, v_aux, v_aux2, n);
		phi_a1 = get_f(v_aux2, y, lambda, n);
	}

	free_vector(dk);
	free_vector(v_aux);
	free_vector(v_aux2);
	free_vector(v1);
	free_vector(v2);
	free_matrix(mat);

	return alpha2;
}

/*
	Método principal, descenso por gradiente usando diferentes alphas.
*/
double *gradient_descent(double *init, double *yi, double lambda, int n, int iter, char *alpha_type, double fixed_alpha, double tol_x, double tol_f, double tol_g) {
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
	double last_alpha = 0.001, alpha_bti = 1.0;
	double f_aprox;

	double alpha = -1;
	if(strcmp(alpha_type, "StepFijo") == 0) {
		alpha = fixed_alpha;
	}

	while(1) {
		get_gradient(gradient, x0, yi, lambda, n);
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = get_f(x0, yi, lambda, n);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		if(strcmp(alpha_type, "StepAprox") == 0) {
			v_aux = scale_vect(gradient, v_aux, n, last_alpha);
			x1 = substract_vect(x0, v_aux, x1, n);
			f_aprox = get_f(x1, yi, lambda, n);
			alpha = step_aprox(gradient, last_alpha, y, f_aprox, n, tol_a);
			last_alpha = alpha;
		}
		else if(strcmp(alpha_type, "Backtracking") == 0) {
			alpha = backtracking(x0, yi, gradient, lambda, alpha_bti, n);
		}
		else if(strcmp(alpha_type, "Quadratic") == 0) {
			alpha = quadratic_interp(x0, yi, gradient, lambda, alpha_bti, n);
			alpha_bti = 2.0 * alpha;
		}
		else if(strcmp(alpha_type, "Cubic") == 0) {
			alpha = cubic_interp(x0, yi, gradient, lambda, alpha_bti, n);
			alpha_bti = alpha;
		}
		else {
			printf("No se indicó correctamente un método de selección del alpha.\n");
			break;
		}
		printf("Alpha: %g\n\n", alpha);

		//Calcular actualización
		v_scaled = scale_vect(gradient, v_scaled, n, alpha);
		x1 = substract_vect(x0, v_scaled, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		double xn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double ggn = get_f(x0, yi, lambda, n);
		double gn2 = fabs(get_f(x1, yi, lambda, n) - ggn) / max(1.0, fabs(ggn));

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

	return x0;
}

void exec(char *files_name, char *alpha_type, double fixed_alpha, double lambda, int max_iter, double tol_x, double tol_f, double tol_g) {
	int n;
	double *y;
	double *x0;
	double *xk;

	//Leer y
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
	fclose(file);

	xk = gradient_descent(x0, y, lambda, n, max_iter, alpha_type, fixed_alpha, tol_x, tol_f, tol_f);
	printf("\nVector resultante (x^*):\n");
	print_vector(xk, n);

	free_vector(y);

	free_vector(x0);
	free_vector(xk);
}