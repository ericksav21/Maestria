#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>

#define MAXN 10005
#define INF 1e18

using namespace std;

typedef long long ll;

// DP, Arreglo de los datos y el arreglo ordenado
ll dp[105][MAXN], arr[MAXN], dom[MAXN];
int n, k;

/*
	Estructura para manejar las funciones en el LiChao
*/
typedef struct _F {
	ll dp, ak;

	_F() {
		dp = ak = 0;
	}

	_F(ll dp, ll ak) {
		this->dp = dp;
		this->ak = ak;
	}

	~_F() {}
} Function;

/*
	Evalúa la función f con respecto al X dado
*/
ll eval_f(Function f, ll x) {
	ll power = (f.ak - x) * (f.ak - x);
	return f.dp + power;
}

/*
	Clase de LiChao Tree con los métodos originales de inserción y buscado.
*/
class LiChao {
private:
	bool empty;
	vector<Function> tree;

public:
	LiChao() {
		empty = true;
		tree.resize(4 * MAXN);
	}
	~LiChao() {}
	
	void add_f(int node, int lo, int hi, Function f) {
		int mid = (lo + hi) / 2;
		int lc = 2 * node, rc = 2 * node + 1;

		bool is_left = eval_f(f, dom[lo]) < eval_f(tree[node], dom[lo]);
		bool is_mid = eval_f(f, dom[mid]) < eval_f(tree[node], dom[mid]);

		if(is_mid) {
			swap(tree[node], f);
		}
		if(hi - lo == 1) {
			return;
		}
		if(is_left != is_mid) {
			add_f(lc, lo, mid, f);
		}
		else {
			add_f(rc, mid, hi, f);
		}
	}

	void insert_f(Function f) {
		// Si el árbol está vacío pon la función en todos los nodos
		if(empty) {
			for(int i = 0; i < tree.size(); i++) {
				tree[i] = f;
			}
			empty = false;
		}
		else {
			add_f(1, 0, n - 1, f);
		}
	}

	ll _get(int node, int lo, int hi, ll x) {
		int mid = (lo + hi) / 2;
		int lc = 2 * node, rc = 2 * node + 1;

		if(hi - lo == 1) {
			return eval_f(tree[node], x);
		}
		else if(x < dom[mid]) {
			return min(eval_f(tree[node], x), _get(lc, lo, mid, x));
		}
		else {
			return min(eval_f(tree[node], x), _get(rc, mid, hi, x));
		}
	}

	ll get(ll x) {
		return _get(1, 0, n - 1, x);
	}
};

ll solve(int k, int n) {
	for(int i = 1; i <= n; i++) {
		dp[1][i] = (arr[i - 1] - arr[0]) * (arr[i - 1] - arr[0]);
	}

	// Cálculo Bottom-Up de la tabla usando el Li Chao
	for(int k_i = 2; k_i <= k; k_i++) {
		LiChao arr_tree;
		for(int i = k_i - 1; i < n; i++) {
			Function f_act(dp[k_i - 1][i], arr[i]);
			arr_tree.insert_f(f_act);
			dp[k_i][i + 1] = arr_tree.get(arr[i]);
		}
	}

	return dp[k][n];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
		dom[i] = arr[i];
	}
	//Lo usará el Li Chao
	sort(dom, dom + n);
	cout << solve(k, n) << "\n";

	return 0;
}