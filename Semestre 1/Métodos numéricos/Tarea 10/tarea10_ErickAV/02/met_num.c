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

double* generate_M(double *x, double *y, int n, double tol) {
	//Generamos las hi's
	double *h = create_vector(n, double);
	double *mu = create_vector(n, double);
	double *lambda = create_vector(n, double);
	double *d = create_vector(n - 2, double);

  for(int i = 0; i < n - 2; i++) d[i] = 0.0;
  for(int i = 0; i < n; i++) h[i] = mu[i] = lambda[i] = 0.0;
  for(int i = 1; i < n; i++) {
    h[i] = x[i] - x[i - 1];
  }
  for(int i = 1; i < n - 1; i++) {
    mu[i] = h[i] / (h[i] + h[i + 1]);
    lambda[i] = h[i + 1] / (h[i] + h[i + 1]);
    d[i - 1] = (6.0 / (h[i] + h[i + 1])) * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]);
  }

  MAT3D *mat = create_mat_3d(n - 2);
  for(int i = 1; i < n - 2; i++) {
    mat->a[i] = mu[i + 1];
    mat->b[i] = 2.0;
    mat->c[i - 1] = lambda[i];
  }
  //mat->a[n - 1] = mu[n - 1];
  mat->b[0] = mat->b[n - 3] = 2.0;
  mat->c[0] = lambda[1];

  double *Maux = resuelve_m_tridiagonal(mat, d, tol);
  double *M = create_vector(n, double);
  for(int i = 1; i < n - 1; i++) {
    M[i] = Maux[i - 1];
  }

	mat = free_mat_3d(mat);
	free(mat);
	free_vector(Maux);
	free_vector(h);
	free_vector(mu);
	free_vector(lambda);
	free_vector(d);

	return M;
}

double evaluate_pol(double *x, double *y, double *M, double xm, int n) {
	int ii;
	for(int i = 1; i < n; i++) {
		if(xm <= x[i] && xm >= x[i - 1]) {
			ii = i;
			break;
		}
	}
	double hi = x[ii] - x[ii - 1];
	double Cp = y[ii - 1] - M[ii - 1] * (pow(hi, 2) / 6.0);
	double C = ((y[ii] - y[ii - 1]) / hi) - ((hi / 6.0) * (M[ii] - M[ii - 1]));

	double Si = M[ii - 1] * pow(x[ii] - xm, 3) / (6.0 * hi) + M[ii] * pow(xm - x[ii - 1], 3) / (6.0 * hi);
	Si += (C * (xm - x[ii - 1])) + Cp;

	return Si;
}

void generate(double *x, double *y, double *M, int m, int n, char *files_name) {
	FILE *out = fopen(files_name, "w");
	double *xr = create_vector(m + 1, double);
	double *yr = create_vector(m + 1, double);
	for(int i = 0; i <= m; i++) {
		xr[i] = x[0] + i * (x[n - 1] - x[0]) / (double)m;
		yr[i] = evaluate_pol(x, y, M, xr[i], n);
	}
	for(int i = 0; i <= m; i++) {
		fprintf(out, "%lf %lf\n", xr[i], yr[i]);
	}

	free_vector(xr);
	free_vector(yr);
	fclose(out);
}
