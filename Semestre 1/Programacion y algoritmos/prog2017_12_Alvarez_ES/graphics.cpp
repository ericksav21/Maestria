#include "graphics.hpp"

Graphics::Graphics(int width, int height, string type) {
	this->width = width;
	this->height = height;
	this->scale = 2.0;
	this->type = type;
	
	init_cairo();
}

Graphics::~Graphics() {
	if(cr) {
		cairo_destroy(cr);
	}
	if(surface) {
		cairo_surface_finish(surface);
		cairo_surface_destroy(surface);
	}
}

void Graphics::save_img() {
	if(type == "png") {
		cairo_surface_write_to_png(surface, "out.png");
	}
	else {
		cairo_surface_show_page(surface);
	}
}

void Graphics::init_cairo() {
	if(type == "png") {
		surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	}
	else if(type == "ps") {
		surface = cairo_ps_surface_create("out.ps", width, height);
	}
	else {
		cout << "Error: Formato de imagen no encontrado." << endl;
		return;
	}

	cr = cairo_create(surface);
	if(type == "ps") {
		cairo_ps_surface_dsc_begin_page_setup(surface);
    	cairo_ps_surface_dsc_comment(surface, "%%PageOrientation: Portrait");
	}
	x_axis = width - (width / 8.0);
	y_axis = height / 8.0;
	org_x = width / 8.0;
	org_y = height - (height / 8.0);
}

void Graphics::create_background() {
	cairo_pattern_t *pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
	cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.286, 0.6078, 0.9176);
	cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.1254, 0.486, 0.8980);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_fill(cr);
}

void Graphics::draw_grid() {
	cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
	cairo_set_line_width(cr, 3.0);
	cairo_move_to(cr, org_x, org_y); cairo_line_to(cr, x_axis, org_y);
	cairo_stroke(cr);
	cairo_move_to(cr, org_x, org_y); cairo_line_to(cr, org_x, y_axis);
	cairo_stroke(cr);

	double x_metric = (x_axis - org_x) / 10.0;
	double y_metric = (org_y - y_axis) / 10.0;
	cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
	cairo_set_line_width(cr, 0.5);
	for(int i = 1; i <= 10; i++) {
		cairo_move_to(cr, (org_x + (x_metric * i)), org_y);
		cairo_line_to(cr, (org_x + (x_metric * i)), y_axis);
		cairo_stroke(cr);

		cairo_move_to(cr, org_x, (y_axis + (y_metric * (i - 1))));
		cairo_line_to(cr, x_axis, (y_axis + (y_metric * (i - 1))));
		cairo_stroke(cr);
	}
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
										CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 10.0);
	for(int i = 0; i <= 10; i++) {
		cairo_move_to(cr, (org_x + (x_metric * i)), (org_y + 10.0));
		cairo_save(cr);
		cairo_rotate(cr, 45.0);
		char tnum[9];
		sprintf(tnum, "%.2f", x_metric * scale * i);
		cairo_show_text(cr, tnum);
		cairo_restore(cr);
	}
	for(int i = 0; i <= 10; i++) {
		cairo_move_to(cr, org_x - 50.0, (org_y - (y_metric * i)));
		char tnum[9];
		sprintf(tnum, "%.2f", y_metric * scale * i);
		cairo_show_text(cr, tnum);
	}
	cairo_set_font_size(cr, y_axis / 3.0);
	cairo_move_to(cr, (width / 2.0) - 60.0, y_axis / 2.0);
	cairo_show_text(cr, "K-Means");
}

Point Graphics::convert_to_cartesian(Point p) {
	double x_res = org_x + p.get_x() / scale;
	double y_res = org_y - p.get_y() / scale;

	return Point(x_res, y_res);
}

vector<Point> Graphics::normalize_points(vector<Point> points, double max_val) {
	for(int i = 0; i < points.size(); i++) {
		points[i].set_x(max_val / points[i].get_x());
		points[i].set_y(max_val / points[i].get_y());
	}

	return points;
}

void Graphics::set_points(vector<Point> points) {
	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	for(int i = 0; i < points.size(); i++) {
		Point p_act = convert_to_cartesian(points[i]);
		cout << p_act.get_x() << " " << p_act.get_y() << endl;
		cairo_arc(cr, p_act.get_x(), p_act.get_y(), 3.5, 0.0, 2.0 * M_PI);
		cairo_fill(cr);
		cairo_stroke(cr);
	}
}