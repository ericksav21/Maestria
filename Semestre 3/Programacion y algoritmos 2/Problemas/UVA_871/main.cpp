#include <bits/stdc++.h>

#define MAXN 30

using namespace std;

int n, m;
int grid[MAXN][MAXN];
bool vis[MAXN][MAXN];

bool is_valid(int r, int c) {
	return (r >= 0 && r < n && c >= 0 && c < m);
}

int bfs(int rs, int cs) {
	vis[rs][cs] = true;
	int cnt = 1;
	queue<pair<int, int> > q;
	q.push(make_pair(rs, cs));

	while(!q.empty()) {
		pair<int, int> pii = q.front();
		int r_act = pii.first;
		int c_act = pii.second;
		q.pop();

		for(int i = -1; i <= 1; i++) {
			for(int j = -1; j <= 1; j++) {
				if(i == 0 && j == 0) continue;
				if(!is_valid(r_act + i, c_act + j)) continue;
				if(!grid[r_act + i][c_act + j]) continue;

				if(!vis[r_act + i][c_act + j]) {
					vis[r_act + i][c_act + j] = true;
					cnt++;
					q.push(make_pair(r_act + i, c_act + j));
				}
			}
		}
	}

	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	string str;
	cin >> t;
	getline(cin, str);
	getline(cin, str);

	while(t--) {
		memset(vis, false, sizeof(vis));
		n = 0;
		while(true) {
			getline(cin, str);
			if(str.size() == 0) break;
			m = str.size();
			for(int i = 0; i < m; i++) {
				grid[n][i] = str[i] - '0';
			}
			n++;
		}

		int res = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(grid[i][j] && !vis[i][j]) {
					int aux = bfs(i, j);
					res = max(res, aux);
				}
			}
		}

		cout << res << "\n";
		if(t) {
			cout << "\n";
		}
	}

	return 0;
}