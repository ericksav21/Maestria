#include "memetic.hpp"

Memetic::Memetic(Graph g, int k, int c) {
	this->g = copy_graph(g);
	this->k = k;
	this->c = c;
	vector<int> v = generate_ind();
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

Memetic::~Memetic() {
	delete g;
}

vector<int> Memetic::generate_ind() {
	vector<int> p(g->no_nodes, 0);
	vector<int> S, U, capacity(g->no_nodes, k);
	int root = 0;
	//Colocar el nodo raíz
	S.push_back(root);
	DSU dsu(g->no_nodes);
	for(int i = 1; i < g->no_nodes; i++) {
		U.push_back(i);
		capacity[i] = k - c;
	}

	double alpha = 0.5;
	while(U.size() > 0) {
		int r_s = rand_in_range(0, S.size() - 1);
		int node_j = S[r_s];

		//Ver todos los nodos de U que son seleccionables
		vector<pair<int, int> > u_nodes;
		for(int i = 0; i < U.size(); i++) {
			int node_act = U[i];

			//Ver si el nodo actual es adyacente al nodo j
			bool can_connect = false;
			bool capacity_av = false;
			int edge_sz;
			for(int x = 0; x < g->adj[node_j].size(); x++) {
				if(g->adj[node_j][x].first == node_act) {
					can_connect = true;
					edge_sz = g->adj[node_j][x].second;
					break;
				}
			}

			//Ver si las capacidades del nodo j permiten más conexiones
			if(node_j == root) {
				capacity_av = true;
			}
			else {
				if(dsu.tree_size(node_j) * c + c <= k) {
					capacity_av = true;
				}
			}
			if(can_connect && capacity_av) {
				u_nodes.push_back(make_pair(node_act, edge_sz));
			}
		}
		//Si no hay nodos disponibles, quitamos el nodo j de S
		if(u_nodes.size() == 0) {
			S.erase(S.begin() + r_s);
		}
		else {
			//Hacer un muestreo de tamaño alpha y seleccionar el nodo con aristas
			//Más cortas
			int spl_sz = max(1, (int)(u_nodes.size() * alpha));
			vector<pair<int, int> > sample;
			if(spl_sz == 1) {
				sample.push_back(make_pair(u_nodes[0].first, u_nodes[0].second));
			}
			else {
				for(int x = 0; x < spl_sz; x++) {
					int r_aux = rand_in_range(0, u_nodes.size() - 1);
					sample.push_back(make_pair(u_nodes[r_aux].first, u_nodes[r_aux].second));
					u_nodes.erase(u_nodes.begin() + r_aux);
				}
			}
			//Seleccionar el nodo con la arista más corta
			int shorter_edge = 1000000;
			int idx_aux;
			for(int x = 0; x < sample.size(); x++) {
				if(sample[x].second < shorter_edge) {
					shorter_edge = sample[x].second;
					idx_aux = x;
				}
			}
			int node_i = sample[idx_aux].first;
			p[node_i] = node_j;
			//Quitar el individuo de U y moverlo a S
			int idx = -1;
			for(int x = 0; x < U.size(); x++) {
				if(U[x] == node_i) {
					idx = x;
					break;
				}
			}
			U.erase(U.begin() + idx);
			S.push_back(node_i);
			
			//Actualizar las capacidades
			if(node_j != root) {
				dsu.make_union(node_j, node_i);
			}
		}

		//Si S está vacío ya no se puede generar el árbol
		if(S.size() == 0) {
			cout << "No se pudo generar un individuo factible del grafo." << endl;
			break;
		}
	}

	return p;
}