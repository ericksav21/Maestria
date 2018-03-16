#include "met_num.h"

void mul_m_tridiagonal(MAT3D *mat, double *x, double *d, int n) {
	d[0] = mat->b[0] * x[0] + mat->c[0] * x[1];
	d[n - 1] = mat->a[n - 1] * x[n - 2] + mat->b[n - 1] * x[n - 1];
	for(int i = 1; i < n - 1; i++) {
		d[i] = mat->a[i] * x[i - 1] + mat->b[i] * x[i] + mat->c[i] * x[i + 1];
	}
}

void get_gradient(double *g, double *x, int n) {
	get_gradient_2(g, x, n);
}

double get_f(double *x, int n) {
	return f_2(x, n);
}

double* PU(double *g, double **H, int n) {
	double *hg = create_vector(n, double);
	hg = mul_mat_vector(H, g, hg, n, n);
	double dk = inner_product(g, g, n);
	double ddk = inner_product(g, hg, n);

	double sc = -(dk / ddk);
	double *res = create_vector(n, double);
	res = scale_vect(g, res, n, sc);

	free_vector(hg);

	return res;
}

double* PB(double *g, double **H, int n) {
	double *gm = create_vector(n, double);
	gm = scale_vect(g, gm, n, -1.0);
	double *res = LU_solver(H, gm, n);

	free_vector(gm);

	return res;
}

double mk(double *x, double *p, double *g, double **H, int n) {
	double *hp = create_vector(n, double);
	hp = mul_mat_vector(H, p, hp, n, n);

	double ddk = 0.5 * inner_product(p, hp, n);
	double gp = inner_product(g, p, n);
	double fp = get_f(x, n);

	free_vector(hp);

	return fp + gp + ddk;
}

double phi(double *x, double *ppk, double *g, double **H, int n) {
	double *ssk = create_vector(n, double);
	double *zeros = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		zeros[i] = 0.0;
	}
	ssk = add_vect(x, ppk, ssk, n);

	double res = (get_f(x, n) - get_f(ssk, n)) / (mk(x, zeros, g, H, n) - mk(x, ppk, g, H, n));

	free_vector(ssk);

	return res;
}

double *dogleg(double *pu, double *pb, double delta, int n) {
	double *v_aux = create_vector(n, double);
	double *v_aux2 = create_vector(n, double);
	double *res = create_vector(n, double);

	v_aux = substract_vect(pb, pu, v_aux, n);
	double aux = norm_2(v_aux, n);

	double a = aux * aux;
	double b = 2.0 * inner_product(pb, v_aux, n);

	aux = norm_2(pu, n);
	double c = aux * aux - delta * delta;
	printf("%lf %lf %lf\n", a, b, c);

	double tao = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
	if(tao >= 0.0 && tao <= 1) {
		res = scale_vect(pu, res, n, tao);
	}
	else {
		v_aux2 = scale_vect(v_aux, v_aux2, n, (1.0 - tao));
		res = add_vect(pu, v_aux2, res, n);
	}

	free_vector(v_aux);
	free_vector(v_aux2);

	return res;
}

double *approx(double *x, double *g, double **H, double delta, int n) {
	double tol = sqrt(get_EPS());
	double *pu = PU(g, H, n);
	double *pb = PB(g, H, n);

	double npb = norm_2(pb, n);
	if(npb <= delta) {
		free_vector(pu);
		return pb;
	}
	double **L = create_matrix(n, n, double);
	double **Lt = create_matrix(n, n, double);
	int def_pos = cholesky(H, &L, &Lt, n, tol);
	free_matrix(L);
	free_matrix(Lt);

	if(def_pos == 1) {
		double *dl = dogleg(pu, pb, delta, n);
		free_vector(pu);
		free_vector(pb);
		return dl;
	}

	free_vector(pb);

	return pu;
}

void r_confidence(double *init, int max_iter, int n) {
	double deltaM = 1.0, delta = 0.4, nabla = 0.1;
	int t = 0;
	double *x0 = create_vector(n, double);
	double *x1 = create_vector(n, double);
	double **H = create_matrix(n, n, double);
	double *gradient = create_vector(n, double);
	for(int i = 0; i < n; i++) {
		x0[i] = init[i];
		gradient[i] = 0.0;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			H[i][j] = 0.0;
		}
	}
	while(1) {
		printf("Iteración: %d\n", t);

		get_gradient(gradient, x0, n);
		get_Hessian_2(H, x0, n);

		double gn = norm_2(gradient, n);
		printf("\nNorma del gradiente: %d\n", (int)gn);
		
		//Solución aproximada
		double *pk = approx(x0, gradient, H, delta, n);
		double phi_k = phi(x0, pk, gradient, H, n);
		if(phi_k > nabla) {
			printf("Actualización...\n");
			x1 = add_vect(x0, pk, x1, n);
			for(int i = 0; i < n; i++) {
				x0[i] = x1[i];
			}
		}
		else if(phi_k < 0.25) {
			delta *= 0.25;
		}
		else {
			double npk = norm_2(pk, n);
			if(phi_k > 0.75 && npk == delta) {
				delta = (2.0 * delta < deltaM ? 2.0 * delta : deltaM);
			}
		}

		printf("Delta: %g\n", delta);
		if(t == max_iter) {
			break;
		}
		t++;
	}

	free_vector(x0);
	free_vector(x1);
	free_vector(gradient);
	free_matrix(H);
}