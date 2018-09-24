#include <iostream>
#include <vector>
#include <algorithm>

#include "lca.hpp"

using namespace std;

int main() {
	int n, m, u, v, a, b;
	cin >> n;
	Tree t = create_tree(n);
	for(int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		t.adj[u].push_back(v);
	}
	compute_parents(t);
	cin >> a >> b;
	cout << lca_naive(t, a, b) << "\n";
	vector<int> path;
	euler_tour(t, path, t.root);
	for(int i = 0; i < path.size(); i++) {
		cout << path[i] << " ";
	}
	cout << "\n";

	return 0;
}