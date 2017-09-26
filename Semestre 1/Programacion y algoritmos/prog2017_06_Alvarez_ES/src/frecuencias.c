#include "memo.h"
#include "frecuencias.h"

int frec_comparator(const void *f1, const void *f2) {
	const FRECROW *of1 = (FRECROW *)f1;
	const FRECROW *of2 = (FRECROW *)f2;
	return (of1->frec < of2->frec); 
}

void str_to_lower(char *str) {
	int n = (int)strlen(str);
	for(int i = 0; i < n; i++) {
		str[i] = tolower(str[i]);
	}
}

//Busca una cierta palabra en el diccionario, si esta se encuentra
//Retorna la posición, si no, retorna -1.
int is_word_in_dict(char *str, char **dict, int pa) {
	int len = (int)strlen(str);
	for(int i = 0; i < pa; i++) {
		if(strcmp(dict[i], str) == 0)
			return i;
	}
	return -1;
}

//Esta función añade una nueva palabra al final del diccionario.
//En caso de estar lleno, crea expande la memoria del mismo.
char** add_word_to_dict(char *str, char **dict, int dict_size, int pa, int *pinserted, int *realocated) {
	//Se asume que la palabra ya se encuentra en minúsculas
	int ppos = is_word_in_dict(str, dict, pa);
	//La palabra ya existe en el diccionario
	if(ppos != -1) {
		*realocated = 0;
		*pinserted = ppos;
		return dict;
	}
	else {
		//Hay que expandir la memoria del diccionario
		if(pa == dict_size) {
			dict = (char **)realloc(dict, (dict_size + 10) * sizeof(char *));
			for(int i = dict_size; i < dict_size + 10; i++) {
				dict[i] = (char *)create_arr1d(1, sizeof(char));
			}
			//printf("Realocado\n");
			*realocated = 1;
		}
		else {
			*realocated = 0;
		}

		//En este punto el diccionario tiene memoria para la nueva palabra
		int len = (int)strlen(str);
		dict[pa] = (char *)realloc(dict[pa], (len + 1) * sizeof(char));
		strcpy(dict[pa], str);
		*pinserted = pa;

		return dict;
	}
}

//Nota: cur_file ya está indexado a cero
int** update_hist(int **hist, int pinserted, int dict_size, int realocated, int cur_file, int no_files) {
	if(realocated) {
		hist = (int **)realloc(hist, (dict_size + 10) * sizeof(int *));
		for(int i = dict_size; i < dict_size + 10; i++) {
			hist[i] = (int *)create_arr1d(no_files, sizeof(int));
			for(int j = 0; j < no_files; j++)
				hist[i][j] = 0;
		}
	}
	hist[pinserted][cur_file]++;
	return hist;
}

//Convierte la matríz de frecuencias a una de frecuencias relativas
//Nota: la matríz resultante es transpuesta de la original
double** convert_to_relative(int **hist, int *tot_per_block, int pa, int no_files) {
	double **res;
	//res = create_arr2d_by_chunks_d(pa, no_files);
	res = create_arr2d_by_chunks_d(no_files, pa);
	for(int i = 0; i < pa; i++)
		for(int j = 0; j < no_files; j++)
			res[j][i] = (double)hist[i][j] / (double)tot_per_block[j];

	return res;
}

//Toma el diccionario y la matríz de frecuencias relativas y los imprime en
//archivos distintos
void print_words(char **dict, double **hist, int pa, int cnt, int no_files) {
	FILE *words, *frequencies;
	words = fopen("words.txt", "w");
	for(int i = 0; i < pa; i++) {
		fprintf(words, "%s\n", dict[i]);
	}
	fclose(words);

	frequencies = fopen("frequencies.txt", "w");
	for(int i = 0; i < pa; i++) {
		for(int j = 0; j < no_files; j++) {
			fprintf(frequencies, "%lf", hist[j][i]);
			if(j < no_files - 1)
				fprintf(frequencies, " ");
		}
		fprintf(frequencies, "\n");
	}
	fclose(frequencies);
}

double** generate_frec(char *files_name, int n_files, int *no_words) {
	FILE *in;
	int word_size = 30, cur_file;
	int pa = 0, dict_size = 10;
	int **hist, *tot_per_block, cnt = 0;
	char word[word_size], out_name[30];
	char **dict;

	//Crear la matríz por bloques con un tamaño inicial de 10 posiciones
	dict = create_arr2d_by_chunks_c(10, 1);

	//Crear la matriz que fungirá como histograma
	hist = create_arr2d_by_chunks_i(10, n_files);
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < n_files; j++) {
			hist[i][j] = 0;
		}
	}
	tot_per_block = (int *)create_arr1d(n_files, sizeof(int));
	for(int i = 0; i < n_files; i++) tot_per_block[i] = 0;

	for(cur_file = 1; cur_file <= n_files; cur_file++) {
		sprintf(out_name, "%s_%d.txt", files_name, cur_file);
		//No se pudo abrir el archivo, liberamos todo y salimos
		in = fopen(out_name, "r");

		//Leer archivo palabra por palabra
		while(fscanf(in, "%s", word) == 1) {
			cnt++;
			tot_per_block[cur_file - 1]++;
			str_to_lower(word);
			int pinserted = 0, realocated = 0;
			dict = add_word_to_dict(word, dict, dict_size, pa, &pinserted, &realocated);
			hist = update_hist(hist, pinserted, dict_size, realocated, cur_file - 1, n_files);

			if(pinserted == pa)
				pa++;
			if(realocated)
				dict_size += 10;
		}
		fclose(in);
	}

	double **res = convert_to_relative(hist, tot_per_block, pa, n_files);
	print_words(dict, res, pa, cnt, n_files);
	*no_words = pa;

	printf("Terminado: %d palabras diferentes, %d palabras totales.\n", pa, cnt);
	delete_arr1d((void *)tot_per_block);
	delete_arr2d_c(dict, dict_size);
	delete_arr2d_i(hist, dict_size);

	return res;
}

//Obtiene las palabras con mejor frecuencia.
//La matríz está constituida por: nr - bloques, nc - palabras
double** get_best_frequencies(double **frec, int nr, int nc, int nfrec) {
	FRECROW frec_table[nc];
	double **res = create_arr2d_by_chunks_d(nr, nfrec);
	//Número de palabras
	for(int i = 0; i < nc; i++) {
		//Número de bloques
		double sum = 0.0;
		for(int j = 0; j < nr; j++) {
			sum += frec[j][i];
		}
		frec_table[i].id = i;
		frec_table[i].frec = sum;
	}

	qsort(frec_table, nc, sizeof(FRECROW), frec_comparator);

	for(int i = 0; i < nfrec; i++) {
		for(int j = 0; j < nr; j++) {
			res[j][i] = frec[j][frec_table[i].id];
		}
	}

	return res;
}