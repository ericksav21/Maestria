#include "met_num.h"

void get_gradient(double *g, double ***hc, double **v_c, double *alpha, double *mu, double sigma,
				int nbins, int ng, int optimice_mu) {
	if(optimice_mu) {
		g_mu(g, hc, v_c, alpha, mu, sigma, nbins, ng);
	}
	else {
		g_alpha(g, hc, v_c, alpha, mu, sigma, nbins, ng);
	}
}

double get_f(double ***hc, double **v_c, double *alpha, double *mu, double sigma,
			int nbins, int ng) {
	f_prin(hc, v_c, alpha, mu, sigma, nbins, ng);
}

double get_Hessian(double **H, double ***hc, double **v_c, double *alpha, double *mu, double sigma,
				int nbins, int ng, int optimice_mu) {
	if(optimice_mu) {
		H_mu(H, hc, v_c, alpha, mu, sigma, nbins, ng);
	}
	else {
		H_alpha(H, v_c, mu, sigma, nbins, ng);
	}
}

double* PU(double *g, double **H, int n) {
	double *hg = create_vector(n, double);
	hg = mul_mat_vector(H, g, hg, n, n);
	double dk = inner_product(g, g, n);
	double ddk = inner_product(g, hg, n);

	double sc = -(dk / ddk);
	double *res = create_vector(n, double);
	res = scale_vect(g, res, n, sc);

	//free_vector(hg);

	return res;
}

double* PB(double *g, double **H, int n) {
	double *gm = create_vector(n, double);
	gm = scale_vect(g, gm, n, -1.0);
	double *res = LU_solver(H, gm, n);

	//free_vector(gm);

	return res;
}

double* PC(double *g, double **H, double delta, int n) {
	double *hp = create_vector(n, double);
	hp = mul_mat_vector(H, g, hp, n, n);
	double ddk = inner_product(g, hp, n);
	double norm_g = norm_2(g, n);
	double tao;
	if(ddk <= 0.0) {
		tao = 1.0;
	}
	else {
		double aux = pow(norm_g, 3.0) / (delta * ddk);
		if(aux < 1.0) {
			tao = aux;
		}
		else {
			tao = 1.0;
		}
	}
	double sc = -1.0 * tao * (delta / norm_g);
	double *res = create_vector(n, double);
	res = scale_vect(g, res, n, sc);

	free_vector(hp);

	return res;
}

/* Aquí */
double mk(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng,
			double *p, double *g, double **H, int optimice_mu) {

	int n = (optimice_mu ? ng * 3 : ng);
	double *hp = create_vector(n, double);
	hp = mul_mat_vector(H, p, hp, n, n);

	double ddk = 0.5 * inner_product(p, hp, n);
	double gp = inner_product(g, p, n);
	double fp = get_f(hc, v_c, alpha, mu, sigma, nbins, ng);

	free_vector(hp);

	return fp + gp + ddk;
}

/* Aquí */
double phi(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng,
			double *ppk, double *g, double **H, int optimice_mu) {

	double tolD = 1e-3;
	int n = (optimice_mu ? ng * 3 : ng);
	double *ssk = create_vector(n, double);
	
	if(optimice_mu) {
		ssk = add_vect(mu, ppk, ssk, n);
	}
	else {
		ssk = add_vect(alpha, ppk, ssk, n);
	}
	double f_k = get_f(hc, v_c, alpha, mu, sigma, nbins, ng);
	double f_ks;
	if(optimice_mu) {
		f_ks = get_f(hc, v_c, alpha, ssk, sigma, nbins, ng);
	}
	else {
		f_ks = get_f(hc, v_c, ssk, mu, sigma, nbins, ng);
	}
	double mks = mk(hc, v_c, alpha, mu, sigma, nbins, ng, ppk, g, H, optimice_mu);
	double den = f_k - mks;
	//printf("Mks: %g f_k: %g\n", mks, f_k);
	/*if(fabs(den) < tolD) {
		den = 1e-6;
	}*/

	double res = (f_k - f_ks) / den;

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
	
	double tao = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
	tao++;
	v_aux2 = scale_vect(v_aux, v_aux2, n, tao);
	res = add_vect(pu, v_aux2, res, n);

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
		printf("PU\n");
		return pb;
	}
	double **L = create_matrix(n, n, double);
	double **Lt = create_matrix(n, n, double);
	int def_pos = cholesky(H, &L, &Lt, n, tol);
	//printf("%d\n", def_pos);
	free_matrix(L);
	free_matrix(Lt);

	if(def_pos == 1) {
		double *dl = dogleg(pu, pb, delta, n);
		free_vector(pu);
		free_vector(pb);
		printf("Dogleg\n");
		return dl;
	}

	//free_vector(pb);
	//free_vector(pu);

	printf("Cauchy\n");
	return PC(g, H, delta, n);
}

