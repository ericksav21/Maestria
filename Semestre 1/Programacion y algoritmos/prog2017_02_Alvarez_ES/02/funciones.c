#include <stdio.h>
#include "funciones.h"

//32: Espacio, 9: Tabulación horizontal, 10: Salto de línea
int is_separator(char c) {
	int aux = (int)c;
	if(aux == 32 || aux == 9 || aux == 10)
		return 1;
	return 0;
}

int is_number(char c) {
	int aux = (int)c;
	if(aux >= 48 && aux <= 57)
		return 1;
	return 0;
}

int is_letter(char c) {
	int aux = (int)c;
	if((aux >= 97 && aux <= 122) || (aux >= 65 && aux <= 90))
		return 1;
	return 0;
}

int is_char_valid(char c) {
	if(is_separator(c))
		return 1;
	else if(is_number(c))
		return 1;
	else if(is_letter(c))
		return 1;

	return 0;
}

void proc(FILE *in, char *new_name) {
	FILE *out;
	int cnt_f = 1, cnt_char = 0, is_sep = 0;
	char c, out_name[30];

	//Se genera el primer archivo de texto de salida
	sprintf(out_name, new_name, cnt_f++);
	out = fopen(out_name, "w");

	while(!feof(in)) {
		c = (char)fgetc(in);
		if(!is_char_valid(c))
			continue;
		if(is_separator(c)) {
			if(is_sep)
				continue;
			is_sep = 1;
			fputc(' ', out);
			cnt_char++;
		}
		else {
			//En este punto el caracter actual es válido
			fputc(c, out);
			cnt_char++;
			is_sep = 0;
		}

		//Se cierra el archivo actual y se crea uno nuevo con un nuevo nombre
		if(cnt_char == 5000) {
			fclose(out);
			sprintf(out_name, new_name, cnt_f++);
			out = fopen(out_name, "w");
			cnt_char = 0;
		}
	}

	printf("Proceso terminado.\n");

	fclose(out);
}
