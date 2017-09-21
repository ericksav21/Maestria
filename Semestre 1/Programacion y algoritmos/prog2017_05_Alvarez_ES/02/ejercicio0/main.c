#include <stdio.h>
#include "apuntadores.h"

int imprimeVector(int *x, int n) {
	for(int i = 0; i < n; i++)
		printf("%d\n", x[i]);

	return 0;
}

int main() {
	int x[10];
	llenaVector(x, 10);
	imprimeVector(x, 10);

	return 0;
}
