#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdio.h>
#include <math.h>

#include "memo.h"

typedef struct img {
	int **mat;
	int width, height;
} IMG;

IMG read_img(char *files_name);

void print_img(IMG img);

void free_img(IMG obj);

IMG resize_img(IMG img);

void draw_line(IMG img, int x0, int y0, int x1, int y1);

#endif