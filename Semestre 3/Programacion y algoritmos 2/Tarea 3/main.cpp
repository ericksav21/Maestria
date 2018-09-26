#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

#include "lca.hpp"

#define INF 1e9 + 1

using namespace std;

int main() {
	srand(time(NULL));

	int n, m, u, v, l, r;
	cin >> n;
	Tree t = create_tree(n);
	for(int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		t.adj[u].push_back(v);
	}
	compute_parents(t);
	cin >> l >> r;
	cout << lca_naive(t, l, r) << "\n";
	
	//Preprocess Euler-tour
	vector<pair<int, int> > path;
	vector<int> occurences(n, -1);

	euler_tour(t, path, occurences, t.root, 0);

	//preprocess Sparse table
	preprocess_st(path);
	cout << lca_optimized(path, occurences, l, r) << "\n";

	return 0;
}