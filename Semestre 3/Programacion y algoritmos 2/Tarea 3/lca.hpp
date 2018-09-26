#ifndef LCA_HPP
#define LCA_HPP

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;

typedef struct tree_str {
	int n, root;
	vector<vector<int> > adj;
	vector<int> parent;
} Tree;

Tree create_tree(int n);

void compute_parents(Tree &t);

Tree generate_random_tree(int n);

int lca_naive(Tree &t, int u, int v);

void preprocess_st(vector<pair<int, int> > &path);

int lca_optimized(vector<pair<int, int> > &path, vector<int> &occurences, int u, int v);

void euler_tour(Tree &t, vector<pair<int, int> > &path, vector<int> &occurences, int node, int lvl);

#endif