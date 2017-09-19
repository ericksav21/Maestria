#include "metricas_calidad.h"

int* copy_vector_i_fobj(int *ori, int n) {
	int *dest = (int *)create_arr1d(n, sizeof(n));
	for(int i = 0; i < n; i++) {
		dest[i] = ori[i];
	}

	return dest;
}

double** copy_matrix_d_fobj(double **ori, int nr, int nc) {
	double **dest = create_arr2d_by_chunks_d(nr, nc);
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			dest[i][j] = ori[i][j];
		}
	}

	return dest;
}

FOBJ* create_clasifier_params(int *trying_set1, int *trying_set2, double **m1, double **m2, int m1_sz, int m2_sz, int no_words) {
	FOBJ *obj = (FOBJ *)malloc(sizeof(FOBJ));
	obj->trying_set1 = copy_vector_i_fobj(trying_set1, m1_sz);
	obj->trying_set2 = copy_vector_i_fobj(trying_set2, m2_sz);
	obj->m1 = copy_matrix_d_fobj(m1, m1_sz, no_words);
	obj->m2 = copy_matrix_d_fobj(m2, m2_sz, no_words);
	obj->m1_sz = m1_sz;
	obj->m2_sz = m2_sz;
	obj->no_words = no_words;
	obj->quality_metric = accuracy_metric;

	return obj;
}

FOBJ* free_obj_mem(FOBJ *obj) {
	if(obj->trying_set1 != NULL) delete_arr1d((void *)obj->trying_set1);
	if(obj->trying_set2 != NULL) delete_arr1d((void *)obj->trying_set2);
	if(obj->m1 != NULL) delete_arr2d_d(obj->m1, obj->m1_sz);
	if(obj->m2 != NULL) delete_arr2d_d(obj->m2, obj->m2_sz);

	obj->trying_set1 = NULL;
	obj->trying_set2 = NULL;
	obj->m1 = NULL;
	obj->m2 = NULL;
	obj->quality_metric = NULL;
	obj->m1_sz = 0;
	obj->m2_sz = 0;
	obj->no_words = 0;

	return obj;
}

/*  --------------- Quality metrics section ---------------  */

double accuracy_metric(int p, int n, int tp, int tn) {
	return (double)(tp + tn) / (double)(p + n);
}

double sensitivity_metric(int p, int n, int tp, int tn) {
	int fn = n - tn;
	return (double)tp / (double)(tp + fn);
}

double specificity_metric(int p, int n, int tp, int tn) {
	int fp = p - tp;
	return (double)(p + n) / (double)(tn + fp);
}

double negative_pvalue_metric(int p, int n, int tp, int tn) {
	int fn = n - tn;
	return (double)tn / (double)(tn + fn);
}

FOBJ* set_quality_metric(FOBJ *obj, char *metric) {
	if(strcmp(metric, "accuracy") == 0) {
		obj->quality_metric = accuracy_metric;
	}

	return obj;
}