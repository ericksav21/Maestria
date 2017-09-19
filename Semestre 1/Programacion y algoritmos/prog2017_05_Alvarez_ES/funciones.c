#include "funciones.h"

//Lee argumentos y regresa un entero, si pudo
//leerlos todos o no
int read_args(int argc, char **argv, char fbname[30], char lbname[30], int *nff, int *nfl, int *seed) {
	if(argc < 5) {
		printf("Ingrese los siguientes argumentos:\n");
		printf("[Nombre base de los primeros libros] [Numero de libros (1)] ");
		printf("[Nombre base de los ultimos libros] [Numero de libros (2)] ");
		printf("[Semilla (opcional)]\n");
		return 0;
	}

	strcpy(fbname, argv[1]);
	strcpy(lbname, argv[3]);
	*nff = atoi(argv[2]);
	*nfl = atoi(argv[4]);

	if(argc >= 6)
		*seed = atoi(argv[5]);

	return 1;
}

//Esta función se encarga de separar los n archivos especificados
//Devuelve el índice del último bloque generado.
int f_separate(char *first_books_name, int n_files_fb, int start_in) {
	FILE *in;
	char formated_name[30];
	int n_chunked = start_in;
	for(int i = 1; i <= n_files_fb; i++) {
		sprintf(formated_name, "%s_%d.txt", first_books_name, i);
		if(!(in = fopen(formated_name, "r"))) {
			printf("Error al separar. No se pudo abrir el archivo %s.\n", formated_name);
			return 0;
		}

		n_chunked = separate(in, n_chunked);

		fclose(in);
	}

	return n_chunked - 1;
}

//30%: 1, 70%: 0
int* generate_trying_set(int no_blocks) {
	int *set = (int *)create_arr1d(no_blocks, sizeof(int));
	for(int i = 0; i < no_blocks; i++) {
		set[i] = 0;
	}

	int sz = (int)((float)no_blocks * 0.3);
	int cnt = 0;
	while(cnt < sz) {
		int rn = rand() % no_blocks;
		if(set[rn] == 0) {
			set[rn] = 1;
			cnt++;
		}
	}

	return set;
}

int* generate_bin_vector(int n) {
	int *arr = (int *)create_arr1d(n, sizeof(int));
	for(int i = 0; i < n; i++) {
		int aux = rand() % 100;
		if(aux >= 0 && aux <= 49)
			arr[i] = 1;
		else
			arr[i] = 0;
	}

	return arr;
}

double distance(double *v1, double *v2, int *bin_vector, int no_words) {
	double res = 0.0;
	for(int i = 0; i < no_words; i++) {
		double aux = v1[i] - v2[i];
		res += (aux * aux * bin_vector[i]);
	}

	return res;
}

void train(int i, double **m1, double **m2, int *bin_vector, int *trying_set, int m_sz, int val_to_set, double *d_min, int *c_dat, int no_words) {
	double d_aux;
	for(int j = 0; j < m_sz; j++) {
		//Valor de entrenamiento!!
		if(trying_set[j] == 0) {
			d_aux = distance(m1[i], m2[j], bin_vector, no_words);
			if(d_aux < *d_min) {
				*d_min = d_aux;
				*c_dat = val_to_set;
			}
		}
	}
}

//void clasify(int **trying_set1, int **trying_set2, int *bin_vector, double **m1, double **m2, int m1_sz, int m2_sz, int no_words) {
void clasify(FOBJ *params, int *bin_vector, int *P, int *N, int *TP, int *TN) {	
	FILE *out = fopen("clasified.txt", "w");
	fprintf(out, "Bloque Clase esperada Clase obtenida\n");

	//Iteramos sobre el conjunto de datos y los que son de tipo prueba
	//los clasificamos
	for(int i = 0; i < params->m1_sz; i++) {
		//Valor de prueba detectado
		if(params->trying_set1[i] == 1) {
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;

			train(i, params->m1, params->m1, bin_vector, params->trying_set1, params->m1_sz, 1, &d_min, &c_dat, params->no_words);
			train(i, params->m1, params->m2, bin_vector, params->trying_set2, params->m2_sz, 2, &d_min, &c_dat, params->no_words);

			fprintf(out, "%d %d %d\n", i + 1, 1, c_dat);
			(*P)++;
			if(c_dat == 1)
				(*TP)++;
		}
	}

	for(int i = 0; i < params->m2_sz; i++) {
		//Valor de prueba detectado
		if(params->trying_set2[i] == 1) {
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;
			train(i, params->m2, params->m1, bin_vector, params->trying_set1, params->m1_sz, 1, &d_min, &c_dat, params->no_words);
			train(i, params->m2, params->m2, bin_vector, params->trying_set2, params->m2_sz, 2, &d_min, &c_dat, params->no_words);

			fprintf(out, "%d %d %d\n", params->m1_sz + i, 2, c_dat);
			(*N)++;
			if(c_dat == 2)
				(*TN)++;
		}
	}

	printf("Terminado.\n");
	fclose(out);
}

double metric_eval(FOBJ *params, int *bin_vector) {
	int P, N, TP, TN;
	P = N = TP = TN = 0;
	clasify(params, bin_vector, &P, &N, &TP, &TN);
	return params->quality_metric(P, N, TP, TN);
}

void close_items(int *tsc1, int *tsc2, double **fc1, double **fc2, double **frec, int m1sz, int m2sz, int frec_size) {
	delete_arr1d((void *)tsc1);
	delete_arr1d((void *)tsc2);
	delete_arr2d_d(fc1, m1sz);
	delete_arr2d_d(fc2, m2sz);
	delete_arr2d_d(frec, frec_size);
}