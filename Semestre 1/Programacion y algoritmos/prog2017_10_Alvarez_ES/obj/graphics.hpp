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
#include <cairo/cairo-ps.h>

using namespace std;

typedef struct circle {
	int x, y;
	int r;
	int id;
	double rgb[3];
	char letter[2];
} CIRCLE;

cairo_t* init_cairo(int width, int height, cairo_surface_t **surface, char *files_name, bool is_png);

void cairo_finish(cairo_t *cr, cairo_surface_t *surface, char *files_name, bool is_png);

void create_img_png(vector<vector<Node> > adj, vector<CIRCLE> circles, int width, int height, char *files_name);

void create_img_png(vector<vector<Node> > adj, vector<CIRCLE> circles, vector<int> path, int width, int height, char *files_name);

void create_img_ps(vector<vector<Node> > adj, vector<CIRCLE> circles, int width, int height, char *files_name);

void create_img_ps(vector<vector<Node> > adj, vector<CIRCLE> circles, vector<int> path, int width, int height, char *files_name);

#endif