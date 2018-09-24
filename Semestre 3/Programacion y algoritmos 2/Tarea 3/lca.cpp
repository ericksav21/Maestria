#include "lca.hpp"

Tree create_tree(int n) {
	Tree res;
	res.n = n;
	res.adj.resize(n);
	res.parent.resize(n);
	res.root = -1;

	return res;
}

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

void euler_tour(Tree &t, vector<int> &path, int node) {
	path.push_back(node);
	for(int i = 0; i < t.adj[node].size(); i++) {
		int children = t.adj[node][i];
		euler_tour(t, path, children);
		path.push_back(node);
	}
}