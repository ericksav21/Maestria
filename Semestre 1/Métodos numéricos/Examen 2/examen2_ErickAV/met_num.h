#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "memo.h"
#include "matriz_vector.h"

/*---------- Calcula el épsilon de la maquina ----------*/
double get_EPS();

/*---------- EQUATION SYSTEM SOLVERS ----------*/
double *solve_mdiagonal(double *d, double *b, int n, double tol);

/*---------- Reuelve un sistema donde la matriz es triangular inferior ----------*/
double *solve_mlower(double **A, double *b, int nr, int nc, double tol);

/*---------- Reuelve un sistema donde la matriz es triangular superior ----------*/
double *solve_mupper(double **A, double *b, int nr, int nc, double tol);

/* 
	Realiza la factorización LU a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada no necesariamente simétrica.
	-L, U: Puntero a matrices de la misma dimensión de A que se convertirán en las factorizadas.
	-n: Las dimensiones de la matriz.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
int factorize_LU(double **A, double ***L, double ***U, int n, double tol);

/* 
	Realiza la factorización LDLt a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada simétrica y no singular.
	-L, D, LT: Puntero a matrices de la misma dimensión de A que se convertirán en las factorizadas, D se guarda como
				vector.
	-n: Las dimensiones de la matriz.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
int LDLT(double **A, double ***L, double **D, double ***Lt, int n, double tol);

/* 
	Realiza la factorización LLt a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada simétrica y no singular.
	-L, LT: Puntero a matrices de la misma dimensión de A que se convertirán en las factorizadas.
	-n: Las dimensiones de la matriz.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
int cholesky(double **A, double ***L, double ***Lt, int n, double tol);

/*---------- END EQUATION SYSTEM SOLVERS ----------*/

/*---------- ITERATIVE EQUATION SYSTEM SOLVERS ----------*/

int Jacobi_Iter(double **A, double *b, double *x, int n, int max_iter, int *iter, double tol);

/*---------- END ITERATIVE EQUATION SYSTEM SOLVERS ----------*/

/*---------- EIGENVALUES AND EIGENVECTORS ----------*/

/* 
	Realiza el método de la potencia a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada no necesariamente simétrica.
	-v_ant: Un vector vacío.
	-nr, nc: Las dimensiones de la matriz.
	-iter: El número de iteraciones máximo que realizará el algoritmo.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
double power_iteration(double **A, double *v_ant, int nr, int nc, int iter, double tol);

/* 
	Realiza el método de la potencia inversa a la matriz A, los parámetros son los siguientes:
	-A: Una matriz cuadrada no necesariamente simétrica.
	-nr, nc: Las dimensiones de la matriz.
	-xk: Un vector de tamaño nc, el cual se convertirá en el eigenvector (Este vector inicialmente puede estar normalizado).
	-mu: El eigenvalor resultante.
	-delta: El valor delta al cual tenderá el eigenvalor, si delta vale cero entonces el método retornará el eigenvalor más pequeño.
	-iter: El número de iteraciones máximo que realizará el algoritmo.
	-k_res: El número de iteraciones que realizó el algoritmo.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
*/
double inverse_power(double **A, int nr, int nc, double **xk, double *mu, double delta, int iter, int *k_res, double tol);

void GAG(double ***A, double ***V, int n, int i, int j, double c, double s);

/* 
	Realiza el método de Jacobi a la matriz A, los parámetros son los siguientes:
	-A: Puntero a una matriz cuadrada y simétrica, (Esta matriz se convierte en la de eigenvalores).
	-V: Puntero a una matriz que resultará ser la matriz de eigenvectores resultantes.
	-nr, nc: Las dimensiones de la matriz.
	-tol: El valor de la tolerancia que se tendrá para la convergencia.
	-xk: Un vector de tamaño nc, el cual se convertirá en el eigenvector (Este vector inicialmente puede estar normalizado).
	-M: El número de iteraciones máximo que realizará el algoritmo.
	-k_res: El número de iteraciones que realizó el algoritmo.
*/
double Jacobi(double ***A, double ***V, int nr, int nc, double tol, int M, int *k_res);

/*---------- END EIGENVALUES AND EIGENVECTORS ----------*/

#endif