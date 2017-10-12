#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "estructuras.h"
#include "lista_ligada.h"

IMG create_img(int width, int height);

IMG read_img(char *files_name);

void print_img(IMG img, char *files_name);

IMG copy_img(IMG img);

void free_img(IMG obj);

IMG resize_img(IMG img);

void draw_line(IMG img, int x0, int y0, int x1, int y1);

PIXEL find_leftmost_pxl(IMG img, int start_line);

PIXEL find_rightmost_pxl(IMG img, int start_line);

void get_lines(IMG img, IMG org, int ind);

int A_test(IMG img, int i, int j);

int B_test(IMG img, int i, int j);

IMG skeletonize(IMG ori);

#endif