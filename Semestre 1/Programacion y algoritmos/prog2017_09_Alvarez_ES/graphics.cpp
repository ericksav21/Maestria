#include "graphics.hpp"

CIRCLE new_circle(int x, int y, int r, int id) {
	CIRCLE res;
	res.x = x;
	res.y = y;
	res.r = r;
	res.id = id;
	res.rgb[0] = 0;
	res.rgb[1] = 0;
	res.rgb[2] = 1;

	return res;
}

void create_background(cairo_t *cr, int width, int height) {
	cairo_pattern_t *pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
	cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
	cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_fill(cr);
}