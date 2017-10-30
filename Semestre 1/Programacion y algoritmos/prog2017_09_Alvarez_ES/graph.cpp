#include "graph.h"

/*void fill_graph(vector<vector<Node> > &adj) {
	adj[1].pb(mp(2, 7));
	adj[1].pb(mp(4, 2));
	adj[2].pb(mp(4, 2));
	adj[2].pb(mp(3, 1));
	adj[3].pb(mp(5, 5));
	adj[4].pb(mp(2, 3));
	adj[4].pb(mp(3, 8));
	adj[4].pb(mp(5, 5));
	adj[5].pb(mp(3, 4));
}*/

int rand_in_range(int a, int b) {
	return rand() % (b - a + 1) + a;
}

void fill_graph(vector<vector<Node> > &adj) {
	srand(time(NULL));
	for(int i = 1; i < adj.size(); i++) {
		for(int j = i + 1; j < adj.size(); j++) {
			int p = rand_in_range(1, 100);
			//P(2/3) de haber conexión
			if(p > 60) {
				int w = rand_in_range(1, 25);
				adj[i].pb(mp(j, w));
			}
		}
	}
}

void print_graph(vector<vector<Node> > &adj) {
	cout << "Grafo: " << endl;
	for(int i = 1; i < adj.size(); i++) {
		char c_orig = 'A' + (i - 1);
		cout << c_orig << " -> ";
		for(int j = 0; j < adj[i].size(); j++) {
			char c_node = 'A' + (adj[i][j].fst - 1);
			cout << c_node << "(w=" << adj[i][j].snd << ") ";
		}
		cout << endl;
	}
}

vector<int> dijkstra(vector<vector<Node> > adj, vector<int> &dist, int init) {
	fill(dist.begin(), dist.end(), INF);
	vector<int> prev(adj.size(), -1);
	vector<bool> vis(adj.size(), false);
	priority_queue<Node, vector<Node>, Node_cmp> pq;
	pq.push(mp(init, 0));
	dist[init] = 0;

	while(!pq.empty()) {
		Node act = pq.top();
		pq.pop();
		int u = act.fst;
		if(vis[u]) continue;
		vis[u] = true;

		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].fst;
			int w = adj[u][i].snd;

			if(!vis[v]) {
				if(dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					prev[v] = u;
					pq.push(mp(v, dist[v]));
				}
			}
		}
	}

	return prev;
}

void get_path(vector<int> prev, vector<int> &p, int dest) {
	if(prev[dest] != -1) {
		get_path(prev, p, prev[dest]);
	}
	p.pb(dest);
}

vector<int> shortest_path(vector<vector<Node> > adj, vector<int> &dist, int orig, int dest) {
	vector<int> prev = dijkstra(adj, dist, orig);
	vector<int> path;
	get_path(prev, path, dest);

	char c_orig = 'A' + (orig - 1), c_dest = 'A' + (dest - 1);
	cout << endl << "Distancia de " << c_orig << " a " << c_dest << ": " << dist[dest] << endl;
	cout << "Ruta: ";
	for(int i = 0; i < path.size(); i++) {
		char c_act = 'A' + (path[i] - 1);
		cout << c_act << " ";
	}
	cout << endl;

	return path;
}