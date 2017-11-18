#include "met_num.h"

double get_EPS() {
    double Eps = 1.0;
 
    while (1.0 + Eps / 2.0 != 1.0)
        Eps /= 2.0;

    return Eps;
}

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

double f_a(double x) {
	return x + 2.0 * sin(x);
}

void generate_system(double ***M, double **V, double *yi, double h, double xi, double xi1) {
	//Izq
	(*M)[0][0] = 1.0;
	(*M)[0][1] = -h / 2.0;
	(*M)[1][0] = h / 2.0;
	(*M)[1][1] = 1 - (h / 2.0) * xi1;

	//Der
	double **I = get_I(2);
	double *aux = create_vector(2, double);
	I[0][1] = h / 2.0;
	I[1][0] = -h / 2.0;
	I[1][1] += (h / 2.0) * xi;
	aux = mul_mat_vector(I, yi, aux, 2, 2);
	double auxn = (h / 2.0) * (-2.0 * xi * cos(xi) - 2.0 * xi1 * cos(xi1));
	(*V)[0] = aux[0];
	(*V)[1] = aux[1] + auxn;

	free_matrix(I);
	free_vector(aux);
}

void solve(double a, double b, int n) {
	double tol = sqrt(get_EPS()), err_abs = 0.0, max_err = -1.0;
	double h = (b - a) / n;
	double *yi = create_vector(2, double);
	yi[0] = 0.0;
	yi[1] = 3.0;
	for(int i = 0; i < n; i++) {
		double xi = a + i * h, xi1 = a + (i + 1) * h;
		double **M = create_matrix(2, 2, double);
		double *V = create_vector(2, double);
		generate_system(&M, &V, yi, h, xi, xi1);		
		//Resolver por LU
		double **L = create_matrix(2, 2, double);
		double **U = create_matrix(2, 2, double);
		factorize_LU(M, &L, &U, 2, tol);
		double *c = solve_mlower(L, V, 2, 2, tol);
		double *yi1 = solve_mupper(U, c, 2, 2, tol);
		double err_act = fabs(f_a(xi1) - yi1[0]);
		err_abs += err_act;
		if(err_act > max_err)
			max_err = err_act;

		yi[0] = yi1[0], yi[1] = yi1[1];

		free_matrix(M);
		free_matrix(L);
		free_matrix(U);
		free_vector(V);
		free_vector(c);
		free_vector(yi1);
	}
	err_abs /= (double)n;

	printf("Error absoluto promedio: %g\nError máximo: %g\n", err_abs, max_err);
	printf("Yn (numérico): %lf, Yn (analítico): %lf\n", yi[0], f_a(b));

	free_vector(yi);
}