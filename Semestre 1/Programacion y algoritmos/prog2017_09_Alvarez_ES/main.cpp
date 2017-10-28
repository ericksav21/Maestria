#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <cairo/cairo.h>

#include "graphics.hpp"
#include "graph.hpp"

using namespace std;

int main() {
	int width = 1024, height = 780;
	int x_ini = width / 2, y_ini = height / 2;
	int V = 6, r = 310;

	cairo_surface_t *surface;
	cairo_t *cr;
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);

	create_background(cr, width, height);
	cairo_set_source_rgb(cr, 0, 0, 1);

	vector<CIRCLE> nodes_g;
	vector<vector<Node> > adj(V + 1);
	double alpha = 0.0;
	double alpha_ini = (2 * M_PI) / (double) V;
	int x, y;
	for(int i = 0; i < V; i++) {
		int x = x_ini + r * cos(alpha), y = y_ini + r * sin(alpha);

		cairo_arc(cr, x, y, 20, 0, 2 * M_PI);
		cairo_stroke_preserve(cr);
		cairo_fill(cr);
		nodes_g.pb(new_circle(x, y, 20, i + 1));

		alpha += alpha_ini;
	}

	fill_graph(adj);

	for(int i = 3; i < 4; i++) {
		for(int j = 0; j < nodes_g.size(); j++) {
			if(i == j)
				continue;
			//Dibujar las aristas
			CIRCLE c1 = nodes_g[i];
			CIRCLE c2 = nodes_g[j];
			double theta, m1;
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

			cairo_set_source_rgb(cr, 1, 0, 0);
			cairo_move_to(cr, x1, y1);
			cairo_line_to(cr, x2, y2);
			cairo_set_line_width(cr, 3.0);
			cairo_stroke(cr);

			//Dibujar las flechas
			double m2 = -1.0 / m1;
			double beta = atan2(-1.0, m1);
			int xr = x2 - c2.r * cos(theta);
			int yr = y2 - c2.r * sin(theta);
			/*int xx1 = xr - c2.r * cos(beta);
			int yy1 = yr - c2.r * sin(beta);
			int xx2 = xr + c2.r * cos(beta);
			int yy2 = yr + c2.r * sin(beta);*/

			cairo_arc(cr, xr, yr, 3, 0, 2 * M_PI);
			cairo_stroke_preserve(cr);
			cairo_fill(cr);

			if(m2 >= 1.0) {
				int xx1 = x2 - 10;
				int yy1 = m2 * (xx1 - x2) + y2;
				int xx2 = x2 + 10;
				int yy2 = m2 * (xx2 - x2) + y2;

				cairo_move_to(cr, xx1, yy1);
				cairo_line_to(cr, x2, y2);
				cairo_move_to(cr, xx2, yy2);
				cairo_line_to(cr, x2, y2);
				cairo_stroke(cr);
			}
			else {
				int yy1 = y2 - 10;
				int xx1 = m2 * (yy1 - y2) * x2;
				int yy2 = y2 + 10;
				int xx2 = m2 * (yy2 - y2) * x2;

				cairo_move_to(cr, xx1, yy1);
				cairo_line_to(cr, x2, y2);
				cairo_move_to(cr, xx2, yy2);
				cairo_line_to(cr, x2, y2);
				cairo_stroke(cr);
			}
		}
	}


	/*for(int i = 1; i < adj.size(); i++) {
		for(int j = 0; j < adj[i].size(); j++) {

		}
	}*/

	cairo_surface_write_to_png(surface, "Cuadro.png");
	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}