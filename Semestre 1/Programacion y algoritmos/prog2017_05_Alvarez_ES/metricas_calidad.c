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

FOBJ* mem_obj_alloc(char *first_books_name, char *last_books_name, int n_files_fb, int n_files_lb) {
	//Fabricamos los bloques de archivos
	int n_c_fb, n_c_lb;
	printf("**---------- Separador de archivos ----------**\n");
	n_c_fb = f_separate(first_books_name, n_files_fb, 1);
	n_c_lb = f_separate(last_books_name, n_files_lb, n_c_fb + 1);

	//Generamos la tabla de frecuencias
	printf("\n**---------- Generador de frecuencias ----------**\n");
	int no_words = 0, frec_size = n_c_lb;

	double **frec = generate_frec("chunked", n_c_lb, &no_words);

	//Se generan las matrices de las clases 1 y 2
	printf("\n**---------- Clasificador de texto ----------**\n");
	printf("Generando las clases.\n");
	//Tamaño: n_c_fb
	double **frec_c1 = get_part_of_matrix(frec, 0, n_c_fb - 1, no_words);
	//Tamaño: n_c_lb
	double **frec_c2 = get_part_of_matrix(frec, n_c_fb, n_c_lb - 1, no_words);

	int m1sz = n_c_fb, m2sz = n_c_lb - n_c_fb;

	//Generar los conjuntos de entrenamiento y prueba
	//frec_size = Num de bloques en general
	printf("Generando los conjuntos de entrenamiento y prueba.\n");
	int *trying_set_c1 = generate_trying_set(m1sz);
	int *trying_set_c2 = generate_trying_set(m2sz);

	//Generar el objeto con los parámetros para la clasificación
	FOBJ *params = create_clasifier_params(trying_set_c1, trying_set_c2, frec_c1, frec_c2, m1sz, m2sz, no_words);
	//Ya no se necesita más a estos objetos
	close_items(trying_set_c1, trying_set_c2, frec_c1, frec_c2, frec, m1sz, m2sz, frec_size);

	return params;
}

//Se asume que el objecto ori está inicializado
FOBJ* clone_obj(FOBJ *ori) {
	FOBJ *dest = (FOBJ *)malloc(sizeof(FOBJ));
	dest->trying_set1 = copy_vector_i_fobj(ori->trying_set1, ori->m1_sz);
	dest->trying_set2 = copy_vector_i_fobj(ori->trying_set2, ori->m2_sz);
	dest->m1 = copy_matrix_d_fobj(ori->m1, ori->m1_sz, ori->no_words);
	dest->m2 = copy_matrix_d_fobj(ori->m2, ori->m2_sz, ori->no_words);
	dest->m1_sz = ori->m1_sz;
	dest->m2_sz = ori->m2_sz;
	dest->no_words = ori->no_words;
	dest->quality_metric = ori->quality_metric;

	return dest;
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
	return (double)tn / (double)(tn + fp);
}

double precision_metric(int p, int n, int tp, int tn) {
	int fp = p - tp;
	return (double)tp / (double)(tp + fp);
}

double negative_pvalue_metric(int p, int n, int tp, int tn) {
	int fn = n - tn;
	return (double)tn / (double)(tn + fn);
}

double balanced_accuracy_metric(int p, int n, int tp, int tn) {
	return ((double)tp / (double)p + (double)tn / (double)n) / 2.0;
}

double f1_score_metric(int p, int n, int tp, int tn) {
	int fp = p - tp;
	int fn = n - tn;
	return (double)(2.0 * tp) / (double)(2.0 * tp + fp + fn);
}

FOBJ* set_quality_metric(FOBJ *obj, char *metric) {
	if(strcmp(metric, "accuracy") == 0) {
		obj->quality_metric = accuracy_metric;
	}
	else if(strcmp(metric, "sensitivity") == 0) {
		obj->quality_metric = sensitivity_metric;
	}
	else if(strcmp(metric, "specificity") == 0) {
		obj->quality_metric = specificity_metric;
	}
	else if(strcmp(metric, "precision") == 0) {
		obj->quality_metric = precision_metric;
	}
	else if(strcmp(metric, "negative") == 0) {
		obj->quality_metric = negative_pvalue_metric;
	}
	else if(strcmp(metric, "balanced accuracy") == 0) {
		obj->quality_metric = balanced_accuracy_metric;
	}
	else if(strcmp(metric, "f1 score") == 0) {
		obj->quality_metric = f1_score_metric;
	}
	else {
		printf("No se encontró la métrica especificada.\n");
	}

	return obj;
}