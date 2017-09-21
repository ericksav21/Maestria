#include "apuntadores.h"

unsigned char **umatriz(int nrow, int ncol) {
	unsigned char **mat = (unsigned char**)malloc(sizeof(unsigned char*) * nrow);
	if (mat)
		for (int i = 0; i < nrow; i++)
			mat[i] = (unsigned char*)malloc(sizeof(unsigned char) * ncol);
	return mat;    
}

void freeMat(unsigned char **mat, int nrow) {
	for (int i = 0; i < nrow; i++)
		free(mat[i]);
	free(mat);
}