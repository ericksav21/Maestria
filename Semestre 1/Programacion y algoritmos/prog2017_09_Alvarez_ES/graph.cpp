#include "graph.hpp"

void fill_graph(vector<vector<Node> > &adj) {
	adj[1].pb(mp(2, 7));
	adj[1].pb(mp(4, 2));
	adj[2].pb(mp(4, 2));
	adj[2].pb(mp(3, 1));
	adj[3].pb(mp(5, 5));
	adj[4].pb(mp(2, 3));
	adj[4].pb(mp(3, 8));
	adj[4].pb(mp(5, 5));
	adj[5].pb(mp(3, 4));
}