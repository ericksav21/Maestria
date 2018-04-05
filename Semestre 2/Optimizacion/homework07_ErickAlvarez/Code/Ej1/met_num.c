#include "met_num.h"

double get_EPS() {
	double Eps = 1.0;

	while (1.0 + Eps / 2.0 != 1.0)
		Eps /= 2.0;

	return Eps;
}

double* conjugate_gradient(double *init, double *y, int n, double lambda, double tol_g, double tol_x, double tol_f) {
	FILE *f1 = fopen("f_eval.txt", "w");
	FILE *f2 = fopen("g_norm.txt", "w");

	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
	}
	//Obtener el Hessiano
	double **H = create_matrix(n, n, double);
	double *gradient = create_vector(n, double);
	double *d = create_vector(n, double);
	double *w = create_vector(n, double);
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			H[i][j] = 0.0;
		}
	}
	get_Hessian_sm(H, lambda, n);
	get_gradient_sm(gradient, x0, y, lambda, n);
	d = scale_vect(gradient, d, n, -1.0);
	int k = 0;
	while(1) {
		double gn = norm_2(gradient, n);
		fprintf(f2, "%d %g\n", k + 1, gn);
		if(gn < tol_g) {
			printf("Norma del gradiente menor que la tolerancia: %g\n", gn);
			break;
		}
		w = mul_mat_vector(H, d, w, n, n);
		double a_num = gn * gn;
		double a_den = inner_product(d, w, n);
		double alpha_k = a_num / a_den;

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
		double fn1 = f_sm(x1, y, lambda, n);
		double fn = f_sm(x0, y, lambda, n);
		fprintf(f1, "%d %g\n", k + 1, fn);
		double fn_dif = fabs(fn1 - fn) / max(1.0, fabs(fn));
		if(fn_dif < tol_f) {
			printf("Norma de las funciones menor que la tolerancia: %g\n", fn_dif);
			break;
		}
		for(int i = 0; i < n; i++) {
			x0[i] = x1[i];
		}
		get_gradient_sm(gradient, x0, y, lambda, n);
		
		//Generar la beta
		double b_num = inner_product(gradient, w, n);
		double b_den = inner_product(d, w, n);
		double beta = b_num / b_den;

		//Generar la nueva dirección Q-conjugada
		v_aux = scale_vect(gradient, v_aux, n, -1.0);
		v_aux2 = scale_vect(d, v_aux2, n, beta);
		d = add_vect(v_aux, v_aux2, d, n);
		k++;
		printf("Iteración %d:\nAlpha: %g\n||g_k||:%g\n||xk+1 - xk||:%g\n|f_k+1 - f_k|:%g\n\n", k, alpha_k, gn, xn_dif, fn_dif);
	}

	printf("Gradiente conjutado terminado en %d iteraciones.\n", k + 1);

	free_matrix(H);
	free_vector(x1);
	free_vector(gradient);
	free_vector(d);
	free_vector(w);
	free_vector(v_aux);
	free_vector(v_aux2);
	fclose(f1);
	fclose(f2);

	return x0;
}

void exec(char *files_name, double lambda, double tol_g, double tol_x, double tol_f) {
	double *xr, *y, *x0;
	int n;

	FILE *file;
	file = fopen(files_name, "r");

	if(file) {
		int nn;
		fscanf(file, "%d", &n);
		xr = create_vector(n, double);
		x0 = create_vector(n, double);
		y = create_vector(n, double);

		double aux;
		for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &aux);
			y[i] = aux;
		}
		for(int i = 0; i < n; i++) {
			fscanf(file, "%lf", &aux);
			xr[i] = aux;
		}
		generate_init_point(x0, n);
		double *xk = conjugate_gradient(x0, y, n, lambda, tol_g, tol_x, tol_f);

		printf("\nVector resultante:\n");
		print_vector(xk, n);
		printf("\n");

		//Imprimir los vectores en un archivo
		FILE *out = fopen("result.txt", "w");
		for(int i = 0; i < n; i++) {
			fprintf(out, "%d %lf %lf %lf\n", (i + 1), xk[i], xr[i], y[i]);
		}
		fclose(out);

		free_vector(xk);
		fclose(file);
		printf("Archivos de texto generados.\n");

		free_vector(y);
		free_vector(xr);
		free_vector(x0);
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return;
	}
}