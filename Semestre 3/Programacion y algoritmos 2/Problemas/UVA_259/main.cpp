#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

#define INF 1000000
#define MAXN 38

using namespace std;

char app, pc;
vector<int> adj[MAXN];
int res[MAXN][MAXN];
int tot;

void reset() {
	for(int i = 0; i < MAXN; i++) {
		adj[i].clear();
		for(int j = 0; j < MAXN; j++) {
			res[i][j] = 0;
		}
	}
}

bool bfs(int s, int t, int *parent) {
	bool visited[MAXN];
	for(int i = 0; i < MAXN; i++) {
		visited[i] = false;
	}
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if(!visited[v] && res[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t] == true;
}

void fordFulkerson() {
	int u, v;
	int max_flow = 0;
	int parent[MAXN];

	int s = 0, t = 37;
	while(bfs(s, t, parent)) {
		int path_flow = INF;
		for(v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, res[u][v]);
		}

		for(v = t; v != s; v = parent[v]) {
			u = parent[v];
			res[u][v] -= path_flow;
			res[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	if(max_flow < tot) {
		printf("!\n");
	}
	else {
		for(int i = 27; i < 37; i++) {
			bool alloc = false;
			for(int j = 1; j <= 26; j++) {
				if(res[i][j]) {
					printf("%c", j + 'A' - 1);
					alloc = true;
					break;
				}
			}
			if(!alloc) {
				printf("_");
			}
		}
		printf("\n");
	}
}

int main() {
	bool flag = false;
	int n;

	while(true) {
		tot = 0;
		reset();
		for(int i = 27; i < 37; i++) {
			adj[i].push_back(37);
			adj[37].push_back(i);

			res[i][37] = 1;
		}

		while(true) {
			if(scanf("%c", &app) == EOF) {
				flag = true;
				break;
			}
			if(app == '\n') {
				break;
			}
			scanf("%d ", &n);

			int node_app = (int)(app - 'A' + 1);
			// Se añade doble para que se vea como red residual
			adj[0].push_back(node_app);
			adj[node_app].push_back(0);

			res[0][node_app] = n;

			tot += n;

			while(true) {
				scanf("%c", &pc);
				if(pc == ';') {
					scanf("%c", &pc);
					break;
				}
				int node_pc = (int)(pc - '0' + 27);
				adj[node_app].push_back(node_pc);
				adj[node_pc].push_back(node_app);

				res[node_app][node_pc] = 1;
			}
		}

		fordFulkerson();
		
		if(flag) {
			break;
		}
	}

	return 0;
}