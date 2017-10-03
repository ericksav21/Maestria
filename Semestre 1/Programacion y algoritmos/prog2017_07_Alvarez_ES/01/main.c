#include <stdio.h>
#include <stdlib.h>

#include "impares.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta: %s [N]\n", argv[0]);
		return 0;
	}

	int n = atoi(argv[1]);
	printf("Suma de impares hasta %d: %d\n", n, get_odd_numbers(n));

	return 0;
}