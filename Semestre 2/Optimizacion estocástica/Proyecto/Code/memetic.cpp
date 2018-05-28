#include "memetic.hpp"

Memetic::Memetic(Graph g, int k) {
	this->g = copy_graph(g);
	this->k = k;
	vector<int> v = generate_ind();
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

Memetic::~Memetic() {
	delete g;
}

void Memetic::update_capacities(vector<int> &cap, vector<int> p, int node_j, int c_act, bool subs) {
	if(subs)
		cap[node_j] -= c_act;
	else
		cap[node_j] += c_act;
	if(node_j == 0) {
		return;
	}

	int bfr = p[node_j];
	int c_new = g->node_list[bfr];
	update_capacities(cap, p, bfr, c_new, subs);
}

vector<int> Memetic::generate_ind() {
	vector<int> p(g->no_nodes, 0);
	vector<int> S, U, capacity(g->no_nodes, k);
	int root = 0;
	//Colocar el nodo raíz
	S.push_back(root);
	for(int i = 1; i < g->no_nodes; i++) {
		U.push_back(i);
		capacity[i] = k - g->node_list[i];
	}

	while(U.size() > 0) {
		int r_s = rand_in_range(0, S.size() - 1);
		int node_j = S[r_s];

		//Seleccionar un nodo i de U
		vector<pair<int, int> > v_aux;
		vector<int> U_aux = U;
		int alpha = max(1, (int)(U_aux.size() * 0.7));
		for(int x = 0; x < alpha; x++) {
			int r_aux = rand_in_range(0, U_aux.size() - 1);
			v_aux.push_back(make_pair(g->node_list[U_aux[r_aux]], U_aux[r_aux]));
			U_aux.erase(U_aux.begin() + r_aux);
		}
		sort(v_aux.begin(), v_aux.end());
		//Bandera que indica si se pudo encontrar un nodo j que no
		//no cumpla las condiciones
		bool flag = false;
		for(int x = 0; x < v_aux.size(); x++) {
			int c_act = v_aux[x].first;
			int node_act = v_aux[x].second;
			int idx_act = 0;
			for(int y = 0; y < U.size(); y++) {
				if(U[y] == node_act) {
					idx_act = y;
					break;
				}
			}
			
			bool can_connect = false;
			for(int i = 0; i < g->adj[node_j].size(); i++) {
				if(g->adj[node_j][i].first == node_act) {
					can_connect = true;
					break;
				}
			}

			int bfr = node_j;
			while(true) {
				if(p[bfr] == root) {
					break;
				}
				bfr = p[bfr];
			}
			if(can_connect && capacity[bfr] - c_act >= 0) {
				flag = true;
				//Actualizar las capacidades de todos los nodos que están entre i y j
				p[node_act] = node_j;
				if(bfr != root) {
					capacity[bfr] -= c_act;
				}

				S.push_back(node_act);
				U.erase(U.begin() + idx_act);
				break;
			}
		}
		if(!flag) {
			/*if(node_j != root) {
				S.erase(S.begin() + r_s);
				U.push_back(node_j);
			}
			if(S.size() == 0) {
				cout << "No se pudo generar un individuo factible del grafo." << endl;
				break;
			}*/
			//Actualizar la capacidad del padre de j
			int bfr = node_j;
			//cout << "Borrar nodo: " << node_j << endl;
			while(true) {
				if(p[bfr] == root) {
					break;
				}
				bfr = p[bfr];
			}
			/*cout << "Capacidad: " << capacity[bfr] << endl;
			for(int i = 0; i < p.size(); i++) {
				cout << p[i] << " ";
			}
			cout << endl;
			if(bfr == root) {
				capacity[bfr] = k;
			}
			else {
				capacity[bfr] = k - g->node_list[node_j];
			}
			cout << "Nueva capacidad: " << capacity[node_j] << endl;*/

			//Quitar el nodo j de p
			queue<int> q;
			q.push(node_j);
			int cnt_cap = g->node_list[node_j];
			//BFS
			while(!q.empty()) {
				//cout << q.size() << endl;
				int aux = q.front();
				q.pop();
				if(aux != root) {
					int idx = -1;
					int nn;
					for(int i = 0; i < S.size(); i++) {
						if(aux == S[i]) {
							idx = i;
							nn = S[i];
							break;
						}
					}
					if(idx != -1) {
						S.erase(S.begin() + idx);
						U.push_back(nn);
					}
				}

				int bfr_j = p[aux];
				for(int i = 0; i < p.size(); i++) {
					if(p[i] == aux && p[i] != root) {
						p[i] = 0;
						cnt_cap += g->node_list[i];
						q.push(i);
					}
				}
				p[aux] = 0;
			}

			if(bfr == root) {
				capacity[bfr] = k;
			}
			else {
				capacity[bfr] = k - cnt_cap;
			}
			/*for(int i = 0; i < p.size(); i++) {
				cout << p[i] << " ";
			}
			cout << endl << endl;
			for(int i = 0; i < p.size(); i++) {
				if(p[i] == node_j) {
					p[i] = bfr_j;
				}
			}
			p[node_j] = 0;*/
		}
	}
	for(int i = 0; i < capacity.size(); i++) {
		cout << capacity[i] << " ";
	}
	cout << endl;

	return p;
}