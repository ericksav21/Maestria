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
int** generate_trying_set(int **set, int no_blocks) {
	int sz = (int)((float)no_blocks * 0.3);
	int cnt = 0;
	while(cnt < sz) {
		int rn = rand() % no_blocks;
		if(set[rn][0] == 0) {
			set[rn][0] = 1;
			set[rn][1] = 0;
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

void train(int i, double **m1, double **m2, int *bin_vector, int **trying_set, int m_sz, int val_to_set, double *d_min, int *c_dat, int no_words) {
	double d_aux;
	for(int j = 0; j < m_sz; j++) {
		//Valor de entrenamiento!!
		if(trying_set[j][0] == 0) {
			d_aux = distance(m1[i], m2[j], bin_vector, no_words);
			if(d_aux < *d_min) {
				*d_min = d_aux;
				*c_dat = val_to_set;
			}
		}
	}
}

void clasify(int **trying_set1, int **trying_set2, int *bin_vector, double **m1, double **m2, int m1_sz, int m2_sz, int no_words) {
	FILE *out = fopen("clasified.txt", "w");
	fprintf(out, "Bloque Clase esperada Clase obtenida\n");

	//Iteramos sobre el conjunto de datos y los que son de tipo prueba
	//los clasificamos
	for(int i = 0; i < m1_sz; i++) {
		//Valor de prueba detectado
		if(trying_set1[i][0] == 1) {
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;

			train(i, m1, m1, bin_vector, trying_set1, m1_sz, 1, &d_min, &c_dat, no_words);
			train(i, m1, m2, bin_vector, trying_set2, m2_sz, 2, &d_min, &c_dat, no_words);

			fprintf(out, "%d %d %d\n", i + 1, 1, c_dat);
		}
	}

	for(int i = 0; i < m2_sz; i++) {
		//Valor de prueba detectado
		if(trying_set2[i][0] == 1) {
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;
			train(i, m2, m1, bin_vector, trying_set1, m1_sz, 1, &d_min, &c_dat, no_words);
			train(i, m2, m2, bin_vector, trying_set2, m2_sz, 2, &d_min, &c_dat, no_words);

			fprintf(out, "%d %d %d\n", m1_sz + i, 2, c_dat);
		}
	}

	printf("Terminado.\n");
	fclose(out);
}

void close_items(int **tsc1, int **tsc2, int *bv, double **fc1, double **fc2, double **frec, int m1sz, int m2sz, int frec_size) {
	delete_arr1d(bv);
	delete_arr2d_i(tsc1, m1sz);
	delete_arr2d_i(tsc2, m2sz);
	delete_arr2d_d(fc1, m1sz);
	delete_arr2d_d(fc2, m2sz);
	delete_arr2d_d(frec, frec_size);
}