double* r_confidence(double ***hc, double **v_c, double *alpha, double *mu, double sigma, 
				int nbins, int ng, int optimice_mu, int max_iter) {
	double deltaM = 10.0, delta = 7.0, nabla = 0.1;
	double tolG = 1.0;
	int t = 0, nx = (optimice_mu ? ng * 3 : ng);
	double *x0 = create_vector(nx, double);
	double *x1 = create_vector(nx, double);
	double **H = create_matrix(nx, nx, double);
	double *gradient = create_vector(nx, double);

	for(int i = 0; i < nx; i++) {
		if(optimice_mu) {
			x0[i] = mu[i];
		}
		else {
			x0[i] = alpha[i];
		}
		gradient[i] = 0.0;
	}
	for(int i = 0; i < nx; i++) {
		for(int j = 0; j < nx; j++) {
			H[i][j] = 0.0;
		}
	}
	while(1) {
		printf("Iteración: %d\n", t);

		if(optimice_mu) {
			get_gradient(gradient, hc, v_c, alpha, x0, sigma, nbins, ng, optimice_mu);
			get_Hessian(H, hc, v_c, alpha, x0, sigma, nbins, ng, optimice_mu);
		}
		else {
			get_gradient(gradient, hc, v_c, x0, mu, sigma, nbins, ng, optimice_mu);
			get_Hessian(H, hc, v_c, x0, mu, sigma, nbins, ng, optimice_mu);
		}

		double gn = norm_2(gradient, nx);
		printf("\nNorma del gradiente: %g\n", gn);
		if(gn < tolG) {
			break;
		}
		if(optimice_mu) {
			printf("Optimizando mu\n");
		}
		else {
			printf("Optimizando alpha\n");
		}
		
		//Solución aproximada
		double *pk = approx(x0, gradient, H, delta, nx);
		double phi_k;
		if(optimice_mu) {
			phi_k = phi(hc, v_c, alpha, x0, sigma, nbins, ng, pk, gradient, H, optimice_mu);
		}
		else {
			phi_k = phi(hc, v_c, x0, mu, sigma, nbins, ng, pk, gradient, H, optimice_mu);
		}
		//printf("Phi_k: %g\n", phi_k);
		if(phi_k < 0.25) {
			delta *= 0.25;
		}
		else {
			double npk = norm_2(pk, nx);
			if(phi_k > 0.75 && npk == delta) {
				delta = (2.0 * delta < deltaM ? 2.0 * delta : deltaM);
			}
		}
		if(phi_k > nabla) {
			printf("Actualización...\n");
			x1 = add_vect(x0, pk, x1, nx);
			for(int i = 0; i < nx; i++) {
				x0[i] = x1[i];
			}
		}

		printf("Delta: %g\n", delta);
		if(t == max_iter) {
			break;
		}
		t++;
		free_vector(pk);
	}

	free_vector(x1);
	free_vector(gradient);
	free_matrix(H);

	printf("Región de confianza terminada.\n");

	print_vector(x0, nx);
	return x0;
}

