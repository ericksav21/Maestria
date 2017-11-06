#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double *resuelve_m_tridiagonal(MAT3D *mat, double *d, double tol) {
	int n = mat->n;
	double *x = create_vector(n, double);
	double *_d = create_vector(n, double);
	MAT3D *aux = create_mat_3d(n);

	aux->b[0] = mat->b[0];
	aux->c[0] = mat->c[0];
	_d[0] = d[0];

	for(int i = 1; i < n; i++) {
		aux->b[i] = (aux->b[i - 1] * mat->b[i]) - (mat->a[i] * aux->c[i - 1]);
		aux->c[i] = aux->b[i - 1] * mat->c[i];
		_d[i] = (aux->b[i - 1] * d[i]) - (mat->a[i] * _d[i - 1]);
	}

	if(fabs(aux->b[n - 1]) < tol) {
		free_vector(x);
		free_vector(_d);
		aux = free_mat_3d(aux);
		free(aux);
		printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[n - 1] = _d[n - 1] / aux->b[n - 1];
	for(int i = n - 2; i >= 0; i--) {
		if(fabs(aux->b[i]) < tol) {
			free_vector(x);
			free_vector(_d);
			aux = free_mat_3d(aux);
			free(aux);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		x[i] = (_d[i] - aux->c[i] * x[i + 1]) / aux->b[i];
	}

	aux = free_mat_3d(aux);
	free(aux);
	free_vector(_d);
	return x;
}

//is_next: Determina si se regresa N_k o N_k+1.
//Se tienen n + 1 puntos z. 
double N(double x, double *z, int k, int is_next) {
	if(x >= z[k] && x <= z[k + 1]) {
		double h = (z[k + 1] - z[k]);
		if(!is_next)
			return 1.0 - (1.0 / h) * (x - z[k]);
		else
			return (1.0 / h) * (x - z[k]);
	}
	else {
		return 0;
	}
}

int kronec(int i, int j) {
	if(i == j)
		return 1;
	return 0;
}

//Tipo 1: Sum{N_k}
//Tipo 2: Sum{N_k+1}
//Tipo 3: Sum{N_k^2}
//Tipo 4: Sum{N_k+1^2}
//Tipo 5: Sum{N_k * N_k+1}
//Coef: Determina si multiplicar por y_i
double sumN(double *x, double *y, double *z, int m, int k, int coef, int type) {
	double res = 0.0;
	for(int i = 0; i < m; i++) {
		switch(type) {
			case 1:
				if(coef)
					res += y[i] * N(x[i], z, k, 0);
				else
					res += N(x[i], z, k, 0);
				break;
			case 2:
				if(coef)
					res += y[i] * N(x[i], z, k, 1);
				else
					res += N(x[i], z, k, 1);
				break;
			case 3:
				res += pow(N(x[i], z, k, 0), 2);
				break;
			case 4:
				res += pow(N(x[i], z, k, 1), 2);
				break;
			case 5:
				res += N(x[i], z, k, 0) * N(x[i], z, k, 1);
				break;
		}
	}

	return res;
}

double* generate_phi(double *x, double *y, int m, int n, double lambda) {
	double h = (x[m - 1] - x[0]) / (double)n;
	double *z = create_vector(n + 1, double);
	for(int i = 0; i <= n; i++) {
		z[i] = x[0] + i * h;
	}
	//Construir los b's
	double *a = create_vector(n, double);
	double *b = create_vector(n, double);
	double *c = create_vector(n, double);
	double *s = create_vector(n, double);
	double *t = create_vector(n, double);
	double *d = create_vector(n + 1, double);
	for(int i = 0; i < n; i++) {
		a[i] = sumN(x, y, z, m, i, 0, 3) + (lambda / h);
		b[i] = sumN(x, y, z, m, i, 0, 5) - (lambda / h);
		c[i] = sumN(x, y, z, m, i, 0, 4) + (lambda / h);
		s[i] = sumN(x, y, z, m, i, 1, 1);
		t[i] = sumN(x, y, z, m, i, 1, 2);
	}
	MAT3D *aux = create_mat_3d(n + 1);
	for(int i = 1; i < n; i++) {
		aux->a[i] = b[i - 1];
		aux->b[i] = a[i] + c[i - 1];
		aux->c[i] = b[i];
		d[i] = t[i - 1] + s[i];
	}
	aux->a[n] = b[n - 1];
	aux->b[0] = a[0];
	aux->b[n] = c[n - 1];
	aux->c[0] = b[0];
	d[0] = s[0];
	d[n] = t[n - 1];

	double tol = sqrt(get_EPS());
	double *phi = resuelve_m_tridiagonal(aux, d, tol);

	aux = free_mat_3d(aux);
	free(aux);
	free_vector(a);
	free_vector(b);
	free_vector(c);
	free_vector(s);
	free_vector(t);
	free_vector(d);
	free_vector(z);

	return phi;
}

double phi_x(double *x, double *phi, double *z, double xm, int n) {
	double res = 0.0, nk, nk1;
	int k;
	for(int i = 0; i < n; i++) {
		if(xm >= z[i] && xm <= z[i + 1]) {
			k = i;
			nk = N(xm, z, k, 0);
			nk1 = N(xm, z, k, 1);
			break;
		}
	}
	res = phi[k] * nk + phi[k + 1] * nk1;

	return res;
}

void generate(double *x, double *y, int m, int n, double lambda, char *files_name) {
	double h = (x[m - 1] - x[0]) / (double)n;
	double *z = create_vector(n + 1, double);
	for(int i = 0; i <= n; i++) {
		z[i] = x[0] + i * h;
	}
	double *phi = generate_phi(x, y, m, n, lambda);
	FILE *out = fopen(files_name, "w");
	for(int i = 0; i < m; i++) {
		fprintf(out, "%lf %lf\n", x[i], phi_x(x, phi, z, x[i], n));
	}

	free_vector(phi);
	free_vector(z);
	fclose(out);
}