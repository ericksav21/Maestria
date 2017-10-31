#include "graphics.h"

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

CIRCLE new_circle(int x, int y, int r, int id, char *letter) {
	CIRCLE res;
	res.x = x;
	res.y = y;
	res.r = r;
	res.id = id;
	res.rgb[0] = 0.3686;
	res.rgb[1] = 0.1450;
	res.rgb[2] = 0.3254;
	strcpy(res.letter, letter);

	return res;
}

int get_circle(vector<CIRCLE> circles, int id) {
	for(int i = 0; i < circles.size(); i++) {
		if(circles[i].id == id)
			return i;
	}
	return -1;
}

vector<CIRCLE> create_circles(vector<vector<Node> > adj, int x_ini, int y_ini, int r) {
	vector<CIRCLE> nodes_g;
	double alpha = 0.0;
	double alpha_ini = (2 * M_PI) / ((double) adj.size() - 1);
	int x, y;
	for(int i = 1; i < adj.size(); i++) {
		x = x_ini + r * cos(alpha);
		y = y_ini + r * sin(alpha);

		char str[] = {'A' + (i - 1), '\0'};
		nodes_g.pb(new_circle(x, y, 40, i, str));

		alpha += alpha_ini;
	}

	return nodes_g;
}

void create_background(cairo_t *cr, int width, int height) {
	cairo_pattern_t *pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
	cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.286, 0.6078, 0.9176);
	cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.1254, 0.486, 0.8980);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source(cr, pat);
	cairo_fill(cr);
}

void write_text(cairo_t *cr, vector<CIRCLE> circles) {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_font_size(cr, 12);
	cairo_select_font_face(cr, "Arial",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
	for(int i = 0; i < circles.size(); i++) {
		CIRCLE c_i = circles[i];
		int dl = 5;
		cairo_move_to(cr, c_i.x - dl, c_i.y + dl);
		cairo_show_text(cr, c_i.letter);
	}
}

void write_weight(cairo_t *cr, int x1, int y1, int x2, int y2, int w) {
	int tam = 25;
	char str[5];
	sprintf(str, "%d", w);
	int ax = 0, ay = 0;
	int dx = x2 - x1, dy = y2 - y1;
	double theta = atan2(dy, dx);
	int xm = x1 + tam * cos(theta);
	int ym = y1 + tam * sin(theta);
	double m = (double)(abs(dy)) / (double)(abs(dx));
	string aux(str);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, xm + ax, ym + ay);
	cairo_show_text(cr, str);
}

void draw_edge(cairo_t *cr, vector<vector<Node> > adj, CIRCLE c1, CIRCLE c2, int i, int j, double &theta, double *rgb) {
	double m1;
	if(c2.x == c1.x) {
		theta = atan2(c2.y - c1.y, c2.x - c1.x + 2);
		m1 = (c2.y - c1.y) / (c2.x - c1.x + 2);
	}
	else {
		theta = atan2(c2.y - c1.y, c2.x - c1.x);
		m1 = (c2.y - c1.y) / (c2.x - c1.x);
	}

	int x1 = c1.x + c1.r * cos(theta);
	int y1 = c1.y + c1.r * sin(theta);
	int x2 = c2.x - c2.r * cos(theta);
	int y2 = c2.y - c2.r * sin(theta);
	int w = adj[i][j].snd;

	cairo_set_source_rgb(cr, rgb[0], rgb[1], rgb[2]);
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y2);
	cairo_set_line_width(cr, 1.8);
	cairo_stroke(cr);

	write_weight(cr, x1, y1, x2, y2, w);
}

void draw_arrow(cairo_t *cr, CIRCLE c, int tam, double theta, double *rgb) {
	int x2 = c.x - c.r * cos(theta), y2 = c.y - c.r * sin(theta);
	int xr = x2 - tam * cos(theta);
	int yr = y2 - tam * sin(theta);
	//30 grados
	double ecos = 0.866, esin = 0.500;
	double dx = xr - x2, dy = yr - y2;
	double end1x = (x2 + (dx * ecos + dy * -esin));
	double end1y = (y2 + (dx * esin + dy * ecos));

	double end2x = (x2 + (dx * ecos + dy * esin));
	double end2y = (y2 + (dx * -esin + dy * ecos));

	cairo_set_source_rgb(cr, rgb[0], rgb[1], rgb[2]);
	cairo_move_to(cr, end1x, end1y);
	cairo_line_to(cr, x2, y2);
	cairo_move_to(cr, end2x, end2y);
	cairo_line_to(cr, x2, y2);
	cairo_stroke(cr);
}

