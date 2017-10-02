#include <stdio.h>
#include <stdlib.h>

#include "promedio.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta: ./main [N]\n");
		return 0;
	}

	int n = atoi(argv[1]);
	printf("Promedio con %d números: %lf\n", n, get_avr(n));

	return 0;
}