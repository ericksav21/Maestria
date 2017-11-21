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

#include "point.hpp"

using namespace std;

class Graphics {
private:
	int width, height;
	double scale, x_axis, y_axis, org_x, org_y;
	cairo_t *cr;
	cairo_surface_t *surface;
	string type;

	void init_cairo();
	Point convert_to_cartesian(Point p);
public:
	Graphics(int width, int height, string type);
	~Graphics();
	void save_img();
	void create_background();
	void draw_grid();
	static vector<Point> normalize_points(vector<Point> points, double max_val);
	void set_points(vector<Point> points);
};

#endif