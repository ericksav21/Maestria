#include "memo.h"
#include "fpalabras.h"

void str_to_lower(char *str) {
	int n = (int)strlen(str);
	for(int i = 0; i < n; i++) {
		str[i] = tolower(str[i]);
	}
}

//Copia un diccionario a uno nuevo, Nota: el nuevo
//debe estar vacío.
char** copy_dict(char **src, char **dest, int src_size) {
	for(int i = 0; i < src_size; i++) {
		int len = (int)strlen(src[i]);
		dest[i] = (char *)create_arr1d(len + 1, sizeof(char));
		strcpy(dest[i], src[i]);
	}

	return dest;
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
char** add_word_to_dict(char *str, char **dict, int **hist, int dict_size, int pa, int *pinserted, int *realocated, int cur_file, int no_files) {
	//Se asume que la palabra ya se encuentra en minúsculas
	int ppos = is_word_in_dict(str, dict, pa);
	//La palabra ya existe en el diccionario
	if(ppos != -1) {
		*realocated = 0;
		*pinserted = ppos;
		(*hist)[ppos]++;
		return dict;
	}
	else {
		//Hay que expandir la memoria del diccionario
		if(pa == dict_size) {
			char **dict_aux;
			dict_aux = (char **)realloc(dict, (dict_size + 10) * sizeof(char *));
			dict = dict_aux;
			(*hist) = (int *)realloc((*hist), (dict_size + 10) * sizeof(int));
			*realocated = 1;
		}
		else {
			*realocated = 0;
		}

		//En este punto el diccionario tiene memoria para la nueva palabra
		int len = (int)strlen(str);
		dict[pa] = (char *)create_arr1d(len + 1, sizeof(char));
		(*hist)[pa] = 0;
		strcpy(dict[pa], str);
		(*hist)[pa]++;
		*pinserted = pa;

		return dict;
	}
}

void print_words(char **dict, int *hist, int pa, int cnt) {
	FILE *out;
	out = fopen("histogram.txt", "w");
	fprintf(out, "Palabras Frecuencia relativa.\n");
	for(int i = 0; i < pa; i++) {
		fprintf(out, "%s %f\n", dict[i], (float)hist[i] / (float)cnt);
	}
	fclose(out);
}

void proc() {
	FILE *in;
	int word_size = 30, n_files, cur_file;
	int pa = 0, dict_size = 10;
	int *hist, cnt = 0;
	char word[word_size], files_name[20], out_name[30];
	char **dict;
	printf("Nombre del archivo: ");
	scanf("%s", files_name);
	printf("Número de archivos: ");
	scanf("%d", &n_files);
	//Crear la matríz por bloques con un tamaño inicial de 10 posiciones
	dict = (char **)create_arr2d_by_chunks(10, 0, sizeof(char));
	//Crear el arreglo que fungirá como histograma
	hist = (int *)create_arr1d(10, sizeof(int));
	for(int i = 0; i < 10; i++)
		hist[i] = 0;
	for(cur_file = 1; cur_file <= n_files; cur_file++) {
		sprintf(out_name, "%s_%d.txt", files_name, cur_file);
		//No se pudo abrir el archivo, liberamos todo y salimos
		if((in = fopen(out_name, "r")) == NULL) {
			printf("Error al abrir el archivo.\n");
			if(dict != NULL)
				delete_arr2d((void **)dict, dict_size, 1);
			if(hist != NULL)
				delete_arr2d((void **)hist, dict_size, 1);

			return;
		}
		//Leer archivo palabra por palabra
		while(fscanf(in, "%s", word) == 1) {
			cnt++;
			str_to_lower(word);
			int pinserted = 0, realocated = 0;
			dict = add_word_to_dict(word, dict, &hist, dict_size, pa, &pinserted, &realocated, cur_file, n_files);

			if(pinserted == pa)
				pa++;
			if(realocated)
				dict_size += 10;
		}
		print_words(dict, hist, pa, cnt);
		fclose(in);
	}

	printf("Terminado: %d palabras diferentes, %d palabras totales.\n", pa, cnt);
	delete_arr2d((void **)dict, dict_size, 1);
	delete_arr1d((void *)hist);
}
