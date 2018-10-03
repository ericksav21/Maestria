#include "lca.hpp"

/*
	Esta función genera un árbol vacío
*/
Tree create_tree(int n) {
	Tree res;
	res.n = n;
	res.adj.resize(n);
	res.parent.resize(n);
	for(int i = 0; i < n; i++) res.parent[i] = i;
	res.root = -1;

	return res;
}

/*
	Esta función calcula los padres de cada nodo y los guarda en el vector parent de la estructura
*/
void compute_parents(Tree &t) {
	int n = t.n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < t.adj[i].size(); j++) {
			t.parent[t.adj[i][j]] = i;
		}
	}
	for(int i = 0; i < n; i++) {
		if(t.parent[i] == i) {
			t.root = i;
			break;
		}
	}
}

/*
	Algoritmo trivial del LCA
*/
int lca_naive(Tree &t, int u, int v) {
	int n = t.n, lca = -1;
	bool vis[n];
	for(int i = 0; i < n; i++) vis[i] = false;

	while(true) {
		vis[u] = true;
		if(t.parent[u] == u) break;
		u = t.parent[u];
	}

	while(true) {
		if(vis[v]) {
			lca = v;
			break;
		}
		v = t.parent[v];
	}

	return lca;
}

vector<vector<int> > table;

/*
	Preprocesamiento de la Sparse table
*/
void preprocess_st(vector<pair<int, int> > &path) {
	int sz = path.size();
	int k = (int)log2(sz);
	table.resize(sz + 5, vector<int>(k + 5, 0));
	for(int i = 0; i < sz; i++) {
		table[i][0] = i;
	}
	for(int j = 1; (1 << j) <= sz; j++) {
		for(int i = 0; i + (1 << j) - 1 < sz; i++) {
			if(path[table[i][j - 1]].first < path[table[i + (1 << (j - 1))][j - 1]].first) {
				table[i][j] = table[i][j - 1];
			}
			else {
				table[i][j] = table[i + (1 << (j - 1))][j - 1];
			}
		}
	}
}

/*
	Hacer una query tipo RMQ a la Sparse table
*/
int lca_optimized(vector<pair<int, int> > &path, vector<int> &occurences, int l, int r) {
	int res = -1;
	if(occurences[l] > occurences[r]) {
		swap(l, r);
	}
	int lq = occurences[l], rq = occurences[r];
	int k = (int)log2(rq - lq + 1);

	if(path[table[lq][k]].first <= path[table[rq - (1 << k) + 1][k]].first) {
		res = table[lq][k];
	}
	else {
		res = table[rq - (1 << k) + 1][k];
	}

	return path[res].second;
}

/*
	Tour euleriano al árbol, se guarda el camino en el vector path y la primer ocurrencia de cada nodo en el
	vector occurences
*/
void euler_tour(Tree &t, vector<pair<int, int> > &path, vector<int> &occurences, int node, int lvl) {
	path.push_back(make_pair(lvl, node));
	if(occurences[node] == -1) occurences[node] = path.size() - 1;
	for(int i = 0; i < t.adj[node].size(); i++) {
		int children = t.adj[node][i];
		euler_tour(t, path, occurences, children, lvl + 1);
		path.push_back(make_pair(lvl, node));
		if(occurences[node] == -1) occurences[node] = path.size() - 1;
	}
}