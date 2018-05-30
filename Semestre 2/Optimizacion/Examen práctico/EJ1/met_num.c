#include "met_num.h"

void LM(double *x0, double *d_x, double *d_y, double *theta, double d4, double *sigma, int n, int m,
	void (*f_ptr)(double*, double*, double*, double*, double, double*, double*, int, int),
	void (*J_ptr)(double*, double*, double*, double*, double, double*, double**J, int, int, double),
	double v, int iter_max, double tol, double h) {

	double *x = create_vector(n, double);
	double *x1 = create_vector(n, double);
	double *R = create_vector(m, double);
	double *R1 = create_vector(m, double);
	double *v_auxn = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		x[i] = x0[i];
	}
	double **J = create_matrix(m, n, double);
	double **JT = create_matrix(n, m, double);
	double **JJT = create_matrix(n, n, double);

	//Calcular J_0
	J_ptr(d_x, d_y, x, theta, d4, sigma, J, n, m, h);
	JT = transpose_matrix(J, JT, m, n);
	JJT = mul_mat_mat(JT, J, JJT, n, m);
	double lambda = -10.0;
	for(int i = 0; i < n; i++) {
		lambda = max(lambda, JJT[i][i]);
	}
	int k = 0;
	while(1) {
		f_ptr(d_x, d_y, x, theta, d4, sigma, R, n, m);
		v_auxn = mul_mat_vector(JT, R, v_auxn, n, m);
		double g_n = norm_2(v_auxn, n);
		//Resolver el sistema de ecuaciones
		for(int i = 0; i < n; i++) {
			JJT[i][i] += lambda;
		}
		v_auxn = scale_vect(v_auxn, v_auxn, n, -1.0);
		double *p = LU_solver(JJT, v_auxn, n);
		x1 = add_vect(x, p, x1, n);
		f_ptr(d_x, d_y, x1, theta, d4, sigma, R1, n, m);
		double fk = 0.5 * inner_product(R, R, m);
		double fk1 = 0.5 * inner_product(R1, R1, m);
		free_vector(p);

		if(k == 0) {
			printf("Primera iteración.\nk\tx_1\tx_2\tlambda\tf(x)\t||grad(f)||\n");
			printf("%d %lf %lf %g %g %g\n\n", k, x[0], x[1], lambda, fk, g_n);
		}

		if(fk1 >= fk) {
			lambda *= v;
		}
		else {
			for(int i = 0; i < n; i++) {
				x[i] = x1[i];
			}
			lambda /= v;
		}

		//Recalcular las Jacobianas
		J_ptr(d_x, d_y, x, theta, d4, sigma, J, n, m, h);
		JT = transpose_matrix(J, JT, m, n);
		JJT = mul_mat_mat(JT, J, JJT, n, m);

		k++;
		if(g_n <= tol) {
			printf("Norma del gradiente menor que la tolerancia: %g.\n\n", g_n);
			printf("Última iteración.\nk\tx_1\tx_2\tlambda\tf(x)\t||grad(f)||\n");
			printf("%d %lf %lf %g %g %g\n\n", k, x[0], x[1], lambda, fk, g_n);
			break;
		}
		if(k == iter_max) {
			printf("Número de iteraciones alcanzado.\n\n");
			printf("Última iteración.\nk\tx_1\tx_2\tlambda\tf(x)\t||grad(f)||\n");
			printf("%d %lf %lf %g %g %g\n\n", k, x[0], x[1], lambda, fk, g_n);
			break;
		}
	}

	printf("Terminado en %d iteraciones.\n\n", k);
	printf("Vector resultante:\n");
	print_vector(x, n);
	printf("\n");
	for(int i = 0; i < n; i++) {
		x0[i] = x[i];
	}

	free_vector(x);
	free_vector(x1);
	free_vector(R);
	free_vector(R1);
	free_vector(v_auxn);
	free_matrix(J);
	free_matrix(JT);
	free_matrix(JJT);
}