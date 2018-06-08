#include "memetic.hpp"

Memetic::Memetic(Graph g, int k, int c, int root) {
	this->g = copy_graph(g);
	this->k = k;
	this->c = c;
	this->root = root;
	/*vector<int> v = generate_ind();
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
	if(v[0] != -1) {
		int fit = fitness(v);
		cout << "Fitness: " << fit << endl;
	}*/
	vector<int> p = {9, 8, 3, 9, 3, 4, 5, 0, 9, 9};
	vector<int> q = {9, 2, 3, 9, 6, 6, 7, 0, 9, 9};
	//vector<int> r = crossover(p, q);
	vector<int> r = mutation(p);
	for(int i = 0; i < r.size(); i++) {
		cout << r[i] << " ";
	}
	cout << endl;
}

Memetic::~Memetic() {
	delete g;
}

vector<int> Memetic::generate_ind() {
	vector<int> p(g->no_nodes, root);
	vector<int> S, U, capacity(g->no_nodes, k);
	//Colocar el nodo raíz
	S.push_back(root);
	DSU dsu(g->no_nodes);
	for(int i = 0; i < g->no_nodes; i++) {
		if(i != root) {
			U.push_back(i);
			capacity[i] = k - c;
		}
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
			//Si el nodo padre es la raíz siempre podremos hacer la conexión
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
			int shorter_edge = INT_MAX;
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
			//Si el nodo padre es la raíz no necesitamos actualizar las capacidades
			if(node_j != root) {
				dsu.make_union(node_j, node_i);
			}
		}

		//Si S está vacío ya no se puede generar el árbol
		if(S.size() == 0) {
			for(int i = 0; i < p.size(); i++) {
				p[i] = -1;
			}
			cout << "No se pudo generar un individuo factible del grafo." << endl;
			break;
		}
	}

	return p;
}

int Memetic::fitness(vector<int> &ind) {
	int cnt = 0;
	queue<int> q;
	q.push(root);

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for(int i = 0; i < ind.size(); i++) {
			//Si el padre del nodo i es el nodo u
			if(i != u && ind[i] == u) {
				//Obtener el costo de la arista entre u e i
				for(int x = 0; x < g->adj[u].size(); x++) {
					if(g->adj[u][x].first == i) {
						cnt += g->adj[u][x].second;
						break;
					}
				}
				q.push(i);
			}
		}
	}

	return cnt;
}

vector<int> Memetic::crossover(vector<int> &p, vector<int> &q) {
	int n = p.size();
	vector<int> r(n, -1);
	vector<int> U;
	DSU dsu(g->no_nodes);
	queue<int> no_connected;

	for(int i = 0; i < n; i++) {
		if(p[i] == q[i]) {
			r[i] = p[i];
		}
		else {
			U.push_back(i);
		}
	}

	while(U.size() > 0) {
		int r_s = rand_in_range(0, U.size() - 1);
		int node_i = U[r_s];
		int r_aux = rand_in_range(0, 1);
		int node_j;
		bool slc = false;
		if(r_aux == 0) {
			node_j = p[node_i];
			slc = true;
		}
		else {
			node_j = q[node_i];
		}
		bool can_connect = false;
		//Si los nodos no se encuentran conectados
		if(!dsu.same_cmp(node_i, node_j)) {
			//Ver que no hayan problemas de capacidades
			if(node_j == root) {
				r[node_i] = node_j;
				can_connect = true;
			}
			else if(dsu.tree_size(node_j) * c + c <= k) {
				r[node_i] = node_j;
				dsu.make_union(node_i, node_j);
				can_connect = true;
			}
		}
		if(!can_connect) {
			//Tomar el otro nodo padre e intentar hacer lo mismo
			node_j = (slc ? q[node_i] : p[node_i]);

			//Si los nodos no se encuentran conectados
			if(!dsu.same_cmp(node_i, node_j)) {
				//Ver que no hayan problemas de capacidades
				if(node_j == root) {
					r[node_i] = node_j;
					can_connect = true;
				}
				else if(dsu.tree_size(node_j) * c + c <= k) {
					r[node_i] = node_j;
					dsu.make_union(node_i, node_j);
					can_connect = true;
				}
			}
			if(!can_connect) {
				no_connected.push(node_i);
			}
		}
		U.erase(U.begin() + r_s);
	}

	//Procesar los nodos que no se pudieron conectar
	double alpha = 0.8;
	while(!no_connected.empty()) {
		int node_i = no_connected.front();
		no_connected.pop();
		vector<pair<int, int> > vp;
		for(int j = 0; j < g->no_nodes; j++) {
			for(int x = 0; x < g->adj[node_i].size(); x++) {
				if(g->adj[node_i][x].first == j && !dsu.same_cmp(node_i, j)) {
					if(j == root || dsu.tree_size(j) * c + c <= k) {
						vp.push_back(make_pair(g->adj[node_i][x].second, j));
						break;
					}
				}
			}
		}
		if(vp.size() == 0) {
			cout << "No se pudo encontrar un hijo factible." << endl;
			for(int i = 0; i < p.size(); i++) {
				r[i] = p[i];
			}
			return r;
		}
		sort(vp.begin(), vp.end());
		int spl_sz = (int)(vp.size() * alpha);
		int r_aux = rand_in_range(0, spl_sz);
		int node_j = vp[r_aux].second; 
		r[node_i] = node_j;
		if(node_j != root) {
			dsu.make_union(node_i, node_j);
		}
	}

	return r;
}

