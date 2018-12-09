#include <bits/stdc++.h>

#define MAXN 35

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	string str, str2;
	double ex;
	map<string, int> mp;
	double adj[MAXN][MAXN];
	int id = 1;
	while(cin >> n) {
		if(n == 0) break;

		mp.clear();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				adj[i][j] = 0.0;
			}
			adj[i][i] = 1.0;
		}
		for(int i = 0; i < n; i++) {
			cin >> str;
			mp[str] = i;
		}

		cin >> m;
		for(int i = 0; i < m; i++) {
			cin >> str >> ex >> str2;
			int id1 = mp[str];
			int id2 = mp[str2];

			adj[id1][id2] = max(adj[id1][id2], ex);
		}

		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					adj[i][j] = max(adj[i][j], adj[i][k] * adj[k][j]);
				}
			}
		}

		bool flag = false;
		for(int i = 0; i < n; i++) {
			if(adj[i][i] > 1.0) {
				flag = true;
				break;
			}
		}

		cout << "Case " << id << ": ";
		if(flag) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
		id++;
	}

	return 0;
}