#include "tree_builder.hpp"

Tree generate_random_tree(int n) {
	vector<int> arr(n), used;
	for(int i = 0; i < n; i++) {
		arr[i] = i;
	}
	Tree t = create_tree(n);
	random_shuffle(arr.begin(), arr.end());
	int idx = 0;

	used.push_back(arr[idx++]);
	while(idx < n) {
		int r = rand() % idx;
		t.adj[used[r]].push_back(arr[idx]);
		used.push_back(arr[idx++]);
	}
	compute_parents(t);

	return t;
}

vector<pair<int, int> > generate_random_queries(Tree &t, int m) {
	int n = t.n, u = 0, v = 0;
	vector<pair<int, int> > res;
	for(int i = 0; i < m; i++) {
		while(u == v) {
			u = rand() % n;
			v = rand() % n;
		}
		res.push_back(make_pair(u, v));
		u = v = 0;
	}

	return res;
}

void save_in_file(Tree &t, vector<pair<int, int> > &queries, string name) {
	ofstream file;
	file.open(name.c_str());
	int n = t.n;
	int m = queries.size();
	file << n << "\n";
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < t.adj[i].size(); j++) {
			file << i << " " << t.adj[i][j] << "\n";
		}
	}
	file << m << "\n";
	for(int i = 0; i < m; i++) {
		file << queries[i].first << " " << queries[i].second << "\n";
	}
	file.close();
}

void print_tree(Tree &t) {
	int n = t.n;
	for(int i = 0; i < n; i++) {
		cout << i << " -> ";
		bool flag = false;
		for(int j = 0; j < t.adj[i].size(); j++) {
			cout << t.adj[i][j];
			if(j < t.adj[i].size() - 1) {
				cout << " ";
			}
			flag = true;
		}
		if(!flag) {
			cout << "Nothing";
		}
		cout << "\n";
	}

	//Print parents
	cout << "\nParents:\n";
	for(int i = 0; i < n; i++) {
		cout << i << ": " << t.parent[i] << "\n";
	}

	//Print root
	cout << "\nRoot: " << t.root << "\n";
}