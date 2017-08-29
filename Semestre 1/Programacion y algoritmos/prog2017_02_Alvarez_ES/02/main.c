#include "funciones.h"

int main() {
	FILE *in;
	char files_name[20], new_name[30];
	char formater[8] = {'_', '%', 'd', '.', 't', 'x', 't', '\0'};

	printf("Nombre del archivo: ");
	scanf("%s", files_name);
	if((in = fopen(files_name, "r")) == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return 0;
	}

	//Se genera el arreglo 'formater' que servirá para crear los
	//diferentes archivos
	int p = 0;
	while(files_name[p] != '.') {
		new_name[p] = files_name[p];
		p++;
	}

	for(int i = 0; i < 8; i++) {
		new_name[p++] = formater[i];
	}

	proc(in, new_name);
	fclose(in);

	return 0;
}
