#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>

#include <boost/functional/hash.hpp>

#define MAXN 100005

using namespace std;

/*
	Se genera una función hash para vectores ya que por defecto
	C++ no posee una
*/
template <typename Container>
struct container_hash {
    size_t operator()(Container const &c) const {
        return boost::hash_range(c.begin(), c.end());
    }
};

int n, id;
vector<int> adj_a[MAXN], adj_b[MAXN];
unordered_map<vector<int>, int, container_hash<vector<int> > > mp;

void clear_adj() {
	for(int i = 0; i < MAXN; i++) {
		adj_a[i].clear();
		adj_b[i].clear();
	}
}

/*
	Se hace un BFS para obtener el nodo más alejado a un nodo A
*/
int bfs(vector<int> (&adj)[MAXN], int org, vector<int> &parent) {
	int farthest = org;
	parent[farthest] = farthest;
	queue<int> q;
	q.push(farthest);

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		farthest = u;

		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if(parent[v] == -1) {
				q.push(v);
				parent[v] = u;
			}
		}
	}

	return farthest;
}

vector<int> get_center(vector<int> (&adj)[MAXN]) {
	vector<int> parent(n + 1, -1);
	vector<int> path, centers;

	// Se hace un primer BFS para obtener el nodo más alejado
	// a un nodo inicial
	int leaf = bfs(adj, 1, parent);
	fill(parent.begin(), parent.end(), -1);
	// Se hace un segundo BFS para obtener el nodo más alejado
	// al nodo leaf, así como obtener el diámetro del árbol
	int farthest = bfs(adj, leaf, parent);

	int u = farthest;
	path.push_back(u);
	while(u != parent[u]) {
		path.push_back(parent[u]);
		u = parent[u];
	}

	if(path.size() % 2 == 0) {
		centers.push_back(path[path.size() / 2 - 1]);
		centers.push_back(path[path.size() / 2]);
	}
	else {
		centers.push_back(path[path.size() / 2]);
	}

	return centers;
}

/*
	Este método usa la tabla Hash así como una variable global
	para asignar IDs únicos a los nodos
*/
int get_id(vector<int> &vec) {
	if(mp.find(vec) != mp.end()) {
		return mp[vec];
	}
	mp[vec] = id++;
	return mp[vec];
}

/*
	Este método usa el algoritmo DFS para generar la representación del árbol
*/
void dfs(vector<int> (&adj)[MAXN], vector<int> &names, vector<int> &prev, int u) {
	vector<int> v_aux;
	for(int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if(prev[v] == -1) {
			prev[v] = u;
			dfs(adj, names, prev, v);
			v_aux.push_back(names[v]);
		}
	}
	if(v_aux.size() == 0) {
		v_aux.push_back(0);
	}
	sort(v_aux.begin(), v_aux.end());
	names[u] = get_id(v_aux);
}

/*
	Método principal de Ahu, este genera las dos representaciones
	de los árboles y compara el ID generado en la raíz de ambos árboles
	para decidir si son Isomorfos
*/
bool ahu(int ra, int rb) {
	mp.clear();
	id = 1;
	vector<int> names_a(n + 1), names_b(n + 1);
	vector<int> prev_a(n + 1, -1), prev_b(n + 1, -1);

	prev_a[ra] = ra;
	prev_b[rb] = rb;
	dfs(adj_a, names_a, prev_a, ra);
	dfs(adj_b, names_b, prev_b, rb);

	return (names_a[ra] == names_b[rb]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, u, v;
	cin >> t;

	while(t--) {
		clear_adj();
		cin >> n;
		if(n == 1) {
			cout << "YES\n";
			continue;
		}

		for(int i = 0; i < n - 1; i++) {
			cin >> u >> v;
			adj_a[u].push_back(v);
			adj_a[v].push_back(u);
		}
		for(int i = 0; i < n - 1; i++) {
			cin >> u >> v;
			adj_b[u].push_back(v);
			adj_b[v].push_back(u);
		}

		vector<int> ca = get_center(adj_a);
		vector<int> cb = get_center(adj_b);

		// Se el número de centros es distinto de antemano
		// se sabe que los árboles no son Isomorfos
		if(ca.size() != cb.size()) {
			cout << "NO\n";
			continue;
		}
		if(ahu(ca[0], cb[0])) {
			cout << "YES\n";
			continue;
		}
		// Puede darse el caso en donde existen dos centros e
		// hicimos el algoritmo de Ahu con la pareja equivocada
		// por lo que hay que comparar el otro par de centros
		if(ca.size() > 1 && ahu(ca[1], cb[0])) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}

	return 0;
}