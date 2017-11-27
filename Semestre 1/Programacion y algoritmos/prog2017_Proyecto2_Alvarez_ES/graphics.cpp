#include "graphics.hpp"

Graphics::Graphics(int width, int height, string files_name) {
	this->width = width;
	this->height = height;
	this->files_name = files_name;

	init_cairo();
}

Graphics::~Graphics() {
	cairo_destroy(cr);
	cairo_surface_finish(surface);
	cairo_surface_destroy(surface);
}

void Graphics::init_cairo() {
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);

	//Crear fondo
	cairo_pattern_t *pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
	cairo_pattern_add_color_stop_rgb(pat, 0.0, 0, 0, 0);
	cairo_pattern_add_color_stop_rgb(pat, 1.0, 0, 0, 0);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_fill(cr);
}

void Graphics::copy_img(Image img) {
	if(img.get_width() != width || img.get_height() != height) {
		cout << "Las dimensiones de las imágenes deben coincidir." << endl;
		return;
	}
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			if(img.get_val(j, i) == 0) {
				cairo_set_source_rgb(cr, 0, 0, 0);
			}
			else {
				cairo_set_source_rgb(cr, 1, 1, 1);
			}
			cairo_rectangle (cr, i, j, 1, 1);
			cairo_fill(cr);
		}
	}
}

void Graphics::save(bool use_path) {
	string files_path;
	if(use_path) {
		stringstream ss;
		ss << Util::get_path() << "/" << files_name;
		files_path = ss.str();
	}
	else {
		files_path = files_name;
	}
	cairo_surface_write_to_png(surface, files_path.c_str());
}