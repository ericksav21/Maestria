#include <bits/stdc++.h>

#define MAXN 105
#define INF 1000000
#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

typedef pair<int, int> pii;

int n, m, dest, t;
vector<pair<int, int> > adj[MAXN];

void clear_adj() {
	for(int i = 0; i < MAXN; i++) {
		adj[i].clear();
	}
}

void dijkstra(int *dist) {
	dist[dest] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.push(mp(0, dest));

	while(!pq.empty()) {
		pii act = pq.top();
		pq.pop();

		int d = act.fst;
		int u = act.snd;

		if(d > dist[u]) continue;

		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].fst;
			int w = adj[u][i].snd;

			if(dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.push(mp(dist[v], v));
			}
		}
	}
}

int main() {
	int cc, u, v, w;
	cin >> cc;

	for(int i = 0; i < cc; i++) {
		clear_adj();
		cin >> n >> dest >> t >> m;
		for(int j = 0; j < m; j++) {
			cin >> u >> v >> w;
			adj[v].pb(mp(u, w));
		}

		int dist[n + 1];
		for(int j = 0; j <= n; j++) {
			dist[j] = INF;
		}
		dijkstra(dist);
		int cnt = 0;
		for(int node = 1; node <= n; node++) {
			if(dist[node] <= t) cnt++;
		}

		cout << cnt << "\n";
		if(i < cc - 1) {
			cout << "\n";
		}
	}

	return 0;
}