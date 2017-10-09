#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

typedef struct img {
	int **mat;
	int width, height;
} IMG;

IMG create_img(int width, int height);

IMG read_img(char *files_name);

void print_img(IMG img);

IMG copy_img(IMG img);

void free_img(IMG obj);

IMG resize_img(IMG img);

void draw_line(IMG img, int x0, int y0, int x1, int y1);

int A_test(IMG img, int i, int j);

int B_test(IMG img, int i, int j);

IMG skeletonize(IMG ori);

#endif