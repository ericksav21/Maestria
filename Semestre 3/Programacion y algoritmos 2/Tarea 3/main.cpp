#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstring>
#include <fstream>

#include "lca.hpp"
#include "tree_builder.hpp"

#define INF 1e9 + 1

using namespace std;

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Error: Al menos dos parametros necesarios.\n";
		return 0;
	}
	if(atoi(argv[1]) == 1) {
		srand(time(NULL));
		int n = atoi(argv[2]);
		int m = atoi(argv[3]);
		string name = string(argv[4]);
		Tree t = generate_random_tree(n);
		vector<pair<int, int> > queries = generate_random_queries(t, m);
		save_in_file(t, queries, name);
		cout << "Archivo generado.\n";
		return 0;
	}

	ifstream file;
	ofstream out_naive, out_opti;
	file.open(argv[2]);
	out_naive.open("out_lca_naive.txt");
	out_opti.open("out_lca_optimized.txt");
	int n, m, u, v, l, r;
	vector<pair<int, int> > queries;
	clock_t begin, end;
	double time_elapsed;
	file >> n;

	Tree t = create_tree(n);
	for(int i = 0; i < n - 1; i++) {
		file >> u >> v;
		t.adj[u].push_back(v);
	}
	compute_parents(t);

	file >> m;
	for(int i = 0; i < m; i++) {
		file >> l >> r;
		queries.push_back(make_pair(l, r));
	}
	file.close();

	//LCA Naive
	cout << "Algoritmo naive en proceso...\n";
	begin = clock();
	for(int i = 0; i < m; i++) {
		l = queries[i].first;
		r = queries[i].second;

		out_naive << lca_naive(t, l, r) << "\n";
	}
	end = clock();
	out_naive.close();
	time_elapsed = (double)(end - begin) / (double)CLOCKS_PER_SEC;
	cout << "Algoritmo naive terminado.\n";
	cout << "Tiempo transcurrido: " << time_elapsed << "s.\n\n";

	//Preprocess Euler-tour
	cout << "Algoritmo optimizado en proceso...\n";
	begin = clock();
	vector<pair<int, int> > path;
	vector<int> occurences(n, -1);

	euler_tour(t, path, occurences, t.root, 0);

	//preprocess Sparse table
	preprocess_st(path);

	//LCA-RMQ
	for(int i = 0; i < m; i++) {
		l = queries[i].first;
		r = queries[i].second;

		out_opti << lca_optimized(path, occurences, l, r) << "\n";
	}
	end = clock();
	out_opti.close();
	time_elapsed = (double)(end - begin) / (double)CLOCKS_PER_SEC;
	cout << "Algoritmo optimizado terminado.\n";
	cout << "Tiempo transcurrido: " << time_elapsed << "s.\n";

	return 0;
}