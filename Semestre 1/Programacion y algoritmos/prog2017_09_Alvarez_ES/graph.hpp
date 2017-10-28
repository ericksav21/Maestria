#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

typedef pair<int, int> Node;

void fill_graph(vector<vector<Node> > &adj);

#endif