#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <climits>

#define MAXN 1030

using namespace std;

int mat[MAXN][MAXN], sum[MAXN][MAXN];

void precalc() {
	for(int i = 0; i < MAXN; i++) {
		sum[0][i] = mat[0][i];
	}
	for(int i = 1; i < MAXN; i++) {
		for(int j = 0; j < MAXN; j++) {
			sum[i][j] = mat[i][j] + sum[i - 1][j];
		}
	}
	for(int i = 0; i < MAXN; i++) {
		for(int j = 1; j < MAXN; j++) {
			sum[i][j] += sum[i][j - 1];
		}
	}
}

int area(int x1, int y1, int x2, int y2) {
	int res = sum[x2][y2];
	if(x1 > 0) {
		res -= sum[x1 - 1][y2];
	}
	if(y1 > 0) {
		res -= sum[x2][y1 - 1];
	}
	if(x1 > 0 && y1 > 0) {
		res += sum[x1 - 1][y1 - 1];
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	precalc();

	int t, d, n, xi, yi, xmin, ymin, sz, res;
	cin >> t;
	while(t--) {
		memset(mat, 0, sizeof(mat));
		cin >> d >> n;
		for(int i = 0; i < n; i++) {
			cin >> xi >> yi >> sz;
			mat[xi][yi] += sz;
		}
		precalc();
		res = INT_MIN;
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				int x1 = max(i - d, 0);
				int y1 = max(j - d, 0);
				int x2 = min(i + d, MAXN - 1);
				int y2 = min(j + d, MAXN - 1);
				int res_act = area(x1, y1, x2, y2);
				if(res_act > res) {
					res = res_act;
					xmin = i;
					ymin = j;
				}
			}
		}

		cout << xmin << " " << ymin << " " << res << "\n";
	}

	return 0;
}