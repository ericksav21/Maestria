#include "apuntadores.h"

//Funciones para requerir y devolver memoria
DMATRIZ dmatriz(int nrow, int ncol) {
	DMATRIZ res;
	res.nrow = nrow;
	res.ncol = ncol;
	res.data = (int **)malloc(sizeof(int *) * nrow);
	for(int i = 0; i < nrow; i++) {
		res.data[i] = (int *)malloc(sizeof(int) * ncol);
	}

	return res;
}

DVECTOR vector(int n) {
	DVECTOR res;
	res.n = n;
	res.data = (int *)malloc(sizeof(int) * n);

	return res;
}

DMATRIZ llenaMat(DMATRIZ A) {
	for(int i = 0; i < A.nrow; i++) {
		for(int j = 0; j < A.ncol; j++) {
			A.data[i][j] = (j + 1);
		}
	}

	return A;
}

DVECTOR llenaVector(DVECTOR x) {
	for(int i = 0; i < x.n; i++) {
		x.data[i] = 1;
	}

	return x;
}

DMATRIZ freeDMat(DMATRIZ A) {
	for(int i = 0; i < A.nrow; i++) {
		free(A.data[i]);
	}
	free(A.data);
	A.nrow = 0;
	A.ncol = 0;

	return A;
}

DVECTOR freeVec(DVECTOR x) {
	free(x.data);
	x.n = 0;

	return x;
}

//Funcion para hacer la multiplicacion matriz-vector
DVECTOR multiMatVec(DMATRIZ A, DVECTOR x, DVECTOR b) {
	if(!b.data)
		b = llenaVector(b);

	for(int i = 0; i < A.nrow; i++) {
		int aux = 0;
		for(int j = 0; j < A.ncol; j++) {
			aux += (A.data[i][j] * x.data[j]);
		}
		b.data[i] = aux;
	}

	return b;
}