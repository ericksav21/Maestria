#include "funciones.h"

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

void clasify(int **trying_set1, int **trying_set2, int *bin_vector, double **m1, double **m2, int m1_sz, int m2_sz, int no_words) {
	FILE *out = fopen("clasified.txt", "w");
	fprintf(out, "Bloque Clase esperada Clase obtenida\n");

	//Iteramos sobre el conjunto de datos y los que son de tipo prueba
	//los clasificamos
	for(int i = 0; i < m1_sz; i++) {
		//Valor de prueba detectado
		if(trying_set1[i][1] == 0) {
			//printf("i: %d\n", i);
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;
			for(int j = 0; j < m1_sz; j++) {
				//Valor de entrenamiento!!
				if(trying_set1[j][0] == 1) {
					//printf("j1: %d\n", j);
					d_aux = distance(m1[i], m1[j], bin_vector, no_words);
					if(d_aux < d_min) {
						d_min = d_aux;
						c_dat = 1;
					}
				}
			}

			for(int j = 0; j < m2_sz; j++) {
				//Valor de entrenamiento!!
				if(trying_set2[j][0] == 1) {
					//printf("j2: %d\n", j);
					d_aux = distance(m1[i], m2[j], bin_vector, no_words);
					if(d_aux < d_min) {
						d_min = d_aux;
						c_dat = 2;
					}
				}
			}

			//trying_set1[i][1] = c_dat;
			fprintf(out, "%d %d %d\n", i + 1, 1, c_dat);
		}
	}

	for(int i = 0; i < m2_sz; i++) {
		//Valor de prueba detectado
		if(trying_set2[i][1] == 0) {
			//Clasificar con los datos de la clase 1
			double d_min = DBL_MAX, d_aux;
			int c_dat = 0;
			for(int j = 0; j < m1_sz; j++) {
				//Valor de entrenamiento!!
				if(trying_set1[j][0] == 1) {
					d_aux = distance(m2[i], m1[j], bin_vector, no_words);
					if(d_aux < d_min) {
						d_min = d_aux;
						c_dat = 1;
					}
				}
			}

			for(int j = 0; j < m2_sz; j++) {
				//Valor de entrenamiento!!
				if(trying_set2[j][0] == 1) {
					d_aux = distance(m2[i], m2[j], bin_vector, no_words);
					if(d_aux < d_min) {
						d_min = d_aux;
						c_dat = 2;
					}
				}
			}

			//trying_set2[i][1] = c_dat;
			fprintf(out, "%d %d %d\n", m1_sz + i, 2, c_dat);
		}
	}

	fclose(out);
}