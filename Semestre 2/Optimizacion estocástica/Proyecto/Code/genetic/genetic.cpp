#include "genetic.hpp"

Genetic::Genetic(Graph g, int k, int c, int root, int pop_size, double mutation_rate) {
	this->g = copy_graph(g);
	this->k = k;
	this->c = c;
	this->root = root;
	this->pop_size = pop_size;
	this->mutation_rate = mutation_rate;
}

Genetic::~Genetic() {
	delete g;
}

void Genetic::set_filesname(string files_name) {
	this->files_name = files_name;
}

void Genetic::set_ex_no(int ex_no) {
	this->ex_no = ex_no;
}

DSU Genetic::get_dsu(vector<int> &p) {
	DSU res(g->no_nodes);
	stack<int> st;
	st.push(root);
	while(!st.empty()) {
		int node_act = st.top();
		st.pop();
		if(p[node_act] != root) {
			res.make_union(node_act, p[node_act]);
		}
		for(int i = 0; i < p.size(); i++) {
			if(p[i] == node_act && i != root) {
				st.push(i);
			}
		}
	}

	return res;
}

vector<int> Genetic::generate_ind() {
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
			//cout << "No se pudo generar un individuo factible del grafo." << endl;
			break;
		}
	}

	return p;
}

int Genetic::fitness(vector<int> &ind) {
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

vector<int> Genetic::crossover(vector<int> &p, vector<int> &q) {
	int n = p.size();
	vector<int> r(n, -1);
	vector<int> U;
	queue<int> no_connected;
	DSU dsu_r(g->no_nodes);

	for(int i = 0; i < n; i++) {
		if(p[i] == q[i]) {
			r[i] = p[i];
			if(p[i] != root) {
				dsu_r.make_union(i, p[i]);
			}
		}
	}
	for(int i = 0; i < r.size(); i++) {
		if(r[i] == -1) {
			U.push_back(i);
		}
	}

	DSU dsu_aux_p = get_dsu(p);
	DSU dsu_aux_q = get_dsu(q);
	while(U.size() > 0) {
		int r_s = rand_in_range(0, U.size() - 1);
		int node_i = U[r_s];
		int r_aux = rand_in_range(0, 1);
		int node_j;

		bool can_connect = false;
		if(r_aux == 0) {
			node_j = p[node_i];
			if(!dsu_aux_p.same_cmp(node_i, node_j)) {
				//Ver si son adyacentes en el grafo
				bool is_ady = false;
				for(int x = 0; x < g->adj[node_j].size(); x++) {
					if(g->adj[node_j][x].first == node_i) {
						is_ady = true;
						break;
					}
				}
				if(is_ady) {
					//Verificar capacidades
					if(node_j == root || dsu_r.tree_size(node_j) * c + dsu_r.tree_size(node_i) * c <= k) {
						//Se pueden conectar
						r[node_i] = node_j;
						dsu_r.make_union(node_i, node_j);
						can_connect = true;
					}
				}
			}
		}
		else if(!can_connect) {
			node_j = q[node_i];
			if(!dsu_aux_q.same_cmp(node_i, node_j)) {
				//Ver si son adyacentes en el grafo
				bool is_ady = false;
				for(int x = 0; x < g->adj[node_j].size(); x++) {
					if(g->adj[node_j][x].first == node_i) {
						is_ady = true;
						break;
					}
				}
				if(is_ady) {
					//Verificar capacidades
					if(node_j == root || dsu_r.tree_size(node_j) * c + dsu_r.tree_size(node_i) * c <= k) {
						//Se pueden conectar
						r[node_i] = node_j;
						dsu_r.make_union(node_i, node_j);
						can_connect = true;
					}
				}
			}
		}
		U.erase(U.begin() + r_s);
		//Si no se pudieron conectar
		if(!can_connect) {
			no_connected.push(node_i);
		}
	}

	//Procesar los nodos que no se pudieron conectar
	double alpha = 0.5;
	while(!no_connected.empty()) {
		int node_i = no_connected.front();
		no_connected.pop();
		vector<pair<int, int> > vp;

		for(int node_j = 0; node_j < p.size(); node_j++) {
			if(!dsu_r.same_cmp(node_i, node_j)) {
				for(int x = 0; x < g->adj[node_j].size(); x++) {
					if(g->adj[node_j][x].first == node_i) {
						if(node_j == root || dsu_r.tree_size(node_j) * c + dsu_r.tree_size(node_i) * c <= k) {
							vp.push_back(make_pair(g->adj[node_j][x].second, node_j));
						}
						break;
					}
				}
			}
		}

		if(vp.size() == 0) {
			//cout << "No se pudo encontrar un hijo factible." << endl;
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
			dsu_r.make_union(node_i, node_j);
		}
	}

	return r;
}

vector<int> Genetic::mutation(vector<int> &p) {
	int n = p.size();
	vector<int> r(n, -1);
	for(int i = 0; i < n; i++) {
		r[i] = p[i];
	}

	int node_i = root;
	while(node_i == root) {
		node_i = rand_in_range(0, n - 1);
	}

	vector<int> st;
	vector<int> S;
	DSU dsu(g->no_nodes);
	st.push_back(root);

	//Hacer DFS
	while(st.size() > 0) {
		int node_act = st.back();
		st.pop_back();
		S.push_back(node_act);
		if(p[node_act] != root) {
			dsu.make_union(node_act, p[node_act]);
		}
		for(int i = 0; i < n; i++) {
			if(i == node_i) {
				continue;
			}
			if(p[i] == node_act && i != root) {
				st.push_back(i);
			}
		}
	}

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
		if(can_connect) {
			if(node_j == root || dsu.tree_size(node_j) * c + tree_cnt * c <= k) {
				//Se pueden conectar!
				nnodes.push_back(make_pair(weight, node_j));
			}
		}
		S.erase(S.begin() + idx_aux);
	}

	if(nnodes.size() == 0) {
		//cout << "No se pudo encontrar una mutación factible." << endl;
		return r;
	}

	sort(nnodes.begin(), nnodes.end());
	double alpha = 0.5;
	int spl_sz = (int)(nnodes.size() * alpha);
	int r_aux = rand_in_range(0, spl_sz);
	int node_j = nnodes[r_aux].second;

	r[node_i] = node_j;
	return r;
}

