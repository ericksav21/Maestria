#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error de ejecución: Indica el nombre del archivo de texto.\n");
		return 0;
	}
	char files_name[30], words[1024];
	FILE *in;
	NODEPTR root = NULL;
	strcpy(files_name, argv[1]);

	in = fopen(files_name, "r");

	while(fscanf(in, "%s", words) == 1) {
		root = add_node(root, words);
	}
	print_list_in_file(root, "lista.txt");
	printf("Terminado.\n");

	free_list(root);
	fclose(in);

	return 0;
}