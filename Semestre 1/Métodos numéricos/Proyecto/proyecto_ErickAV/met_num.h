#ifndef MET_NUM_H
#define MET_NUM_H

#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "memo.h"
#include "matriz_vector.h"
#include "image.h"

double** pderivative_x(IMG *img);

double** pderivative_y(IMG *img);

double** pderivative_t(IMG *img1, IMG *img2);

void get_derivatives(IMG *img1, IMG *img2, double ***dx, double ***dy, double ***dt);

int check_convergence(double **vx, double **vy, double **vx1, double **vy1, int width, int height, double tol);

void Horn_Schunck(IMG *img1, IMG *img2, double ***vx, double ***vy, int iter, double lambda);

void quiver(IMG *out, double **vx, double **vy, int width, int height);

#endif