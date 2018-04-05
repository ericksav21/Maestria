#include "utils.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

double *read_init_point(char *files_name, int *n) {
	FILE *file;
	file = fopen(files_name, "r");

	double *x;
	if(file) {
		int nn;
		fscanf(file, "%d", &nn);
		(*n) = nn;
		x = create_vector(nn, double);
		for(int i = 0; i < nn; i++) {
			fscanf(file, "%lf", &x[i]);
		}

		fclose(file);
		return x;
	}
	else {
		printf("Error: No se pudo abrir el archivo de entrada.\n");
		return NULL;
	}
}

double ***read_histogram(char *files_name, int *n) {
	FILE *file;
	file = fopen(files_name, "r");
	if(file) {
		int nn;
		fscanf(file, "%d", &nn);
		(*n) = nn;
		fscanf(file, "%d", &nn);
		fscanf(file, "%d", &nn);
		double ***matrix = create_vmatrix(nn, nn, nn, double);

		for(int i = 0; i < nn; i++) {
			for(int j = 0; j < nn; j++) {
				for(int k = 0; k < nn; k++) {
					double aux;
					fscanf(file, "%lf", &aux);
					matrix[i][j][k] = aux;
				}
			}
		}

		fclose(file);
		return matrix;
	}
	else {
		printf("Error: No se pudo abrir el archivo de histograma.\n");
		return NULL;
	}
}

double **vect_c(int nbins) {
	int sz = nbins * nbins * nbins;
	double** v_c = create_matrix(sz, 3, double);
	int cnt = 0;
	for(int r = 0; r < nbins; r++) {
		for(int g = 0; g < nbins; g++) {
			for(int b = 0; b < nbins; b++) {
				//printf("%d %d %d\n", r, g, b);
				v_c[cnt][0] = r;
				v_c[cnt][1] = g;
				v_c[cnt++][2] = b;
			}
		}
	}

	return v_c;
}

/*----- Función principal -----*/
double f_pexp(double *ck, double *mu, double sigma) {
	double *v_aux = create_vector(3, double);
	v_aux = substract_vect(ck, mu, v_aux, 3);
	double v_norm = norm_2(v_aux, 3);
	v_norm = v_norm * v_norm;
	double res = exp((-v_norm) / (2.0 * sigma * sigma));

	free_vector(v_aux);
	return res;
}

double f_psum(double *ck, double *alpha, double *mu, double sigma, int ng) {
	double res = 0.0;
	double *mu_i = create_vector(3, double);

	for(int i = 0; i < ng; i++) {
		for(int j = 0; j < 3; j++) {
			mu_i[j] = mu[i * 3 + j];
		}
		double e_aux = f_pexp(ck, mu_i, sigma);
		res += alpha[i] * e_aux;
	}

	free_vector(mu_i);
	return res;
}

//nc = nbins^3
double f_prin(double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng) {
	double *ck = create_vector(3, double);
	double res = 0.0;
	int cnt = 0;
	for(int i = 0; i < nbins; i++) {
		for(int j = 0; j < nbins; j++) {
			for(int k = 0; k < nbins; k++) {
				for(int nb = 0; nb < 3; nb++) {
					ck[nb] = v_c[cnt][nb];
				}
				cnt++;
				double aux_s = f_psum(ck, alpha, mu, sigma, ng);
				res += pow(hc[i][j][k] - aux_s, 2);
			}
		}
	}

	free_vector(ck);
	return res;
}

/*----- Gradiente de las alphas -----*/
void g_alpha(double *grad, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng) {
	double *ck = create_vector(3, double);
	double *mu_i = create_vector(3, double);

	for(int g = 0; g < ng; g++) {
		double res = 0.0;
		int cnt = 0;

		for(int i = 0; i < nbins; i++) {
			for(int j = 0; j < nbins; j++) {
				for(int k = 0; k < nbins; k++) {
					for(int nb = 0; nb < 3; nb++) {
						ck[nb] = v_c[cnt][nb];
					}
					cnt++;
					double aux_s = f_psum(ck, alpha, mu, sigma, ng);
					aux_s = hc[i][j][k] - aux_s;
					
					for(int mj = 0; mj < 3; mj++) {
						mu_i[mj] = mu[g * 3 + mj];
					}
					double e_aux = f_pexp(ck, mu_i, sigma);
					res += aux_s * e_aux;
				}
			}
		}

		grad[g] = -2.0 * res;
	}
	free_vector(mu_i);
	free_vector(ck);
}

