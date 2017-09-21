#include "apuntadores.h"

int llenaVector(int *x, int n) {
	for(int i = 0; i < n; i++)
		x[i] = i;
	return 0;
}
