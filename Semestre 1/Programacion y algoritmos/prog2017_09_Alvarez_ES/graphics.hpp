#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cairo/cairo.h>

using namespace std;

typedef struct circle {
	int x, y;
	int r;
	int id;
	int rgb[3];
} CIRCLE;

CIRCLE new_circle(int x, int y, int r, int id);

void create_background(cairo_t *cr, int width, int height);

#endif