#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "matriz_vector.h"
#include "image.h"

int** pderivative_x(IMG *img);

int** pderivative_y(IMG *img);

int** pderivative_t(IMG *img1, IMG *img2);

void get_derivatives(IMG *img1, IMG *img2, int **dx, int **dy, int ***dt);

void Horn_Schunck(IMG *img1, IMG *img2, double ***vx, double ***vy, int iter, double lambda);

#endif