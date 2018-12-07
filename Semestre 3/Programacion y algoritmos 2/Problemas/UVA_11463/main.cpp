#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAXN 105
#define INF 100000

using namespace std;

int adj[MAXN][MAXN];
int cost[MAXN][MAXN];

int n, r, s, e;

int main() {
	int t;
	cin >> t;
	int u, v;

	for(int c = 1; c <= t; c++) {
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				adj[i][j] = 0;
				cost[i][j] = INF;
			}
		}

		cin >> n >> r;
		for(int i = 0; i < r; i++) {
			cin >> u >> v;
			adj[u][v] = adj[v][u] = 1;
			cost[u][v] = cost[v][u] = 1;
		}
		cin >> s >> e;

		for(int i = 0; i < n; i++) {
			cost[i][i] = 0;
		}
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(cost[i][k] + cost[k][j] < cost[i][j]) {
						cost[i][j] = cost[i][k] + cost[k][j];
					}
				}
			}
		}

		int res = -1;
		for(int i = 0; i < n; i++) {
			res = max(res, cost[s][i] + cost[i][e]);
		}

		cout << "Case " << c << ": " << res << "\n";
	}

	return 0;
}