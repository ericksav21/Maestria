#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "utils.h"
#include "met_num.h"

int main(int argc, char **argv) {
	int nr, nc;
	double **X = read_matrix(argv[1], &nr, &nc);
	double mean[2];
	mean[0] = 0.4074;
	mean[1] = 0.1901;
	double **S = PCA_g(X, mean, nr, nc, 2, 0.2);

	free_matrix(X);
	//free_matrix(S);
	return 0;
}