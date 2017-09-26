#ifndef METRICAS_CALIDAD_H
#define METRICAS_CALIDAD_H

#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "separador.h"
#include "frecuencias.h"

typedef struct argsObj {
	char fbname[30], lbname[30], quality_metric[30];
	int nff, nfl, seed;
	int nwords, nfeat, npop, niter;
} ARGSOBJ;

typedef struct fobj {
	//Conjuntos de entrenamiento y prueba
	int *trying_set1;
	int *trying_set2;

	//Matrices de frecuencias
	double **m1;
	double **m2;

	//Número de filas de las matrices de frecuencias
	int m1_sz;
	int m2_sz;
	int no_words;

	double (*quality_metric)(int, int, int, int);
} FOBJ;

#include "funciones.h"

int* copy_vector_i_fobj(int *ori, int n);

double** copy_matrix_d_fobj(double **ori, int nr, int nc);

FOBJ* create_clasifier_params(int *trying_set1, int *trying_set2, double **m1, double **m2, int m1_sz, int m2_sz, int no_words);

FOBJ* mem_obj_alloc(ARGSOBJ *args);

FOBJ* clone_obj(FOBJ *ori);

FOBJ* free_obj_mem(FOBJ *obj);

/*  --------------- Quality metrics section ---------------  */

double accuracy_metric(int p, int n, int tp, int tn);

double sensitivity_metric(int p, int n, int tp, int tn);

double specificity_metric(int p, int n, int tp, int tn);

double precision_metric(int p, int n, int tp, int tn);

double negative_pvalue_metric(int p, int n, int tp, int tn);

double balanced_accuracy_metric(int p, int n, int tp, int tn);

double f1_score_metric(int p, int n, int tp, int tn);

FOBJ* set_quality_metric(FOBJ *obj, char *metric);

#endif