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

void preprocess_lca(Tree &t, vector<pair<int, int> > &path, vector<int> &occurences) {
	int n = t.n;
	euler_tour(t, path, occurences, t.root, 0);

	for(int i = 0; i < path.size(); i++) {
		cout << path[i].first << " " << path[i].second << "\n";
	}
	cout << "\n";
	for(int i = 0; i < n; i++) {
		cout << i << ": " << occurences[i] << "\n";
	}
}

int lca_optimized(Tree &t, vector<pair<int, int> > &path, vector<int> &occurences, int u, int v) {

	return 0;
}

void euler_tour(Tree &t, vector<pair<int, int> > &path, vector<int> &occurences, int node, int lvl) {
	path.push_back(make_pair(lvl, node));
	if(occurences[node] == -1) occurences[node] = path.size() - 1;
	for(int i = 0; i < t.adj[node].size(); i++) {
		int children = t.adj[node][i];
		euler_tour(t, path, children, lvl + 1);
		path.push_back(make_pair(lvl, node));
		if(occurences[node] == -1) occurences[node] = path.size() - 1;
	}
}