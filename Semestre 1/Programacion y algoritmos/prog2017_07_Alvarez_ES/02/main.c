#include <stdio.h>
#include <stdlib.h>

#include "promedio.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta: %s [N]\n", argv[0]);
		return 0;
	}

	int n = atoi(argv[1]);
	printf("Promedio con %d números: %.2f\n", n, get_avr(n));

	return 0;
}