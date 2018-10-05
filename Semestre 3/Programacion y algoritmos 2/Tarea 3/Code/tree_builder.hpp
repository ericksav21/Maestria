#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
#include <cstring>
#include <fstream>

#include "lca.hpp"

using namespace std;

Tree generate_random_tree(int n);

vector<pair<int, int> > generate_random_queries(Tree &t, int m);

void save_in_file(Tree &t, vector<pair<int, int> > &queries, string name);

void print_tree(Tree &t);

#endif