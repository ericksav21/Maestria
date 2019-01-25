#include <bits/stdc++.h>

#define MAXN 11

using namespace std;

int grid[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int i = 1, n;
	while(cin >> n) {
		if(n == 0) break;
		cout << "Case " << i << ": ";

		for(int x = 0; x < n; x++) {
			for(int y = 0; y < n; y++) {
				cin >> grid[x][y];
			}
		}

		int sr = 0, sc = 0, er = n - 1, ec = n - 1;
		int n_sums = (int)ceil((float)n / 2.0);

		for(int j = 0; j < n_sums; j++) {
			int sum = 0, it;
			for(it = sc; it <= ec; it++) {
				sum += grid[sr][it];
			}
			for(it = sr + 1; it <= er; it++) {
				sum += grid[it][ec];
			}
			for(it = ec - 1; it >= sc; it--) {
				sum += grid[er][it];
			}
			for(it = er - 1; it >= (sr + 1); it--) {
				sum += grid[it][sc];
			}
			cout << sum;
			if(j < n_sums - 1) {
				cout << " ";
			}
			sr++; sc++;
			er--; ec--;
		}

		cout << "\n";
		i++;
	}


	return 0;
}