vector<vector<int> > Genetic::generate_pop() {
	vector<vector<int> > pop;
	int cnt = 0;
	while(cnt < pop_size) {
		vector<int> ind = generate_ind();
		if(ind[0] == -1) {
			continue;
		}
		pop.push_back(ind);
		cnt++;
	}

	return pop;
}

vector<int> Genetic::tournament_selection(vector<vector<int> > &pop) {
	int ind1 = rand_in_range(0, pop.size() - 1);
	int ind2 = ind1;
	while(ind2 == ind1) {
		ind2 = rand_in_range(0, pop.size() - 1);
	}

	if(fitness(pop[ind1]) < fitness(pop[ind2])) {
		return pop[ind1];
	}
	else {
		return pop[ind2];
	}
}

vector<vector<int> > Genetic::evolve_pop(vector<vector<int> > &pop) {
	vector<vector<int> > new_pop(pop.size());
	new_pop[0] = pop[0];

	int cnt = 1;
	while(cnt < pop.size()) {
		vector<int> p1 = tournament_selection(pop);
		vector<int> p2 = tournament_selection(pop);
		vector<int> son = crossover(p1, p2);

		double pm = (double)rand() / (double)RAND_MAX;
		if(pm < mutation_rate) {
			vector<int> mut = mutation(son);
			new_pop[cnt] = mut;
		}
		else {
			new_pop[cnt] = son;
		}
		cnt++;
	}

	return new_pop;
}

void Genetic::run() {
	vector<vector<int> > pop = generate_pop();
	int pop_limit = 20000;
	clock_t ck_1 = clock();
	double register_event_time = 5.0, reg_evt_time_act = register_event_time;
	int cnt = 1;
	vector<pair<int, vector<int> > > pop_act;
	string res_name = files_name + "pop" + to_string(ex_no) + ".txt";
	ofstream file(res_name.c_str());

	while(true) {
		vector<vector<int> > ev_pop = evolve_pop(pop);
		pop_act.clear();
		for(int i = 0; i < ev_pop.size(); i++) {
			pop_act.push_back(make_pair(fitness(ev_pop[i]), ev_pop[i]));
		}
		sort(pop_act.begin(), pop_act.end(), pairCompare);
		best_fitness = pop_act[0].first;
		
		pop.clear();
		for(int i = 0; i < pop_act.size(); i++) {
			pop.push_back(pop_act[i].second);
		}

		if((cnt - 1) % 4 == 0) {
			cout << "Datos registrados en la generación: " << cnt - 1 << endl;
			file << "Gen: " << cnt - 1 << endl;
			for(int x = 0; x < pop.size(); x++) {
				for(int y = 0; y < pop[x].size(); y++) {
					file << pop[x][y] << " ";
				}
				file << endl;
			}
			file << best_fitness << endl << endl;
		}

		cnt++;
		if(cnt == pop_limit) {
			break;
		}
	}

	file.close();
}

bool pairCompare(const pair<int, vector<int> >& firstElem, const pair<int, vector<int> >& secondElem) {
  return firstElem.first < secondElem.first;
}
