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
	return 0.0001;
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

double *gradient_descent(double *init, int n, int iter, int alpha_type) {
	//double tol = sqrt(get_EPS());
	double tol_x = 1e-10;
	double tol_f = 1e-12;
	double tol_g = 1e-6;
	double tol_a = pow(get_EPS(), 3.0 / 2.0);
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	int t = 0;

	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *v_aux = create_vector(n, double);
	double *gradient = create_vector(n, double);
	double **Hessian = create_matrix(n, n, double);
	double last_alpha = 0.001;
	double f_aprox;

	while(1) {
		get_gradient_1(gradient, x0);
		if(alpha_type == 1) {
			get_Hessian_1(Hessian, x0);
		}
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = f_1(x0);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		double alpha = -1;
		if(alpha_type == 1) {
			alpha = compute_alpha_1(gradient, Hessian, n, tol_a);
		}
		else if(alpha_type == 2) {
			alpha = compute_alpha_2();
		}
		else if(alpha_type == 3) {
			v_aux = scale_vect(gradient, v_aux, n, last_alpha);
			x1 = substract_vect(x0, v_aux, x1, n);
			f_aprox = f_1(x1);
			alpha = compute_alpha_3(gradient, last_alpha, y, f_aprox, n, tol_a);
			last_alpha = alpha;
		}

		if(alpha == -1) {
			break;
		}
		printf("Alpha: %g\n\n", alpha);

		//Calcular actualización
		gradient = scale_vect(gradient, gradient, n, alpha);
		x1 = substract_vect(x0, gradient, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		gn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double gn2 = fabs(f_1(x1) - f_1(x0)) / max(1.0, fabs(f_1(x0)));

		if(gn < tol_x) {
			printf("Xi+1 muy cercano a Xi.\n");
			printf("||Xi+1 - Xi|| / ||Xi|| = %g\n", gn);
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
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
			printf("%lf ", x0[i]);
		}
		printf("\n");
	}

	free_vector(v_aux);
	free_vector(x1);
	free_vector(gradient);
	free_matrix(Hessian);

	return x0;
}

double *gradient_descent_2(double *init, int n, int iter, int alpha_type) {
	//double tol = sqrt(get_EPS());
	double tol_x = 1e-10;
	double tol_f = 1e-12;
	double tol_g = 1e-6;
	double tol_a = pow(get_EPS(), 3.0 / 2.0);
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	int t = 0;

	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *v_aux = create_vector(n, double);
	double *gradient = create_vector(n, double);
	double last_alpha = 0.001;
	double f_aprox;

	MAT3D *Hessian_3d = create_mat_3d(n);

	while(1) {
		get_gradient_2(gradient, x0, n);
		if(alpha_type == 1) {
			get_Hessian_2(Hessian_3d, x0, n);
		}
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = f_2(x0, n);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		double alpha = -1;
		if(alpha_type == 1) {
			alpha = compute_alpha_1_3d(gradient, Hessian_3d, n, tol_a);
		}
		else if(alpha_type == 2) {
			alpha = compute_alpha_2();
		}
		else if(alpha_type == 3) {
			v_aux = scale_vect(gradient, v_aux, n, last_alpha);
			x1 = substract_vect(x0, v_aux, x1, n);
			f_aprox = f_2(x1, n);
			alpha = compute_alpha_3(gradient, last_alpha, y, f_aprox, n, tol_a);
			last_alpha = alpha;
		}

		if(alpha == -1) {
			break;
		}
		printf("Alpha: %g\n\n", alpha);

		//Calcular actualización
		gradient = scale_vect(gradient, gradient, n, alpha);
		x1 = substract_vect(x0, gradient, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		gn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double gn2 = fabs(f_2(x1, n) - f_2(x0, n)) / max(1.0, fabs(f_2(x0, n)));

		if(gn < tol_x) {
			printf("Xi+1 muy cercano a Xi.\n");
			printf("||Xi+1 - Xi|| / ||Xi|| = %g\n", gn);
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
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
		}
	}

	free_vector(v_aux);
	free_vector(x1);
	free_vector(gradient);
	Hessian_3d = free_mat_3d(Hessian_3d);
	free(Hessian_3d);

	return x0;
}

double *gradient_descent_3(double *init, int n, int iter, int alpha_type) {
	//double tol = sqrt(get_EPS());
	double tol_x = 1e-10;
	double tol_f = 1e-12;
	double tol_g = 1e-6;
	double tol_a = pow(get_EPS(), 3.0 / 2.0);
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	int t = 0;

	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *v_aux = create_vector(n, double);
	double *gradient = create_vector(n, double);
	double **Hessian = create_matrix(n, n, double);
	double last_alpha = 0.001;
	double f_aprox;

	while(1) {
		get_gradient_3(gradient, x0, n);
		if(alpha_type == 1) {
			get_Hessian_3(Hessian, x0, n);
		}
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = f_3(x0);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		double alpha = -1;
		if(alpha_type == 1) {
			alpha = compute_alpha_1(gradient, Hessian, n, tol_a);
		}
		else if(alpha_type == 2) {
			alpha = compute_alpha_2();
		}
		else if(alpha_type == 3) {
			v_aux = scale_vect(gradient, v_aux, n, last_alpha);
			x1 = substract_vect(x0, v_aux, x1, n);
			f_aprox = f_3(x1);
			alpha = compute_alpha_3(gradient, last_alpha, y, f_aprox, n, tol_a);
			last_alpha = alpha;
		}

		if(alpha == -1) {
			break;
		}
		printf("Alpha: %g\n\n", alpha);

		//Calcular actualización
		gradient = scale_vect(gradient, gradient, n, alpha);
		x1 = substract_vect(x0, gradient, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		gn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double gn2 = fabs(f_3(x1) - f_3(x0)) / max(1.0, fabs(f_3(x0)));

		if(gn < tol_x) {
			printf("Xi+1 muy cercano a Xi.\n");
			printf("||Xi+1 - Xi|| / ||Xi|| = %g\n", gn);
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
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
			printf("%lf ", x0[i]);
		}
		printf("\n");
	}

	free_vector(v_aux);
	free_vector(x1);
	free_vector(gradient);
	free_matrix(Hessian);

	return x0;
}