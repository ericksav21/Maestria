#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	srand(time(NULL));
	int n;
	double *x0 = read_init_point(argv[1], &n);
	r_confidence(x0, 10000, n);

	free_vector(x0);

	return 0;
}