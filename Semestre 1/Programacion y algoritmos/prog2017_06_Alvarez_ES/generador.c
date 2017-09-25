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
	int *xbest = (int *)create_arr1d(n_bstf, sizeof(int));
	double *P = (double *)create_arr1d(n_bstf, sizeof(double));
	for(int i = 0; i < n_bstf; i++) {
		P[i] = 0.5;
	}

	//Criterio de convergencia
	while(vb_xnorm(P, n_bstf) > (1.0 / pow(n_bstf, 2)) || t < args->niter) {
		//Generar la matríz de vectores binarios
		for(int i = 0; i < args->npop; i++) {
			X[i] = generate_bv(X[i], P, n_bstf, args->nfeat);
		}

		FRECROW *F = (FRECROW *)malloc(sizeof(FRECROW) * args->npop);
		for(int i = 0; i < args->npop; i++) {
			printf("Realizando evaluación... ");
			double quality = metric_eval(params, X[i]);
			printf("Terminado.\n");
			F[i].id = i;
			F[i].frec = quality;
		}

		qsort(F, args->npop, sizeof(FRECROW), frec_comparator);

		//Copiar el mejor vector
		int ind = F[0].id;
		for(int i = 0; i < n_bstf; i++) {
			xbest[i] = X[ind][i];
		}

		//Actualizar el vector de probabilidades
		printf("Vector de probabilidades:\n");
		for(int i = 0; i < n_bstf; i++) {
			double pi = 0.0;
			for(int j = 0; j < (int)(args->npop / 2); j++) {
				pi += X[j][i];
			}
			P[i] = pi / ((double)args->npop / 2.0);
			printf("%lf ", P[i]);
		}
		printf("\n");
		t++;
	}
	printf("Terminado. Número de iteraciones: %d\n", t);

	delete_arr2d_i(X, args->npop);
	delete_arr1d((void *)P);
	return xbest;
}