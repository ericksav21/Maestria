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

Graph::Graph(int no_nodes) {
	this->no_nodes = no_nodes + 1;
	node_list.resize(no_nodes + 1, 0);
	adj.resize(no_nodes + 1, vector<pair<int, int> >(0));
}

Graph::~Graph() {}

void Graph::add_node(int from_id, int to_id, int from_weight, int to_weight, int cost) {
	Node from_node = create_node(from_weight, from_id);
	Node to_node = create_node(to_weight, to_id);
	Edge new_edge = create_edge(from_node, to_node, cost);

	//Añadir de forma no dirigida
	adj[from_id].push_back(make_pair(to_id, cost));	
	adj[to_id].push_back(make_pair(from_id, cost));
	edge_list.push_back(new_edge);
	node_list[from_id] = from_weight;
	node_list[to_id] = to_weight;
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

void Graph::print_weights() {
	for(int i = 0; i < node_list.size(); i++) {
		cout << "Nodo " << (i) << ", peso: " << node_list[i] << endl;
	}
}

Graph read_graph(string files_name) {
	ifstream f;
	f.open(files_name.c_str());
	int no_nodes, no_edges;
	int u, v, w;

	f >> no_nodes >> no_edges;
	Graph res(no_nodes);
	for(int i = 0; i < no_edges; i++) {
		f >> u >> v >> w;
		res.add_node(u, v, 1, 1, w);
	}

	f.close();
	return res;
}

Graph *copy_graph(Graph g) {
	Graph *res = new Graph(g.no_nodes - 1);
	res->adj = g.adj;
	res->node_list = g.node_list;
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

	if(rx == ry) {
		return;
	}

	p[rx] = ry;
}

bool DSU::same_cmp(int x, int y) {
	return find(x) == find(y);
}

DSU create_DSU(int n) {
	DSU res;
	res.n = n + 1;
	res.p.resize(n + 1);
	for(int i = 0; i <= n; i++) {
		res.p[i] = i;
	}

	return res;
}