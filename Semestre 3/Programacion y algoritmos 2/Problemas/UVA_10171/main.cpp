#include <iostream>
#include <vector>
#include <algorithm>

#define INF 100000
#define MAXN 35

using namespace std;

int cost_y[MAXN][MAXN];
int cost_m[MAXN][MAXN];

int n;

int main() {
	char type, direct, u, v, ss, sm;
	int ener;

	while(cin >> n && n) {
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				cost_y[i][j] = cost_m[i][j] = INF;
			}
		}
		for(int i = 0; i < n; i++) {
			cin >> type >> direct >> u >> v >> ener;
			if (type == 'Y') {
				cost_y[u - 'A'][v - 'A'] = ener;
				if(direct == 'B') {
					cost_y[v - 'A'][u - 'A'] = ener;
				}
			}
			else {
				cost_m[u - 'A'][v - 'A'] = ener;
				if(direct == 'B') {
					cost_m[v - 'A'][u - 'A'] = ener;
				}
			}
		}
		cin >> ss >> sm;

		for(int i = 0; i < MAXN; i++) {
			cost_y[i][i] = cost_m[i][i] = 0;
		}

		for(int k = 0; k < MAXN; k++) {
			for(int i = 0; i < MAXN; i++) {
				for(int j = 0; j < MAXN; j++) {
					if(cost_y[i][k] + cost_y[k][j] < cost_y[i][j]) {
						cost_y[i][j] = cost_y[i][k] + cost_y[k][j];
					}
					if(cost_m[i][k] + cost_m[k][j] < cost_m[i][j]) {
						cost_m[i][j] = cost_m[i][k] + cost_m[k][j];
					}
				}
			}
		}

		int min_ener = INF;
		for(int i = 0; i < MAXN; i++) {
			if(cost_y[ss - 'A'][i] == INF || cost_m[sm - 'A'][i] == INF) continue;
			min_ener = min(min_ener, cost_y[ss - 'A'][i] + cost_m[sm - 'A'][i]);
		}

		if(min_ener == INF) {
			cout << "You will never meet.\n";
		}
		else {
			cout << min_ener;
			for(int i = 0; i < MAXN; i++) {
				if(cost_y[ss - 'A'][i] + cost_m[sm - 'A'][i] == min_ener) {
					cout << " " << (char)(i + 'A');
				}
			}
			cout << "\n";
		}
	}

	return 0;
}