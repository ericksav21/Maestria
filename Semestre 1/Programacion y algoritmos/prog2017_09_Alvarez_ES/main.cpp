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
	if(argc < 4) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [No. de nodos] [Origen] [Destino]." << endl;
		return 0;
	}
	int V = atoi(argv[1]);
	char c_orig = argv[2][0];
	char c_dest = argv[3][0];
	int orig = (int)(c_orig - 'A' + 1);
	int dest = (int)(c_dest - 'A' + 1);

	int width = 1024, height = 780;
	int x_ini = width / 2, y_ini = height / 2, r = 310;

	vector<vector<Node> > adj(V + 1);
	fill_graph(adj);
	print_graph(adj);
	vector<CIRCLE> nodes_g = create_circles(adj, x_ini, y_ini, r);
	create_img(adj, nodes_g, width, height, "Grafo.png");

	reset_circles(nodes_g);
	vector<int> dist(adj.size());
	vector<int> path = shortest_path(adj, dist, orig, dest);
	cout << endl;
	if(dist[dest] < 1000) {
		update_circles(path, nodes_g, orig, dest);
		create_img(adj, nodes_g, path, width, height, "Ruta.png");
	}
	else {
		cout << "No se pudo determinar el camino mínimo debido a que no existe conexión entre los nodos origen y destino." << endl;
	}

	return 0;
}