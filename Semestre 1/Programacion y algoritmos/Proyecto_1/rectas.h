#ifndef RECTAS_H
#define RECTAS_H

#include <stdio.h>
#include <math.h>

#include "estructuras.h"
#include "imagen.h"
#include "lista_ligada.h"

/*
	Encuentra la distancia euclideana entre dos puntos.
*/
double distance(PIXEL p1, PIXEL p2);

/*
	Encuentra el trayecto generado por la esqueletización, así como los puntos
	extremos.
*/
void dfs(IMG *ori, PIXEL p_ini, NODEPTR *extreme_points, NODEPTR *path);


/*
	Limpia la esqueletización de posibles bifurcaciones.
*/
void clean_skeletonize(IMG *ori, PIXEL *p1, PIXEL *p2, NODEPTR *n_path);

/*
	Obtiene el pixel que se encuentre más a la izquierda, partiendo de
	una fila dada.
*/
PIXEL get_leftmost_pixel(int *start_line, NODEPTR path, int psz);

/*
	Obtiene el pixel que se encuentre más a la derecha, partiendo de
	una fila dada.
*/
PIXEL get_rightmost_pixel(int *start_line, NODEPTR path, int psz);

/*
	Encuentra las rectas de interés a partir de la esqueletización.
*/
NODEPTR get_lines(IMG *img, PIXEL p1, PIXEL p2, NODEPTR n_path, int ind);

/*
	Encuentra la distancia ortogonal de un punto dado a una recta.
*/
double ortho_dist(PIXEL pt, PIXEL l_start, PIXEL l_end);

/*
	Algoritmo de Ramer-Douglas-Peucker se encarga de encontrar un conjunto
	de rectas desde un conjunto de puntos inicial.
*/
void RDP(NODEPTR points, int sz, NODEPTR *outs, double eps);

/*
	Prueba A para el algoritmo de Zhang-Suen.
*/
int A_test(IMG *img, int i, int j);

/*
	Prueba B para el algoritmo de Zhang-Suen.
*/
int B_test(IMG *img, int i, int j);

/*
	Algoritmo de Zhang-Suen genera una esqueletización desde una imagen dada.
*/
IMG* skeletonize(IMG *ori);

/*
	Obtiene los ángulos de un conjunto de rectas dado.
*/
double* get_angles(NODEPTR lines);

#endif