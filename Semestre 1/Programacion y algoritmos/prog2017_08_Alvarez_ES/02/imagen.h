#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>
#include <cstddef>
#include <fstream>
#include <queue>

#include "memo.h"

using namespace std;

typedef struct point {
	int i, j;
} POINT;

int** read_img(string files_name, int *fwidth, int *fheight);

void print_img(int **img, int width, int height, string files_name);

vector<POINT> get_neighbors(int **img, int width, int height, int i, int j);

int bfs(int **img, int width, int height, int ii, int jj, int **visited);

void update_img(int **src, int **org, int **dest, int width, int height, bool update_max);

#endif