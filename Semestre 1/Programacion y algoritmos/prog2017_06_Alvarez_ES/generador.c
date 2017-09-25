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

int *get_best_bv(ARGSOBJ *args, FOBJ *params) {
	int n_bstf = args->nwords, t = 0;
	int **X = create_arr2d_by_chunks_i(args->npop, n_bstf);
	int *xbest = (int *)create_arr1d(n_bstf, sizeof(int));
	double *P = (double *)create_arr1d(n_bstf, sizeof(double));
	for(int i = 0; i < n_bstf; i++) {
		P[i] = 0.5;
	}
	for(int i = 0; i < args->npop; i++) {
		X[i] = generate_bv(X[i], P, n_bstf, args->nfeat);
	}
	//Criterio de convergencia
	while(t < args->niter) {
		FRECROW *F = (FRECROW *)malloc(sizeof(FRECROW) * args->npop);
		for(int i = 0; i < args->npop; i++) {
			printf("Realizando evaluación... ");
			double quality = metric_eval(params, X[i]);
			printf("Terminado.\n");
			F[i].id = i;
			F[i].frec = quality;
		}

		qsort(F, args->npop, sizeof(FRECROW), frec_comparator);


	}

	delete_arr2d_i(X, args->npop);
	delete_arr1d((void *)P);
	return xbest;
}