void optimice(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng) {
	int nx = ng * 3;
	double *alpha_k = create_vector(ng, double);
	double *mu_k = create_vector(nx, double);
	double *g_alpha_act = create_vector(ng, double);
	double *g_mu_act = create_vector(nx, double);
	double tolGG = 1.0;

	for(int i = 0; i < ng; i++) {
		alpha_k[i] = alpha[i];
	}
	for(int i = 0; i < nx; i++) {
		mu_k[i] = mu[i];
	}

	int t = 0;
	while(1) {
		//Optimizar alphas
		double *res_alpha = r_confidence(hc, v_c, alpha_k, mu_k, sigma, nbins, ng, 0, 10000);
		for(int i = 0; i < ng; i++) {
			alpha_k[i] = res_alpha[i];
		}

		//Optimizar mu's
		double *res_mu = r_confidence(hc, v_c, alpha_k, mu_k, sigma, nbins, ng, 1, 10000);
		for(int i = 0; i < nx; i++) {
			mu_k[i] = res_mu[i];
		}

		//Comparar gradientes
		g_alpha(g_alpha_act, hc, v_c, alpha_k, mu_k, sigma, nbins, ng);
		g_mu(g_mu_act, hc, v_c, alpha_k, mu_k, sigma, nbins, ng);

		double nga = norm_2(g_alpha_act, ng);
		double ngmu = norm_2(g_mu_act, nx);

		free_vector(res_alpha);
		free_vector(res_mu);

		if(t == 1)
			break;
		if(nga < tolGG && ngmu < tolGG) {
			printf("alpha_k y mu_k menores que el gradiente.\n");
			break;
		}
		t++;
	}

	printf("Optimización terminada en %d iteraciones.\n", t);

	for(int i = 0; i < ng; i++) {
		alpha[i] = alpha_k[i];
	}
	for(int i = 0; i < nx; i++) {
		mu[i] = mu_k[i];
	}

	free_vector(alpha_k);
	free_vector(mu_k);
	free_vector(g_alpha_act);
	free_vector(g_mu_act);
}

void solve(char *bg_hist_fn, char *obj_hist_fn, int ng, double sigma) {
	int nbins;
	int nx = ng * 3;
	double *alpha_bg = create_vector(ng, double);
	double *alpha_obj = create_vector(ng, double);

	for(int i = 0; i < ng; i++) {
		alpha_bg[i] = ((double)rand() / (double)RAND_MAX);
		alpha_obj[i] = ((double)rand() / (double)RAND_MAX);
		//alpha_bg[i] = 1.0 / (double)ng;
		//alpha_obj[i] = 1.0 / (double)ng;
	}
	double ***hc_bg = read_histogram(bg_hist_fn, &nbins);
	double ***hc_obj = read_histogram(obj_hist_fn, &nbins);
	double **v_c = vect_c(nbins);
	double *mu_bg = create_vector(3 * ng, double);
	double *mu_obj = create_vector(3 * ng, double);
	for(int i = 0; i < ng; i++) {
		for(int j = 0; j < 3; j++) {
			mu_bg[i * 3 + j] = ((double)rand() / (double)RAND_MAX) * 5.0;
			mu_obj[i * 3 + j] = ((double)rand() / (double)RAND_MAX) * 5.0;
			//mu_bg[i * 3 + j] = 1.0;
			//mu_obj[i * 3 + j] = 7.0;
		}
	}

	optimice(hc_bg, v_c, alpha_bg, mu_bg, sigma, nbins, ng);
	optimice(hc_obj, v_c, alpha_obj, mu_obj, sigma, nbins, ng);

	FILE *out = fopen("res.txt", "w");
	fprintf(out, "%d %d %d\n", nbins, ng, (int)sigma);
	//Alpha bg
	for(int i = 0; i < ng; i++) {
		fprintf(out, "%lf ", alpha_bg[i]);
	}
	fprintf(out, "\n");
	//Mu bg
	for(int i = 0; i < nx; i++) {
		fprintf(out, "%lf ", mu_bg[i]);
	}
	fprintf(out, "\n");
	//Alpha obj
	for(int i = 0; i < ng; i++) {
		fprintf(out, "%lf ", alpha_obj[i]);
	}
	fprintf(out, "\n");
	//Mu bg
	for(int i = 0; i < nx; i++) {
		fprintf(out, "%lf ", mu_obj[i]);
	}

	fclose(out);

	free_vector(alpha_bg);
	free_vector(alpha_obj);
	free_vector(mu_bg);
	free_vector(mu_obj);
	free_matrix(v_c);
	free_vmatrix(hc_bg, nbins);
	free_vmatrix(hc_obj, nbins);
}