/*----- Gradiente de las mu -----*/
void g_mu(double *grad, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng) {
	double *ck = create_vector(3, double);
	double *mu_i = create_vector(3, double);

	for(int g = 0; g < ng; g++) {
		for(int gi = 0; gi < 3; gi++) {
			double res = 0.0;
			int cnt = 0;

			for(int i = 0; i < nbins; i++) {
				for(int j = 0; j < nbins; j++) {
					for(int k = 0; k < nbins; k++) {
						for(int nb = 0; nb < 3; nb++) {
							ck[nb] = v_c[cnt][nb];
						}
						cnt++;
						double aux_s = f_psum(ck, alpha, mu, sigma, ng);
						aux_s = hc[i][j][k] - aux_s;
						
						for(int mj = 0; mj < 3; mj++) {
							mu_i[mj] = mu[g * 3 + mj];
						}
						double e_aux = f_pexp(ck, mu_i, sigma);
						res += aux_s * e_aux * alpha[g] * (ck[gi] - mu_i[gi]);
					}
				}
			}

			grad[g * 3 + gi] = (-2.0 / sigma * sigma) * res;
		}
	}

	free_vector(mu_i);
	free_vector(ck);
}

/*----- Hessiano de las alphas -----*/
void H_alpha(double **H, double **v_c, double *mu, double sigma, int nbins, int ng) {
	double *ck = create_vector(3, double);
	double *mu_i = create_vector(3, double);

	for(int y = 0; y < ng; y++) {
		for(int x = 0; x < ng; x++) {
			double h_i = 0.0;
			int cnt = 0;

			for(int i = 0; i < nbins; i++) {
				for(int j = 0; j < nbins; j++) {
					for(int k = 0; k < nbins; k++) {
						for(int nb = 0; nb < 3; nb++) {
							ck[nb] = v_c[cnt][nb];
						}
						cnt++;
						for(int mj = 0; mj < 3; mj++) {
							mu_i[mj] = mu[y * 3 + mj];
						}
						//Diagonal
						if(y == x) {
							double e_aux = f_pexp(ck, mu_i, sigma);
							h_i += e_aux * e_aux;
						}
						else {
							double e_aux1 = f_pexp(ck, mu_i, sigma);
							for(int mj = 0; mj < 3; mj++) {
								mu_i[mj] = mu[x * 3 + mj];
							}
							double e_aux2 = f_pexp(ck, mu_i, sigma);
							h_i += (e_aux1 * e_aux2);
						}
					}
				}
			}
			H[y][x] = 2.0 * h_i;
		}
	}

	free_vector(mu_i);
	free_vector(ck);
}

void H_mu(double **H, double ***hc, double **v_c, double *alpha, double *mu, double sigma, int nbins, int ng) {
	int nx = ng * 3;
	double *mu_i = create_vector(nx, double);
	double *g1 = create_vector(nx, double);
	double *g2 = create_vector(nx, double);
	double *v_aux = create_vector(nx, double);

	for(int i = 0; i < nx; i++) {
		mu_i[i] = mu[i];
	}
	double h = 0.0000001;

	for(int i = 0; i < nx; i++) {
		double aux = mu_i[i];
		mu_i[i] += h;
		g_mu(g1, hc, v_c, alpha, mu_i, sigma, nbins, ng);
		g_mu(g2, hc, v_c, alpha, mu, sigma, nbins, ng);

		substract_vect(g1, g2, v_aux, nx);
		for(int j = 0; j < nx; j++) {
			v_aux[j] /= h;
		}
		mu_i[i] = aux;
		for(int j = 0; j < nx; j++) {
			H[j][i] = v_aux[j];
		}
	}

	free_vector(mu_i);
	free_vector(g1);
	free_vector(g2);
	free_vector(v_aux);
}

/*----- Función 2 - Rosembrock 100 -----*/

void get_gradient_2(double *g, double *x, int n) {
	g[0] = -400.0 * x[0] * (x[1] - x[0] * x[0]) - 2.0 * (1.0 - x[0]);
	g[n - 1] = 200.0 * (x[n - 1] - x[n - 2] * x[n - 2]);

	for(int i = 1; i < n - 1; i++) {
		g[i] = 200.0 * (x[i] - x[i - 1] * x[i - 1]) - 400.0 * x[i] * (x[i + 1] - x[i] * x[i]) - 2.0 * (1.0 - x[i]);
	}
}

void get_Hessian_2(double **H, double *x, int n) {
	for(int i = 0; i < n; i++) {
		if(i < n - 1) {
			H[i + 1][i] = -400.0 * x[i];
			H[i][i + 1] = -400.0 * x[i];
		}
		if(i > 0 && i < n - 1) {
			H[i][i] = 202.0 - 400.0 * x[i + 1] + 1200.0 * x[i] * x[i];
		}
	}
	H[0][0] = -400.0 * (x[1] - 3.0 * x[0] * x[0]) + 2.0;
	H[n - 1][n - 1] = 200.0;
}

