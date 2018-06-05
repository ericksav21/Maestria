#include "graph.hpp"

void Edge::print() {
	cout << "Nodo a: (Peso=" << begin_node.weight << ", id=" << begin_node.id << ")" << endl;
	cout << "Nodo b: (Peso=" << end_node.weight << ", id=" << end_node.id << ")" << endl;
	cout << "Costo: " << cost << endl;
}

bool Node::operator==(const Node& op){
	return id == op.id;
}

Node create_node(int weight, int id) {
	Node res;
	res.weight = weight;
	res.id = 0;

	return res;
}

Edge create_edge(Node a, Node b, int cost) {
	Edge res;
	res.begin_node = a;
	res.end_node = b;
	res.cost = cost;
	res.valid = true;

	return res;
}

Graph::Graph(int no_nodes, int node_cost) {
	this->no_nodes = no_nodes;
	this->node_cost = node_cost;
	adj.resize(no_nodes, vector<pair<int, int> >(0));
}

Graph::~Graph() {}

void Graph::add_node(int from_id, int to_id, int cost) {
	Node from_node = create_node(node_cost, from_id);
	Node to_node = create_node(node_cost, to_id);
	Edge new_edge = create_edge(from_node, to_node, cost);

	//Añadir de forma no dirigida
	adj[from_id].push_back(make_pair(to_id, cost));	
	adj[to_id].push_back(make_pair(from_id, cost));
	edge_list.push_back(new_edge);
}

void Graph::print_adj() {
	cout << adj.size() << endl;
	for(int i = 0; i < adj.size(); i++) {
		cout << "Nodo " << (i) << ": ";
		for(int j = 0; j < adj[i].size(); j++) {
			int node_act = adj[i][j].first;
			int weight_act = adj[i][j].second;
			cout << "(N: " << node_act << ", P: " << weight_act << ")";
			if(j < adj[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}

Graph read_graph(string files_name) {
	ifstream f;
	f.open(files_name.c_str());
	int no_nodes, no_edges;
	int u, v, w;

	f >> no_nodes >> no_edges;
	Graph res(no_nodes, 1);
	for(int i = 0; i < no_edges; i++) {
		f >> u >> v >> w;
		res.add_node(u, v, w);
	}

	f.close();
	return res;
}

Graph read_graph_2(string files_name) {
	ifstream f;
	f.open(files_name.c_str());
	int no_nodes, node_cost;
	int w;

	f >> no_nodes >> node_cost;
	//cout << no_nodes << " " << node_cost << endl;
	Graph res(no_nodes, node_cost);
	for(int i = 0; i < no_nodes; i++) {
		for(int j = 0; j < no_nodes; j++) {
			f >> w;
			if(j <= i) {
				continue;
			}
			res.add_node(i, j, w);
		}
	}

	return res;
}

Graph *copy_graph(Graph g) {
	//Se resta 1 para que al final el grado copia no quede
	//con dos nodos extra.
	//Graph *res = new Graph(g.no_nodes - 1, g.node_cost);
	Graph *res = new Graph(g.no_nodes, g.node_cost);
	res->adj = g.adj;
	res->edge_list = g.edge_list;

	return res;
}

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

/*----- Union-Find -----*/
int DSU::find(int x) {
	if(p[x] == x) {
		return x;
	}
	return p[x] = find(p[x]);
}

void DSU::make_union(int x, int y) {
	int rx = find(x);
	int ry = find(y);

	if(sz[rx] < sz[ry]) {
		p[rx] = p[ry];
		sz[ry] += sz[rx];
	}
	else {
		p[ry] = p[rx];
		sz[rx] += sz[ry];
	}
}

bool DSU::same_cmp(int x, int y) {
	return find(x) == find(y);
}

int DSU::tree_size(int x) {
	return sz[find(x)];
}

DSU::DSU(int n) {
	this->n = n;
	p.resize(n, 0);
	sz.resize(n, 1);
	for(int i = 0; i < n; i++) {
		p[i] = i;
	}
}

DSU::~DSU() {}