#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <utility>
#include <climits>

#define MAXN 10

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

int mat[MAXN][MAXN], dist[MAXN][MAXN];
int row[] = {-1, 1, 0, 0};
int col[] = {0, 0, -1, 1};

//m: rows, n: cols
int m, n, sz, cp_r[3], cp_c[3], cp_time[3];
int cnt, no_paths;

bool check_boundaries(int y, int x) {
	return (y >= 0 && y < m &&
			x >= 0 && x < n);
}

void bfs() {
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			dist[i][j] = INT_MAX;
		}
	}

	queue<pair<int, int> > q;
	q.push(mp(0, 1));
	dist[0][1] = 0;

	while(!q.empty()) {
		pair<int, int> g_act = q.front(); q.pop();
		int y = g_act.fst, x = g_act.snd;

		for(int i = 0; i < 4; i++) {
			int x_new = x + col[i], y_new = y + row[i];
			if(check_boundaries(y_new && x_new) &&
				mat[y_new][x_new] == 0 &&
				dist[y_new][x_new] == INT_MAX) {

				dist[y_new][x_new] = dist[y][x] + 1;
				q.push(mp(y_new, x_new));
			}
		}
	}
}

int manhattan(int y1, int x1, int y2, int x2) {
	return abs(x2 - x1) + abs(y2 - y1);
}

void solve(int y, int x, int nxt_cp) {
	//Si se pisa la casilla final
	if(y == 0 && x == 1) {
		if(cnt == sz) no_paths++;
		return;
	}
	//Hacer poda
	//Si pisa una casilla antes de ser necesario
	bool hit_cp = false;
	if(nxt_cp < 3 && y == cp_r[nxt_cp] && x == cp_c[nxt_cp]) {
		if(cnt < cp_time[nxt_cp]) return;
		else hit_cp = true;
	}
	//Si no pisa la casilla en el momento exacto
	if(nxt_cp < 3 && !hit_cp && cnt == cp_time[nxt_cp]) return;

	//Si no pisará la casilla a tiempo
	if(nxt_cp < 3) {
		int md = manhattan(y, x, cp_r[nxt_cp], cp_c[nxt_cp]);
	}

	for(int i = 0; i < 4; i++) {
		int x_new = x + col[i], y_new = y + row[i];
		if(!check_boundaries(y_new, x_new)) continue;

	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while(cin >> m >> n) {
		if(m == 0 && n == 0) break;

		sz = m * n;
		cp_time[0] = (int)(sz / 4);
		cp_time[1] = (int)(sz / 2);
		cp_time[2] = (int)(3 * sz / 4);
		memset(mat, 0, sizeof(mat));
		no_paths = 0;
		cnt = 1;
		for(int i = 0; i < 3; i++) {
			cin >> cp_r[i] >> cp_c[i];
		}
	}

	return 0;
}