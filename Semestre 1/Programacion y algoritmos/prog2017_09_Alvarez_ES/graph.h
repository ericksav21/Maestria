#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <queue>
#include <string>
#include <algorithm>

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

typedef pair<int, int> Node;

const int INF = 10000;

class Node_cmp {
public:
	bool operator()(Node n1, Node n2) {
		return n1.snd > n2.snd;
	}
};

int rand_in_range(int a, int b);

void fill_graph(vector<vector<Node> > &adj);

void print_graph(vector<vector<Node> > &adj);

vector<int> dijkstra(vector<vector<Node> > adj, vector<int> &dist, int init);

void get_path(vector<int> prev, vector<int> &p, int dest);

vector<int> shortest_path(vector<vector<Node> > adj, vector<int> &dist, int orig, int dest);

#endif