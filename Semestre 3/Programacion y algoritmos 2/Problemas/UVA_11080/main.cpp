#include <bits/stdc++.h>

#define MAXN 205

using namespace std;

vector<int> adj[MAXN];
int col[MAXN];

int bfs(int src) {
	col[src] = 1;
	queue<int> q;
	q.push(src);
	int cnt = 1, black = 0;

	while(!q.empty()) {
		int u = q.front();
		int col_u = col[u];
		q.pop();

		if(col_u == 1) black++;

		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			int col_v = 1 - col_u;

			if(col[v] == -1) {
				col[v] = col_v;
				cnt++;
				q.push(v);
			}
			else if(col[v] == col[u]) return -1;
		}
	}

	if(cnt == 1) return 1;
	return min(black, cnt - black);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, v, e, a, b;
	cin >> t;
	while(t--) {
		for(int i = 0; i < MAXN; i++) {
			adj[i].clear();
		}

		cin >> v >> e;
		for(int i = 0; i < e; i++) {
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		
		int res = 0;
		memset(col, -1, sizeof(col));
		for(int i = 0; i < v; i++) {
			if(col[i] == -1) {
				int aux = bfs(i);
				if(aux == -1) {
					res = -1;
					break;
				}
				res += aux;
			}
		}

		cout << res << "\n";
	}

	return 0;
}