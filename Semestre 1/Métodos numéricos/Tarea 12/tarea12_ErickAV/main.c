#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memo.h"
#include "met_num.h"
#include "matriz_vector.h"

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Error. Ejecuta: %s [N].\n", argv[0]);
		return 0;
	}
	int n = atoi(argv[1]);
	solve(0, 5, n);	

	return 0;
}