vector<int> Memetic::mutation(vector<int> &p) {
	int n = p.size();
	vector<int> r(n, -1);
	for(int i = 0; i < n; i++) {
		r[i] = p[i];
	}

	int node_i = root;
	while(node_i == root) {
		node_i = rand_in_range(0, n - 1);
	}
	cout << node_i << endl;

	vector<int> st;
	vector<int> S;
	DSU dsu(g->no_nodes);
	st.push_back(root);
	cout << "Raiz: " << root << endl;

	//Run DFS
	while(st.size() > 0) {
		int node_act = st.back();
		cout << node_act << endl;
		st.pop_back();
		S.push_back(node_act);
		if(p[node_act] != root) {
			dsu.make_union(node_act, p[node_act]);
		}
		for(int i = 0; i < n; i++) {
			if(i == node_i) {
				continue;
			}
			if(p[i] == node_act && node_act != root) {
				st.push_back(i);
			}
		}
	}
	return r;

	st.clear();
	st.push_back(node_i);
	int tree_cnt = 0;
	while(st.size() > 0) {
		int node_act = st.back();
		st.pop_back();
		tree_cnt++;
		for(int i = 0; i < n; i++) {
			if(p[i] == node_act && node_act != root) {
				st.push_back(i);
			}
		}
	}

	cout << "S:" << endl;
	for(int i = 0; i < S.size(); i++) {
		cout << S[i] << " ";
	}
	cout << endl << "DSU:" << endl;
	for(int i = 0; i < p.size(); i++) {
		cout << i << ": " << dsu.tree_size(i) << endl;
	}
	cout << endl << tree_cnt << endl;

	int idx_to_rem;
	for(int i = 0; i < S.size(); i++) {
		if(S[i] == p[node_i]) {
			idx_to_rem = i;
			break;
		}
	}
	S.erase(S.begin() + idx_to_rem);
	vector<pair<int, int> > nnodes;
	while(S.size() > 0) {
		int idx_aux = rand_in_range(0, S.size() - 1);
		int node_j = S[idx_aux];

		//Ver si los nodos están conectados en el grafo
		bool can_connect = false;
		int weight = -1;
		for(int x = 0; x < g->adj[node_j].size(); x++) {
			if(g->adj[node_j][x].first == node_i) {
				can_connect = true;
				weight = g->adj[node_j][x].second;
				break;
			}
		}

		//Ver si no se violan restricciones de capacidad
		if(can_connect && dsu.tree_size(node_j) * c + tree_cnt * c <= k) {
			//Hacer la union
			nnodes.push_back(make_pair(weight, node_j));
		}
		S.erase(S.begin() + idx_aux);
	}

	if(S.size() == 0) {
		cout << "No se pudo encontrar una mutación factible." << endl;
		return r;
	}

	sort(nnodes.begin(), nnodes.end());
	double alpha = 0.8;
	int spl_sz = (int)(nnodes.size() * alpha);
	int r_aux = rand_in_range(0, spl_sz);
	int node_j = nnodes[r_aux].second;

	r[node_i] = node_j;
	return r;
}