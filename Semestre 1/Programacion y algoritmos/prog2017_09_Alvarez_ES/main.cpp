#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cairo/cairo.h>

#include "graphics.h"
#include "graph.h"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [No. de nodos] [Origen]." << endl;
		return 0;
	}
	int V = atoi(argv[1]);
	int orig = atoi(argv[2]);

	int width = 1024, height = 780;
	int x_ini = width / 2, y_ini = height / 2, r = 310;

	vector<vector<Node> > adj(V + 1);
	fill_graph(adj);
	print_graph(adj);
	vector<CIRCLE> nodes_g = create_circles(adj, x_ini, y_ini, r);
	create_img(adj, nodes_g, width, height, "Grafo.png");

	for(int i = 1; i < adj.size(); i++) {
		if(i == orig) continue;
		reset_circles(nodes_g);
		vector<int> dist(adj.size());
		vector<int> path = shortest_path(adj, dist, orig, i);
		if(dist[i] >= 1000) continue;
		update_circles(path, nodes_g, orig, i);
		char files_name[30];
		sprintf(files_name, "Grafo_%d.png", i);
		create_img(adj, nodes_g, width, height, files_name);
	}

	return 0;
}