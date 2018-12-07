#include <iostream>
#include <cstring>
#include <cmath>

#define MAXN 100010

using namespace std;

int b[MAXN];
bool vis[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, ans;
	while(true) {
		cin >> n >> m;
		if(n == 0 && m == 0) break;

		ans = 0;
		memset(vis, false, sizeof(vis));
		for(int i = 1; i <= m; i++) {
			cin >> b[i];
		}
		for(int i = 1; i <= m; i++) {
			for(int j = i; j <= m; j++) {
				int val = abs(b[j] - b[i]);
				if(!vis[val]) {
					vis[val] = true;
					ans++;
				}
			}
		}

		cout << (ans == (n + 1) ? "Y" : "N") << "\n";
	}

	return 0;
}