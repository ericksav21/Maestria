#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double f(double x1, double x2) {
	return 100.0 * pow(x2 - x1 * x1, 2) + pow(1.0 - x1, 2);
}

double *get_gradient(double x1, double x2) {
	double *res = create_vector(2, double);
	res[0] = -400.0 * x1 * (x2 - x1 * x1) - 2.0 * (1.0 - x1);
	res[1] = 200.0 * (x2 - x1 * x1);

	return res;
}

double **get_Hessian(double x1, double x2) {
	double **res = create_matrix(2, 2, double);
	res[0][0] = -400.0 * (x2 - 3.0 * x1 * x1) + 2.0;
	res[0][1] = res[1][0] = -400.0 x1;
	res[1][1] = 200.0;

	return res;
}

double *gradient_descent(int iter) {
	double *x0 = create_vector(2, double);
	x0[0] = -1.2;
	x0[1] = 1.0;
	double tol = get_EPS();
	int t = 0;

	while(1) {
		double *gradient = get_gradient(x0[0], x0[1]);
		double **Hessian = get_Hessian(x0[0], x0[1]);

		//Evaluar
		double y = f(x[0], x[1]);
		printf("%lf\n", y);
		double nn = norm_2(gradient, 2);
		if(nn < tol) {
			printf("Gradiente aprox. cero.\n");
			free_vector(gradient);
			free_matrix(Hessian);
			break;
		}

		//Calcular alpha
		double aux1 = inner_product(gradient, gradient, 2);
		double *v_aux = create_vector(2, double);
		v_aux = mul_mat_vector(Hessian, gradient, v_aux, 2, 2);
		double aux2 = inner_product(gradient, v_aux, 2);
		if(fabs(aux2) < tol) {
			printf("Error al generar el alpha: División entre cero.\n");
			free_vector(v_aux);
			free_vector(gradient);
			free_matrix(Hessian);
			break;
		}
		double alpha = aux1 / aux2;

		//Calcular actualización
		double *x1 = create_vector(2, double);
		

		free_vector(v_aux);
		free_vector(gradient);
		free_matrix(Hessian);
	}
}