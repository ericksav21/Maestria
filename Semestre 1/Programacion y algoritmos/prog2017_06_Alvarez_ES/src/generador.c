#include "generador.h"

//Genera y repara un vector binario
int *generate_bv(int *bv, double *P, int n, int nfeat) {
	int cnt = 0;
	//Generar
	for(int i = 0; i < n; i++) {
		int r = rand() % 100;
		if(r < (int)(P[i] * 100.0)) {
			bv[i] = 1;
			cnt++;
		}
		else {
			bv[i] = 0;
		}
	}
	//Reparar
	while(cnt != nfeat) {
		for(int i = 0; i < n; i++) {
			int r = rand() % 100;
			if(r < (int)(P[i] * 100.0)) {
				if(bv[i] == 0 && cnt < nfeat) {
					bv[i] = 1;
					cnt++;
				}
				else if(bv[i] == 1 && cnt > nfeat) {
					bv[i] = 0;
					cnt--;
				}
			}
		}
	}

	return bv;
}

double vb_xnorm(double *P, int n) {
	double norm = 0.0;
	for(int i = 0; i < n; i++) {
		norm += pow(0.5 - P[i], 2);
	}
	return 1.0 - (4.0 / (double)n) * norm;
}

int *get_best_bv(ARGSOBJ *args, FOBJ *params) {
	int n_bstf = args->nwords, t = 0;
	int **X = create_arr2d_by_chunks_i(args->npop, n_bstf);
	double best_metric = 0.0;
	double *P = (double *)create_arr1d(n_bstf, sizeof(double));
	for(int i = 0; i < n_bstf; i++) {
		P[i] = 0.5;
	}
	int *xbest = (int *)create_arr1d(n_bstf, sizeof(int));
	xbest = generate_bv(xbest, P, n_bstf, args->nfeat);
	for(int i = 0; i < n_bstf; i++) {
		X[0][i] = xbest[i];
	}

	//Criterio de convergencia
	printf("Nfeat: %d\n", args->nfeat);
	while(vb_xnorm(P, n_bstf) > (1.0 / pow(n_bstf, 2)) && t < args->niter && best_metric != 1.0) {
		printf("Norma: %lf\n", vb_xnorm(P, n_bstf));
		//Generar la matríz de vectores binarios
		for(int i = 1; i < args->npop; i++) {
			X[i] = generate_bv(X[i], P, n_bstf, args->nfeat);
		}

		FRECROW *F = (FRECROW *)malloc(sizeof(FRECROW) * args->npop);
		for(int i = 0; i < args->npop; i++) {
			double quality = metric_eval(params, X[i]);
			F[i].id = i;
			F[i].frec = quality;
		}

		qsort(F, args->npop, sizeof(FRECROW), frec_comparator);

		printf("Iteración: %d, Mejores 3 métricas: %lf %lf %lf\n", t, F[0].frec, F[1].frec, F[2].frec);

		//Actualizar el vector de probabilidades
		for(int i = 0; i < n_bstf; i++) P[i] = 0.0;
		for(int i = 0; i < (int)(args->npop / 2); i++) {
			int ind = F[i].id;
			for(int j = 0; j < n_bstf; j++) {
				P[j] += X[ind][j];
			}
		}
		for(int i = 0; i < n_bstf; i++) P[i] /= ((double)args->npop / 2.0);

		//Copiar el mejor vector
		int ind = F[0].id;
		best_metric = F[0].frec;
		for(int i = 0; i < n_bstf; i++) {
			xbest[i] = X[ind][i];
			X[0][i] = xbest[i];
		}
		free(F);
		t++;
	}
	printf("Terminado. Número de iteraciones: %d\n", t);

	delete_arr2d_i(X, args->npop);
	delete_arr1d((void *)P);
	return xbest;
}