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