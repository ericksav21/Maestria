#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "memo.h"
#include "funciones.h"

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Por favor especifique 2 enteros: n y t.\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int t = atoi(argv[2]);
    unsigned int seed = time(NULL);

    //Verificar si se pasó un número de semilla en los argumentos
    if(argc == 4) {
        seed = atoi(argv[3]);
    }

    srand(seed);

    if(t <= 0)
        t = 1;
    if(t > omp_get_max_threads())
        t = omp_get_max_threads();

    struct timeval t1, t2;
    double *a = (double *)create_arr_1d(n, sizeof(double));
    double *b = (double *)create_arr_1d(n, sizeof(double));
    double *c = (double *)create_arr_1d(n, sizeof(double));
    double **P = (double **)create_arr_2d(n, n, sizeof(double));
    double **Q = (double **)create_arr_2d(n, n, sizeof(double));
    double **R = (double **)create_arr_2d(n, n, sizeof(double));

    fill_arr_randomly(a, n);
    fill_arr_randomly(c, n);
    for(int i = 0; i < n; i++) {
        fill_arr_randomly(P[i], n);
        fill_arr_randomly(Q[i], n);
        c[i] = 0;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            R[i][j] = 0;

    printf("Número de threads: %d.\nTamaño de n: %d\n", t, n);
    omp_set_num_threads(t);

    gettimeofday(&t1, NULL);
    printf("\n------- Suma de vectores ------------\n");

    funcion_1(a, b, c, n);

    gettimeofday(&t2, NULL);
    tiempoTranscurrido(t1, t2);

    gettimeofday(&t1, NULL);
    printf("\n------- Producto de vectores ------------\n");

    funcion_2(a, b, c, n);

    gettimeofday(&t2, NULL);
    tiempoTranscurrido(t1, t2);

    gettimeofday(&t1, NULL);
    printf("\n------- Producto punto ------------\n");

    funcion_3(a, b, n);

    gettimeofday(&t2, NULL);
    tiempoTranscurrido(t1, t2);

    gettimeofday(&t1, NULL);
    printf("\n------- Matriz por vector ------------\n");

    funcion_4(P, a, c, n);

    gettimeofday(&t2, NULL);
    tiempoTranscurrido(t1, t2);

    gettimeofday(&t1, NULL);
    printf("\n------- Producto de matrices ------------\n");

    funcion_5(P, Q, R, n);

    gettimeofday(&t2, NULL);
    tiempoTranscurrido(t1, t2);

    delete_arr_1d((void *)a);
    delete_arr_1d((void *)b);
    delete_arr_1d((void *)c);
    delete_arr_2d((void **)P, n);
    delete_arr_2d((void **)Q, n);
    delete_arr_2d((void **)R, n);

    return 0;
}
