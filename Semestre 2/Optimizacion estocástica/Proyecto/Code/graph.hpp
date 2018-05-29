#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

typedef struct Node {
	bool operator==(const Node& op);

	int weight;
	int id;
} Node;

typedef struct Edge{
	void print();

	Node begin_node;
	Node end_node;
	int cost;
	bool valid;
} Edge;

typedef struct Graph {
	int no_nodes;
	vector<vector<pair<int, int> > > adj;
	vector<int> node_list;
	vector<Edge> edge_list;

	Graph(int no_nodes);
	~Graph();
	void add_node(int from_id, int to_id, int from_weight, int to_weight, int cost);
	void print_adj();
	void print_weights();

} Graph;

typedef struct DSU {
	DSU(int n);
	~DSU();

	int n;
	vector<int> p, sz;
	int find(int x);
	void make_union(int x, int y);
	bool same_cmp(int x, int y);
} DSU;

Node create_node(int weight, int id);

Edge create_edge(Node a, Node b, int cost);

void initializate_graph(int no_nodes);

Graph read_graph(string files_name);

Graph *copy_graph(Graph g);

int rand_in_range(int a, int b);

#endif