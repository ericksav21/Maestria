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

int dist[MAXN][MAXN];
bool mat[MAXN][MAXN];

//Se usan para generar los vecinos de la casilla actual
int row[] = {-1, 1, 0, 0};
int col[] = {0, 0, -1, 1};

//m: Filas, n: Columnas
int m, n, sz, cp_r[3], cp_c[3], cp_time[3];
int cnt, no_paths;

/*
	Este método verifica si una posición está adentro o no 
	de la matriz.
*/
bool check_boundaries(int y, int x) {
	return (y >= 0 && y < m &&
			x >= 0 && x < n);
}

/*
	Este método ejecuta un BFS partiendo de la casilla final a las demás.
	Se usa una matriz auxiliar para guardar los resultados por casilla.
	Actualmente esta función no es usada en el algoritmo pero se dejó en el código.
*/
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
			if(check_boundaries(y_new, x_new) &&
				!mat[y_new][x_new] &&
				dist[y_new][x_new] == INT_MAX) {

				dist[y_new][x_new] = dist[y][x] + 1;
				q.push(mp(y_new, x_new));
			}
		}
	}
}

/*
	Este método se usa para saber si desde una cierta casilla existe
	un camino a las demás sin pasar más de una vez por alguna
*/
bool is_blocked(int y, int x) {
    int y_i, x_i;
    bool lst = false, act = false, fst = false;
    int outs = 0;
    fst = lst = act = !check_boundaries(y - 1, x - 1) || mat[y - 1][x - 1];
    act = !check_boundaries(y - 1, x) || mat[y - 1][x]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y - 1, x + 1) || mat[y - 1][x + 1]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y, x + 1) || mat[y][x + 1]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y + 1, x + 1) || mat[y + 1][x + 1]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y + 1, x) || mat[y + 1][x]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y + 1, x - 1) || mat[y + 1][x - 1]; if(act != lst) outs++;
    lst = act;
    act = !check_boundaries(y, x - 1) || mat[y][x - 1]; if(act != lst) outs++;
    if(act != fst) outs++;

    return outs >= 4;
}

/*
	Distancia de Manhattan
*/
int manhattan(int y1, int x1, int y2, int x2) {
	return abs(x2 - x1) + abs(y2 - y1);
}

/*
	Búsqueda completa
*/
void solve(int y, int x, int cnt, int nxt_cp) {
	//Si se pisa la casilla final
	if(y == 0 && x == 1) {
		if(cnt == sz) {
			no_paths++;
		}
		return;
	}
	//Hacer poda
	//Si pisa una casilla antes de ser necesario
	bool hit_cp = false;
	if(nxt_cp < 3 && y == cp_r[nxt_cp] && x == cp_c[nxt_cp]) {
		if(cnt < cp_time[nxt_cp]) {
			return;
		}
		else hit_cp = true;
	}
	//Si no pisa la casilla en el momento exacto
	if(nxt_cp < 3 && !hit_cp && cnt == cp_time[nxt_cp]) {
		return;
	}

	//Si no pisará la casilla a tiempo
	if(nxt_cp < 3) {
		int md = manhattan(y, x, cp_r[nxt_cp], cp_c[nxt_cp]);
		if(cnt + md > cp_time[nxt_cp]) {
			return;
		}
	}
	//Si se autobloqueó
	if(is_blocked(y, x)) {
		return;
	}

	for(int i = 0; i < 4; i++) {
		int x_new = x + col[i], y_new = y + row[i];
		if(!check_boundaries(y_new, x_new) || mat[y_new][x_new]) continue;
		mat[y_new][x_new] = true;
		if(hit_cp) solve(y_new, x_new, cnt + 1, nxt_cp + 1);
		else solve(y_new, x_new, cnt + 1, nxt_cp);
		mat[y_new][x_new] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int cc = 1;
	while(cin >> m >> n) {
		if(m == 0 && n == 0) break;

		sz = m * n;
		cp_time[0] = (int)(sz / 4);
		cp_time[1] = (int)(sz / 2);
		cp_time[2] = (int)(3 * sz / 4);
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				mat[i][j] = false;
			}
		}
		for(int i = 0; i < 3; i++) {
			cin >> cp_r[i] >> cp_c[i];
		}
		no_paths = 0;
		mat[0][0] = true;
		solve(0, 0, 1, 0);
		cout << "Case " << cc << ": " << no_paths << "\n";
		cc++;
	}

	return 0;
}