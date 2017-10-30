#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <utility>
#include <cairo/cairo.h>

#include "graph.h"

using namespace std;

typedef struct circle {
	int x, y;
	int r;
	int id;
	double rgb[3];
	char letter[2];
} CIRCLE;

cairo_t* init_cairo(int width, int height, cairo_surface_t **surface);

void cairo_finish(cairo_t *cr, cairo_surface_t *surface, char *files_name);

CIRCLE new_circle(int x, int y, int r, int id, char *letter);

int get_circle(vector<CIRCLE> circles, int id);

vector<CIRCLE> create_circles(vector<vector<Node> > adj, int x_ini, int y_ini, int r);

void create_background(cairo_t *cr, int width, int height);

void write_text(cairo_t *cr, vector<CIRCLE> circles);

void write_weight(cairo_t *cr, int x1, int y1, int x2, int y2, int w, map<pair<int, int>, bool> &mmap);

void draw_arrow(cairo_t *cr, int x2, int y2, int tam, double theta);

void draw_graph(cairo_t *cr, vector<vector<Node> > adj, vector<CIRCLE> circles);

void update_circles(vector<int> path, vector<CIRCLE> &circles, int orig, int dest);

void reset_circles(vector<CIRCLE> &circles);

void create_img(vector<vector<Node> > adj, vector<CIRCLE> circles, int width, int height, char *files_name);

#endif