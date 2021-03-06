#ifndef MEMO_H
#define MEMO_H

#include <stdlib.h>

/*
	Esta librería contiene funciones para pedir y liberar
	memoria para matrices y vectores
*/ 

/* Macros para simplificar las llamadas a funciones */
#define create_vector(sz, type) (type *)create_matrix_1d(sz, sizeof(type))
#define create_matrix(nr, nc, type) (type **)create_matrix_2d(nr, nc, sizeof(type))
#define free_vector(v) free_matrix_1d((void *)v)
#define free_matrix(m) free_matrix_2d((void **)m)

/* Genera un vector de tamaño n */
void *create_matrix_1d(int sz, size_t type_size);

/* Genera una matriz continua de tamaño nr * nc */
void **create_matrix_2d(int nr, int nc, size_t type_size);

/* Libera un vector */
void free_matrix_1d(void *v);

/* Libera una matriz */
void free_matrix_2d(void **m);

#endif