void draw_graph(cairo_t *cr, vector<vector<Node> > adj, vector<CIRCLE> circles) {
	for(int i = 0; i < circles.size(); i++) {
		CIRCLE c_i = circles[i];
		cairo_set_source_rgb(cr, c_i.rgb[0], c_i.rgb[1], c_i.rgb[2]);
		int x = c_i.x;
		int y = c_i.y;

		cairo_arc(cr, x, y, c_i.r, 0, 2 * M_PI);
		cairo_stroke_preserve(cr);
		cairo_fill(cr);
	}
	//Dibujar las letras
	write_text(cr, circles);
	//Dibujar las aristas
	for(int i = 1; i < adj.size(); i++) {
		for(int j = 0; j < adj[i].size(); j++) {
			double theta = 0.0;

			//Dibujar las aristas
			CIRCLE c1 = circles[i - 1];
			CIRCLE c2 = circles[adj[i][j].fst - 1];
			double rgb[3] = {0.7607, 0.9803, 1};
			draw_edge(cr, adj, c1, c2, i, j, theta, rgb);

			//Dibujar las flechas
			draw_arrow(cr, c2, 15, theta, rgb);
		}
	}
}

void update_circles(vector<int> path, vector<CIRCLE> &circles, int orig, int dest) {
	circles[orig - 1].rgb[0] = 0.1627;
	circles[orig - 1].rgb[1] = 0.8509;
	circles[orig - 1].rgb[2] = 0.4235;

	circles[dest - 1].rgb[0] = 1;
	circles[dest - 1].rgb[1] = 0.1725;
	circles[dest - 1].rgb[2] = 0.3450;

	for(int i = 1; i < path.size() - 1; i++) {
		circles[path[i] - 1].rgb[0] = 0.866;
		circles[path[i] - 1].rgb[1] = 0.5607;
		circles[path[i] - 1].rgb[2] = 0.1647;
	}
}

void update_edges(cairo_t *cr, vector<vector<Node> > adj, vector<int> path, vector<CIRCLE> &circles) {
	double rgb[3] = {0.8627, 0.6431, 0.1803};
	for(int i = 0; i < path.size() - 1; i++) {
		double theta = 0.0;
		int u = path[i], v = path[i + 1], vv;
		for(int i = 0; i < adj[u].size(); i++) {
			if(adj[u][i].fst == v) {
				vv = i;
				break;
			}
		}
		CIRCLE c_o = circles[u - 1], c_d = circles[v - 1];
		draw_edge(cr, adj, c_o, c_d, u, vv, theta, rgb);

		//Dibujar las flechas
		draw_arrow(cr, c_d, 15, theta, rgb);
	}
}

void reset_circles(vector<CIRCLE> &circles) {
	for(int i = 0; i < circles.size(); i++) {
		circles[i].rgb[0] = 0.3686;
		circles[i].rgb[1] = 0.1450;
		circles[i].rgb[2] = 0.3254;
	}
}

void create_img_png(vector<vector<Node> > adj, vector<CIRCLE> circles, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, "", true);
	draw_graph(cr, adj, circles);
	cairo_finish(cr, surface, files_name, true);
}

void create_img_png(vector<vector<Node> > adj, vector<CIRCLE> circles, vector<int> path, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, "", true);
	draw_graph(cr, adj, circles);
	update_edges(cr, adj, path, circles);
	cairo_finish(cr, surface, files_name, true);
}

void create_img_ps(vector<vector<Node> > adj, vector<CIRCLE> circles, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, files_name, false);
	draw_graph(cr, adj, circles);
	cairo_finish(cr, surface, files_name, false);
}

void create_img_ps(vector<vector<Node> > adj, vector<CIRCLE> circles, vector<int> path, int width, int height, char *files_name) {
	cairo_surface_t *surface;
	cairo_t *cr = init_cairo(width, height, &surface, files_name, false);
	draw_graph(cr, adj, circles);
	update_edges(cr, adj, path, circles);
	cairo_finish(cr, surface, files_name, false);
}