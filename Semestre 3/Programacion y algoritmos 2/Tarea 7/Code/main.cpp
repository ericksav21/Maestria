#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <utility>
#include <cstring>

#define MAXN 200010
#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

int t, n, m, q;
int block_size;

typedef struct _Query {
	int left, right;
	int bloq_l, bloq_r;
	int id;

	_Query() {}
	_Query(int left, int right, int bloq_l, int bloq_r, int id) {
		this->left = left;
		this->right = right;
		this->bloq_l = bloq_l;
		this->bloq_r = bloq_r;
		this->id = id;
	}
	~_Query() {}

} Query;

typedef struct _Edge {
	int u, v;

	_Edge() {}
	_Edge(int u, int v) {
		this->u = u;
		this->v = v;
	}

	~_Edge() {}
} Edge;

class DSU {
private:
	vector<int> parent;
	vector<pair<int, int> > connections;
	int n;

public:
	DSU() {
		parent.resize(MAXN);
	}

	~DSU() {}

	void restart(int n) {
		for(int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}

	int find(int x, bool do_pc) {
		if(parent[x] == x) {
			return x;
		}
		if(do_pc) {
			return parent[x] = find(parent[x], do_pc);
		}

		return find(parent[x], do_pc);
	}

	int union_mul(int le, int re, Edge *edges) {
		int res = 0;
		for(int i = le; i <= re; i++) {
			int rx = find(edges[i].u, false);
			int ry = find(edges[i].v, false);

			if(rx != ry) {
				connections.pb(mp(rx, ry));
				parent[rx] = ry;
				res++;
			}
		}

		for(int i = 0; i < connections.size(); i++) {
			int rx = connections[i].fst;
			int ry = connections[i].snd;

			parent[rx] = rx;
			parent[ry] = ry;
		}
		connections.clear();

		return res;
	}

	void union_single(int x, int y, int &comp) {
		int rx = find(x, true);
		int ry = find(y, true);

		if(rx != ry) {
			parent[rx] = ry;
			comp--;
		}
	}
};

Query queries[MAXN];
Edge edges[MAXN];
int answers[MAXN];

bool query_comparator(const Query &a, const Query &b) {
	if(a.bloq_l == b.bloq_l) {
		return a.right < b.right;
	}

	return a.bloq_l < b.bloq_l;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	int u, v, l, r, bl, br;
	int act_block, last_block;
	DSU dsu;

	while(t--) {
		cin >> n >> m >> q;
		block_size = (int)round(sqrt(m) + 1.0);
		dsu.restart(n);
		memset(answers, 0, sizeof(answers));

		for(int i = 0; i < m; i++) {
			cin >> u >> v;
			Edge e_act(u, v);
			edges[i] = e_act;
		}

		for(int i = 0; i < q; i++) {
			cin >> l >> r;
			l--; r--;
			bl = l / block_size;
			br = r / block_size;
			Query q_act(l, r, bl, br, i);
			queries[i] = q_act;
		}

		sort(queries, queries + q, query_comparator);

		int idx = 0;
		for(int k = 0; k <= block_size; k++) {
			dsu.restart(n);
			int res = n;
			int ll = block_size * (k + 1);

			while(idx < q && queries[idx].bloq_l == k) {
				// No es necesario procesarlas de manera separada
				if(queries[idx].bloq_l == queries[idx].bloq_r) {
					answers[queries[idx].id] = n - dsu.union_mul(queries[idx].left, queries[idx].right, edges);
				}
				else {
					// Procesar las queries de la derecha que no se encuentren en el bloque siguiente
					while(ll <= queries[idx].right) {
						dsu.union_single(edges[ll].u, edges[ll].v, res);
						ll++;
					}

					// Procesar las queries de la izquierda y guardar la respuesta
					answers[queries[idx].id] = res - dsu.union_mul(queries[idx].left, block_size * (k + 1) - 1, edges);
				}
				idx++;
			}
		}

		for(int i = 0; i < q; i++) {
			cout << answers[i] << "\n";
		}
	}

	return 0;
}