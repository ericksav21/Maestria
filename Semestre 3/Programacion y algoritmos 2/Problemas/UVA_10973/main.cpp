#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 3005
#define pb push_back
#define mp make_pair

using namespace std;

vector<int> adj[MAXN];
bool flag[MAXN];
int n, m;

void clear_adj() {
	memset(flag, false, sizeof(flag));
	for(int i = 0; i < MAXN; i++) {
		adj[i].clear();
	}
}

int main() {
	int t, u, v;
	scanf("%d", &t);
	while(t--) {
		clear_adj();
		scanf("%d %d", &n, &m);
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			if(u < v) adj[u].pb(v);
			else adj[v].pb(u);
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < adj[i].size(); j++) {
				flag[adj[i][j]] = true;
			}
			for(int j = 0; j < adj[i].size(); j++) {
				int y = adj[i][j];
				for(int k = 0; k < adj[y].size(); k++) {
					int z = adj[y][k];
					if(flag[z]) cnt++;
				}
			}
			for(int j = 0; j < adj[i].size(); j++) {
				flag[adj[i][j]] = false;
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}