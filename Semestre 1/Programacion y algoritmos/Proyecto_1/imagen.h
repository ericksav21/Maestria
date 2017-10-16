#ifndef IMAGEN_H
#define IMAGEN_H

#include <stdio.h>
#include <math.h>

#include "memo.h"
#include "estructuras.h"
#include "lista_ligada.h"

double distance(PIXEL p1, PIXEL p2);

int pixel_cmp(const void *a, const void *b);

IMG* create_img(int width, int height);

IMG* read_img(char *files_name);

void print_img(IMG *img, char *files_name);

IMG* copy_img(IMG *img);

void free_img(IMG *obj);

IMG* resize_img(IMG *img);

void draw_line(IMG *img, int x0, int y0, int x1, int y1);

void dfs(IMG *ori, PIXEL p_ini, NODEPTR *extreme_points, NODEPTR *path);

//void get_path(IMG *ori, IMG *dest, int **mark, PIXEL p_ini, PIXEL **extreme_points, int *k, PIXEL **path, int *psz);

IMG* clean_skeletonize(IMG *ori, PIXEL *p1, PIXEL *p2, NODEPTR *n_path);

PIXEL get_leftmost_pixel(int *start_line, PIXEL *path, int psz);

PIXEL get_rightmost_pixel(int *start_line, PIXEL *path, int psz);

void get_lines(IMG *img, PIXEL p1, PIXEL p2, NODEPTR n_path, int ind);

double ortho_dist(PIXEL pt, PIXEL l_start, PIXEL l_end);

void RDP(NODEPTR points, int sz, NODEPTR *outs, double eps);

int A_test(IMG *img, int i, int j);

int B_test(IMG *img, int i, int j);

IMG* skeletonize(IMG *ori);

void skeletonize_2(IMG *ori);

#endif