#include "graphics.hpp"

void create_background(cairo_t *cr, int width, int height) {
	cairo_pattern_t *pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
	cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.286, 0.6078, 0.9176);
	cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.1254, 0.486, 0.8980);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_fill(cr);
}

cairo_t* init_cairo(int width, int height, cairo_surface_t **surface, char *files_name, bool is_png) {
	cairo_t *cr;
	if(is_png) {
		*surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	}
	else {
		*surface = cairo_ps_surface_create(files_name, width, height);
	}
	cr = cairo_create(*surface);

	if(!is_png) {
		cairo_ps_surface_dsc_begin_page_setup (*surface);
    		cairo_ps_surface_dsc_comment (*surface, "%%PageOrientation: Portrait");
	}
	create_background(cr, width, height);

	return cr;
}

void write_text(cairo_t *cr, int x, int y, int id, bool is_last) {
	char str[5];
	if(id == 0 && !is_last)
		sprintf(str, "B");
	else
		sprintf(str, "%d", is_last ? id + 1 : id);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_font_size(cr, 12);
	cairo_select_font_face(cr, "Arial",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);

	int dl = 5;
	cairo_move_to(cr, x - dl, y + dl);
	cairo_show_text(cr, str);
	cairo_stroke(cr);
}

void print_arrows(cairo_t *cr, int x, int y, double r, int tam, double theta) {
	int x2 = x - r * cos(theta), y2 = y - r * sin(theta);
	int xr = x2 - tam * cos(theta);
	int yr = y2 - tam * sin(theta);
	//30 grados
	double ecos = 0.866, esin = 0.500;
	double dx = xr - x2, dy = yr - y2;
	double end1x = (x2 + (dx * ecos + dy * -esin));
	double end1y = (y2 + (dx * esin + dy * ecos));

	double end2x = (x2 + (dx * ecos + dy * esin));
	double end2y = (y2 + (dx * -esin + dy * ecos));

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_move_to(cr, end1x, end1y);
	cairo_line_to(cr, x2, y2);
	cairo_move_to(cr, end2x, end2y);
	cairo_line_to(cr, x2, y2);
	cairo_stroke(cr);
}

void print_rects(cairo_t *cr, vector<vector<pair<int, int> > > neurons, double r) {
	for(int i = 0; i < neurons.size() - 1; i++) {
		for(int j = 0; j < neurons[i].size(); j++) {
			for(int k = 0; k < neurons[i + 1].size(); k++) {
				pair<int, int> p1 = neurons[i][j], p2 = neurons[i + 1][k];
				double theta = atan2((double)(p2.second - p1.second), (double)(p2.first - p1.first));
				int x1 = p1.first + r * cos(theta);
				int y1 = p1.second + r * sin(theta);
				int x2 = p2.first - r * cos(theta);
				int y2 = p2.second - r * sin(theta);
				cairo_move_to(cr, x1, y1);
				cairo_line_to(cr, x2, y2);
				cairo_stroke(cr);
				print_arrows(cr, p2.first, p2.second, r, 15, theta);
			}
		}
	}
}

void draw_graph(cairo_t *cr, vector<int> layers, int width, int height) {
	double r = 30.0;
	double dw = width / (double)layers.size();
	double sz = layers.size() * dw;
	vector<vector<pair<int, int> > > neurons(layers.size());
	for(int i = 0; i < layers.size(); i++) {
		int xinit = i * dw, xfinish = xinit + (int)dw;
		int no_neurons = layers[i];
		if(i < layers.size() - 1) no_neurons++;
		double dh = height / (double)no_neurons;

		for(int j = 0; j < no_neurons; j++) {
			int yinit = j * dh, yfinish = yinit + (int)dh;
			int xm = abs(xfinish + xinit) / 2, ym = abs(yfinish + yinit) / 2;
			neurons[i].push_back(make_pair(xm, ym));
			cairo_set_source_rgb(cr, 0, 0, 0);
			cairo_arc(cr, xm, ym, r, 0, 2 * M_PI);
			cairo_fill(cr);
			cairo_stroke(cr);

			write_text(cr, xm, ym, j, i == layers.size() - 1);
		}
	}
	print_rects(cr, neurons, r);
}

void cairo_finish(cairo_t *cr, cairo_surface_t *surface, char *files_name, bool is_png) {
	if(is_png) {
		cairo_surface_write_to_png(surface, files_name);
	}
	else {
		cairo_surface_show_page(surface);
	}
	cairo_destroy(cr);
	cairo_surface_finish(surface);
	cairo_surface_destroy(surface);
}

void create_img_png(vector<int> layers, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, "", true);
	draw_graph(cr, layers, width, height);
	cairo_finish(cr, surface, files_name, true);
}

void create_img_ps(vector<int> layers, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, files_name, false);
	draw_graph(cr, layers, width, height);
	cairo_finish(cr, surface, files_name, false);
}
