#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double f(double *x) {
	return 100.0 * pow(x[1] - x[0] * x[0], 2) + pow(1.0 - x[0], 2);
}

void get_gradient(double *g, double *x) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[1] = 200.0 * (x[1] - x[0] * x[0]);
}

void get_Hessian(double **H, double *x) {
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[0][1] = H[1][0] = -400.0 * x[0];
	H[1][1] = 200.0;
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

double compute_alpha_2() {
	return 0.00000001;
}

double *gradient_descent(double *init, int n, int iter, int alpha_type) {
	//double tol = sqrt(get_EPS());
	double tol_x = 0.00001;
	double tol_f = 0.0000001;
	double tol_g = 0.00001;
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	int t = 0;

	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}

	double *v_aux = create_vector(n, double);
	double *gradient = create_vector(n, double);
	double **Hessian = create_matrix(n, n, double);

	while(1) {
		get_gradient(gradient, x0);
		get_Hessian(Hessian, x0);
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = f(x0);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		double alpha = 0.0;
		if(alpha_type == 1) {
			alpha = compute_alpha_1(gradient, Hessian, n, tol_x);
		}
		else if(alpha_type == 2) {
			alpha = compute_alpha_2();
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
		double gn2 = fabs(f(x1) - f(x0)) / max(1.0, fabs(f(x0)));

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
	free_matrix(Hessian);

	return x0;
}