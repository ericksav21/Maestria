#include "met_num.h"

double get_k2(double **Jac, int n, double tol) {
	double **V = NULL;
	double **JT = create_matrix(n, n, double);
	double **JJT = create_matrix(n, n, double);
	int k_res, M = 20000;

	JT = transpose_matrix(Jac, JT, n, n);
	JJT = mul_mat_mat(Jac, JT, JJT, n);
	double e = Jacobi(&JJT, &V, n, n, tol, M, &k_res);

	double *eig = create_vector(n, double);
	double e_min = 100000.0;
	double e_max = -100000.0;

	for(int i = 0; i < n; i++) {
		eig[i] = JJT[i][i];
		if(eig[i] > e_max)
			e_max = eig[i];
		if(eig[i] < e_min)
			e_min = eig[i];
	}

	double s1 = sqrt(e_max);
	double sn = sqrt(e_min);
	double k2 = (s1 / sn);

	free_vector(eig);
	free_matrix(V);
	free_matrix(JT);
	free_matrix(JJT);

	return k2;
}

void broyden(double *x0, void (*func_ptr)(double*, double*), void (*j_ptr)(double*, double**), int iter_max, double tol) {
	int n = 3;
	int k = 1;
	double *Func = create_vector(n, double);
	double *yk = create_vector(n, double);
	double *v_aux1 = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	double **Jac = create_matrix(n, n, double);
	double **m_aux = create_matrix(n, n, double);

	j_ptr(x0, Jac);
	while(1) {
		//Calcular el valor de la función en el punto xk.
		func_ptr(x0, Func);
		double nk = norm_2(Func, n);
		//Calcular el Jacobiano de la función.
		double k2 = get_k2(Jac, n, tol);

		printf("Iteración %d\n", k);
		printf("Xk: ");
		print_vector(x0, n);
		printf("Norma de la función: %g\n", nk);
		printf("k2: %g\n\n", k2);

		//Verificar tolerancia
		if(nk < tol) {
			printf("Tolerancia de la función alcanzada: %g.\n", nk);
			break;
		}
		if(k == iter_max) {
			printf("Límite de iteraciones alcanzado: %d.\n", k);
			break;
		}

		Func = scale_vect(Func, Func, n, -1.0);
		double *x1 = LU_solver(Jac, Func, n);
		for(int i = 0; i < n; i++) {
			x0[i] = x0[i] + x1[i];
		}

		func_ptr(x0, v_aux1);
		//Se hace una suma ya que Func fue cambiada por -Func
		yk = add_vect(v_aux1, Func, yk, n);
		double ssk = inner_product(x1, x1, n);
		v_aux2 = mul_mat_vector(Jac, x1, v_aux2, n, n);
		yk = substract_vect(yk, v_aux2, yk, n);
		yk = scale_vect(yk, yk, n, 1.0 / ssk);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				m_aux[i][j] = yk[i] * x1[j];
			}
		}
		Jac = add_mat(Jac, m_aux, Jac, n, n);

		k++;
		free_vector(x1);
	}

	printf("Terminado en %d iteraciones.\n", k);
	printf("Vector x*: ");
	print_vector(x0, n);
	printf("\n");

	free_vector(Func);
	free_vector(yk);
	free_vector(v_aux1);
	free_vector(v_aux2);
	free_matrix(Jac);
	free_matrix(m_aux);
}