#ifndef APUNTADORES_H 
#define APUNTADORES_H

#include <stdio.h>
#include <stdlib.h>

//Definicion de tipo para estructura
typedef struct DMATRIZ {
	int **data;
	int nrow, ncol;
} DMATRIZ;

typedef struct DVECTOR {
	int *data;
	int n;
} DVECTOR;

//Funciones para requerir y devolver memoria
DMATRIZ dmatriz(int nrow, int ncol);

DVECTOR vector(int n);

DMATRIZ llenaMat(DMATRIZ A);

DVECTOR llenaVector(DVECTOR x);

DMATRIZ freeDMat(DMATRIZ A);

DVECTOR freeVec(DVECTOR x);

//Funcion para hacer la multiplicacion matriz-vector
DVECTOR multiMatVec(DMATRIZ A, DVECTOR x, DVECTOR b);

#endif