double f_2(double *x, int n) {
	double res = 0.0;
	for(int i = 0; i < n - 1; i++) {
		res += (100.0 * pow((x[i + 1] - x[i] * x[i]), 2) + pow(1.0 - x[i], 2));
	}

	return res;
}

/*----- LU -----*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol) {
	double *x = create_vector(nc, double);
	if(fabs(A[0][0]) < tol) {
		free_vector(x);
		if(b[0] == 0)
			printf("El sistema tiene infinitas soluciones.\n");
		else
			printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[0] = b[0] / A[0][0];
	for(int i = 1; i < nr; i++) {
		int flag = 0;
		for(int k = 0; k <= i; k++) {
			if(fabs(A[i][k]) > tol) {
				flag = 1;
				break;
			}
		}
		if(!flag) {
			free_vector(x);
			if(b[i] == 0)
				printf("El sistema tiene infinitas soluciones.\n");
			else
				printf("El sistema no tiene solución.\n");
			return NULL;
		}

		if(fabs(A[i][i]) < tol) {
			free_vector(x);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		double sum = 0.0;
		for(int j = 0; j < i; j++) {
			sum += (A[i][j] * x[j]);
		}
		x[i] = (b[i] - sum) / A[i][i];
	}

	return x;
}

double *solve_mupper(double **A, double *b, int nr, int nc, double tol) {
	double *x = create_vector(nc, double);
	if(fabs(A[nr - 1][nc - 1]) < tol) {
		free_vector(x);
		if(b[nc - 1] == 0)
			printf("El sistema tiene infinitas soluciones.\n");
		else
			printf("El sistema no tiene solución.\n");
		return NULL;
	}
	x[nc - 1] = b[nc - 1] / A[nr - 1][nc - 1];
	for(int i = nr - 2; i >= 0; i--) {
		int flag = 0;
		for(int k = nc - 1; k >= i; k--) {
			if(fabs(A[i][k]) > tol) {
				flag = 1;
				break;
			}
		}
		if(!flag) {
			free_vector(x);
			if(b[i] == 0)
				printf("El sistema tiene infinitas soluciones.\n");
			else
				printf("El sistema no tiene solución.\n");
			return NULL;
		}

		if(fabs(A[i][i]) < tol) {
			free_vector(x);
			printf("El sistema no tiene solución.\n");
			return NULL;
		}
		double sum = 0.0;
		for(int j = nc - 1; j > i; j--) {
			sum += (A[i][j] * x[j]);
		}
		x[i] = (b[i] - sum) / A[i][i];
	}

	return x;
}

int factorize_LU(double **A, double ***L, double ***U, int n, double tol) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			double aux = 0.0;

			//Es una Li
			if(i > j) {
				if(fabs((*U)[j][j]) < tol) {
					return 0;
				}
				for(int k = 0; k < j; k++) {
					aux += ((*L)[i][k] * (*U)[k][j]);
				}
				(*L)[i][j] = (A[i][j] - aux) / (*U)[j][j];
			}
			else {
				for(int k = 0; k < i; k++) {
					aux += ((*L)[i][k] * (*U)[k][j]);
				}
				(*U)[i][j] = A[i][j] - aux;
			}

			if(i == j){
				(*L)[i][i] = 1.0;
			}
		}
	}

	return 1;
}

double* LU_solver(double **A, double *d, int n) {
	double tol = sqrt(get_EPS());
	double **L = create_matrix(n, n, double);
	double **U = create_matrix(n, n, double);
	double *b, *x;
	int c = factorize_LU(A, &L, &U, n, tol);
	if(c) {
		b = solve_mlower(L, d, n, n, tol);
		x = solve_mupper(U, b, n, n, tol);
	}

	//free_vector(b);
	//free_matrix(L);
	//free_matrix(U);

	return x;
}

int cholesky(double **A, double ***L, double ***Lt, int n, double tol) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < (i + 1); j++) {
			double aux = 0.0;
			for(int k = 0; k < j; k++) {
				aux += (*L)[i][k] * (*L)[j][k];
			}
			if(i == j) {
				if(A[i][i] - aux < 0) {
					return 0;
				}
				(*L)[i][j] = sqrt(A[i][i] - aux);
				(*Lt)[i][j] = (*L)[i][j];
			}
			else {
				if(fabs((*L)[j][j]) < tol) {
					return 0;
				}
				(*L)[i][j] = 1.0 / (*L)[j][j] * (A[i][j] - aux);
				(*Lt)[j][i] = (*L)[i][j];
			}
		}
	}

	return 1;
}
