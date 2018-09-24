#ifndef LCA_HPP
#define LCA_HPP

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef struct tree_str {
	int n, root;
	vector<vector<int> > adj;
	vector<int> parent;
} Tree;

Tree create_tree(int n);

void compute_parents(Tree &t);

int lca_naive(Tree &t, int u, int v);

void euler_tour(Tree &t, vector<int> &path, int node);

#endif