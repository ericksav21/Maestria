#include "funciones.h"

void fill_arr_randomly(double *arr, int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 50;
}

void tiempoTranscurrido(struct timeval t1, struct timeval  t2) {
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;  // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;      // us to ms
    printf("Tiempo transcurrido: %6.4f mseg. \n", elapsedTime);
}

//Esta función calcula en paralelo la suma
//de dos arreglos y la almacena en un tercero
void funcion_1(double *a, double *b, double *c, int n) {
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
        c[i] = a[i] + b[i];
}

//Esta función calcula en paralelo el producto
//de dos arreglos y la almacena en un tercero
void funcion_2(double *a, double *b, double *c, int n) {
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
        c[i] = a[i] * b[i];
}

//Esta función calcula el producto punto de dos
//vectores
double funcion_3(double *a, double *b, int n) {
    double c = 0;
    #pragma omp parallel for reduction(+:c)
    for(int i = 0; i < n; i++) {
        c += a[i] * b[i];
    }

    return c;
}

//Esta función calcula el producto de una matriz por
//un vector
void funcion_4(double **A, double *x, double *b, int n) {
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        double aux = 0;
        for(int j = 0; j < n; j++) {
            aux += (A[i][j] * x[j]);
        }
        b[i] = aux;
    }
}

//Esta función calcula el producto de dos matrices
//cuadradas
void funcion_5(double **P, double **Q, double **R, int n) {
    #pragma omp parallel for schedule (static, 50)
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            double aux = 0;
            for(int k = 0; k < n; k++) {
                aux += (P[i][k] * Q[k][j]);
            }
            R[i][j] = aux;
        }
    }
}
