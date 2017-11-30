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
#include <sstream>
#include <cairo/cairo.h>
#include <cairo/cairo-ps.h>

#include "util.hpp"
#include "point.hpp"
#include "image.hpp"

using namespace std;

class Graphics {
private:
	int width, height;
	string files_name;
	cairo_surface_t *surface;
	cairo_t *cr;

	void init_cairo();
public:
	Graphics(int width, int height, string files_name);
	~Graphics();
	void copy_img(Image img);
	void copy_points(vector<Point> ppoints);
	void save(bool use_path);
};

#endif