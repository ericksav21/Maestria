#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double get_f(double **x, double *y, double *beta, int m, int n) {
	double *xi = create_vector(n, double);
	double res = 0.0;
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			xi[j] = x[i][j];
		}

		double aux1 = 0.0, pi = 0.0, ex = 0.0;
		aux1 = inner_product(xi, beta, n);
		ex = exp(-aux1);
		pi = 1.0 / (1.0 + ex);

		res += (y[i] * log(pi)) + (1.0 - y[i]) * log(1.0 - pi);
	}

	free_vector(xi);
	return (-1.0) * res;
}

void get_gradient(double *g, double **x, double *y, double *beta, int m, int n) {
	double *xi = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		g[i] = 0.0;
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			xi[j] = x[i][j];
		}

		double aux1 = 0.0, pi = 0.0, ex = 0.0;
		aux1 = inner_product(xi, beta, n);
		ex = exp(-aux1);
		pi = 1.0 / (1.0 + ex);

		for(int j = 0; j < n; j++) {
			g[j] -= ((pi * ex - 1.0 + y[i]) * xi[j]);
		}
	}

	free_vector(xi);
}

double backtracking(double **x, double *y, double *beta, double *gradient, double last_alpha, int m, int n) {
	double rho = 0.2;
	double c1 = 1e-4;
	double alpha = last_alpha;
	//double *dk = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	//dk = scale_vect(gradient, dk, n, -1.0);
	double bt = inner_product(gradient, gradient, n);
	double fx = get_f(x, y, beta, m, n);

	while(1) {
		v_aux = scale_vect(gradient, v_aux, n, alpha);
		v_aux2 = substract_vect(beta, v_aux, v_aux2, n);
		if(get_f(x, y, v_aux2, m, n) <= (fx - (c1 * alpha * bt))) {
			break;
		}
		alpha *= rho;
	}

	//free_vector(dk);
	free_vector(v_aux);
	free_vector(v_aux2);
	
	return alpha;
}

/*
	Método principal, descenso por gradiente usando diferentes alphas.
*/
//Se asume que los xi ya tienen un 1 añadido
double *gradient_descent(double *init, double **xi, double *yi, int m, int n, int iter, char *alpha_type, double tol_x, double tol_f, double tol_g) {
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
	double last_alpha = 0.001, alpha_bti = 2.0;
	double f_aprox;

	double alpha = -1;

	while(1) {
		get_gradient(gradient, xi, yi, x0, m, n);
		printf("Iteración: %d\n", t + 1);

		//Evaluar
		double y = get_f(xi, yi, x0, m, n);
		printf("f(x) = %g\n", y);
		double gn = norm_2(gradient, n);
		printf("Norma del gradiente: %g\n", gn);
		if(gn < tol_g) {
			printf("Gradiente aprox. a cero.\n");
			break;
		}

		//Calcular alpha
		if(strcmp(alpha_type, "Backtracking") == 0) {
			alpha = backtracking(xi, yi, x0, gradient, alpha_bti, m, n);
			alpha_bti = 2.0 * alpha;
		}
		else if(strcmp(alpha_type, "Fixed") == 0) {
			alpha = 0.00005;
		}
		else {
			printf("No se indicó correctamente un método de selección del alpha.\n");
			break;
		}
		printf("Alpha: %g\n", alpha);

		//Calcular actualización
		v_scaled = scale_vect(gradient, v_scaled, n, alpha);
		x1 = substract_vect(x0, v_scaled, x1, n);
		v_aux = substract_vect(x0, x1, v_aux, n);

		double xn = norm_2(v_aux, n) / max(1.0, norm_2(x0, n));
		double ggn = y;
		double gn2 = fabs(get_f(xi, yi, x1, m, n) - ggn) / max(1.0, fabs(ggn));
		printf("|f(xi+1) - f(xi)| / |f(xi)| = %g\n\n", gn2);

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
		printf("\n");
	}

	free_vector(v_aux);
	free_vector(v_scaled);
	free_vector(x1);
	free_vector(gradient);

	return x0;
}

void make_test(char *test, double *beta, int n1, int n2, int n) {
	//Obtener los datos de prueba
	char tfn_x[30], tfn_y[30];
	sprintf(tfn_x, "%sX.csv", test);
	sprintf(tfn_y, "%sY.csv", test);

	int m;
	double **test_x = create_matrix(13000, 785, double);
	double *test_y = create_vector(13000, double);
	printf("Leyendo datos de prueba...\n");
	read_files(tfn_x, tfn_y, test_x, test_y, n1, n2, &m);
	printf("Número de datos de prueba: %d\n", m);
	for(int i = 0; i < m; i++) {
		test_x[i][784] = 1.0;
		if((int)test_y[i] == n1) {
			test_y[i] = 0.0;
		}
		else {
			test_y[i] = 1.0;
		}
	}

	double err = 0.0;
	double *xi = create_vector(n, double);
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			xi[j] = test_x[i][j];
		}
		double aux1 = 0.0, pi = 0.0, ex = 0.0;
		aux1 = inner_product(xi, beta, n);
		ex = exp(-aux1);
		pi = 1.0 / (1.0 + ex);

		double ind = 0.0;
		if(pi > 0.5) {
			ind = 1.0;
		}
		err += fabs(ind - test_y[i]);
	}
	printf("Número de equivocaciones: %lf\n", err);
	err /= m;
	printf("Error medio: %g\n", err);

	free_matrix(test_x);
	free_vector(test_y);
	free_vector(xi);
}

void exec(char *train, char *test, int max_iter, double tol_x, double tol_f, double tol_g, int n1, int n2, int ts) {
	double **train_x = create_matrix(13000, 784, double);
	double *train_y = create_vector(13000, double);
	char trfn_x[30], trfn_y[30];
	sprintf(trfn_x, "%sX.csv", train);
	sprintf(trfn_y, "%sY.csv", train);

	int m;
	//int n1 = 1, n2 = 8;
	printf("Leyendo los datos...\n");
	read_files(trfn_x, trfn_y, train_x, train_y, n1, n2, &m);

	//Tomar un subconjunto de los datos
	//int ts = 8000;
	int ss = (m < ts ? m : ts);
	double **strain_x = create_matrix(ss, 785, double);
	double *strain_y = create_vector(ss, double);
	printf("Se completó la lectura de los datos, se tomará un subconjunto de la misma.\n");
	for(int i = 0; i < ss; i++) {
		for(int j = 0; j < 784; j++) {
			strain_x[i][j] = train_x[i][j];
		}
		strain_x[i][784] = 1.0;
		if((int)train_y[i] == n1) {
			strain_y[i] = 0.0;
		}
		else {
			strain_y[i] = 1.0;
		}
	}

	free_matrix(train_x);
	free_vector(train_y);

	int n = 785;
	double *beta = create_vector(n, double);
	double *betak;
	for(int i = 0; i < n; i++) {
		beta[i] = 0.0;
	}

	char alpha_type[] = "Backtracking";
	printf("Entrenando...\n");
	betak = gradient_descent(beta, strain_x, strain_y, ss, n, max_iter, alpha_type, tol_x, tol_f, tol_g);
	printf("\nResultante:\n");
	for(int i = 0; i < n; i++) {
		printf("%lf ", betak[i]);
	}
	printf("\n");

	make_test(test, betak, n1, n2, n);

	free_matrix(strain_x);
	free_vector(strain_y);
	free_vector(beta);
	free_vector(betak);
}