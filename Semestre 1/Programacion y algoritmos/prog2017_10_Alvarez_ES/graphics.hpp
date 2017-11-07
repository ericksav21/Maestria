#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <utility>
#include <cairo/cairo.h>
#include <cairo/cairo-ps.h>

using namespace std;

typedef struct circle {
	int x, y;
	int r;
	int id;
	double rgb[3];
	char letter[2];
} CIRCLE;

void create_background(cairo_t *cr, int width, int height);

cairo_t* init_cairo(int width, int height, cairo_surface_t **surface, char *files_name, bool is_png);

void write_text(cairo_t *cr, int x, int y, int id);

void print_arrows(cairo_t *cr, vector<vector<pair<int, int> > > neurons, double r);

void draw_graph(cairo_t *cr, vector<int> layers, int width, int height);

void cairo_finish(cairo_t *cr, cairo_surface_t *surface, char *files_name, bool is_png);

void create_img_png(vector<int> layers, int width, int height, char *files_name);

void create_img_ps(vector<int> layers, int width, int height, char *files_name);

#endif