#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>

#define MAXN 100010

#define pb push_back
#define mp make_pair
#define fst first
#define snd second

using namespace std;

vector<int> tree[4 * MAXN];
int arr[MAXN], comp[MAXN];

/*
  Se hace la misma función merge del mergesort para calcular el valor
del nodo actual
*/
void merge(int node, int lc, int rc) {
	int s1 = tree[lc].size(), s2 = tree[rc].size();
	int sz_t = s1 + s2;
	tree[node].resize(sz_t, 0);

	int i = 0, j = 0;
	for(int k = 0; k < sz_t; k++) {
		if(i >= s1) tree[node][k] = tree[rc][j++];
		else if(j >= s2) tree[node][k] = tree[lc][i++];
		else if(tree[lc][i] < tree[rc][j]) tree[node][k] = tree[lc][i++];
		else tree[node][k] = tree[rc][j++];
	}
}

/*
  Función básica para construir el árbol
*/
void build_tree(int node, int lo, int hi) {
	if(lo == hi) {
		tree[node].push_back(comp[lo]);
	}
	else {
		int lc = 2 * node, rc = 2 * node + 1;
		int mid = (lo + hi) / 2;

		build_tree(lc, lo, mid);
		build_tree(rc, mid + 1, hi);

		merge(node, lc, rc);
	}
}

/*
  Búsqueda binaria para ver cuántos elementos son menores o iguales que K
*/
int bs(int node, int k) {
	int sz = tree[node].size();
	int linf = 0, lsup = sz;

	//Hacer upper bound
	while(linf < lsup) {
		int mid = (linf + lsup) / 2;
		if(k >= tree[node][mid]) {
			linf = mid + 1;
		}
		else {
			lsup = mid;
		}
	}

	return linf;
}

/*
  Método para consultar al árbol
*/
int query(int node, int lo, int hi, int i, int j, int k) {
	//Si está fuera de rango regresar cero
	if(i > hi || j < lo) return 0;

	//Si está completamente adentro del rango, hacer BS
	if(i <= lo && j >= hi) {
		return bs(node, k);
	}

	//Parcialmente adentro, consultar a los hijos
	int lc = 2 * node, rc = 2 * node + 1;
	int mid = (lo + hi) / 2;

	int q1 = query(lc, lo, mid, i, j, k);
	int q2 = query(rc, mid + 1, hi, i, j, k);

	return q1 + q2;
}

/*
  Esta función hace un BFS al árbol, sólo fue hecha para verificar que
  se haya construido correctamente
*/
void print_tree(int node, int lo, int hi) {
	queue<pair<int, pair<int, int> > > q;
	q.push(mp(node, mp(lo, hi)));

	while(!q.empty()) {
		pair<int, pair<int, int> > pp = q.front(); q.pop();
		int nn = pp.fst;
		int i = pp.snd.fst, j = pp.snd.snd;

		for(int k = 0; k < tree[nn].size(); k++) {
			printf("%d ", tree[nn][k]);
		}
		printf("\n");

		if(i < j) {
			int lc = 2 * nn, rc = 2 * nn + 1;
			int mid = (i + j) / 2;
			q.push(mp(lc, mp(i, mid)));
			q.push(mp(rc, mp(mid + 1, j)));
		}
	}
}

int main() {
	int n, m, ai, q, i, j, k, res;
	scanf("%d %d", &n, &q);
	for(int i = 0; i < n; i++) {
		scanf("%d", &ai);
		//Se usa una copia del vector original
		arr[i] = comp[i] = ai;
	}

	//En esta parte se hace la compresión de caminos, primero se ordena el arreglo
	sort(arr, arr + n);

	//Luego, por cada elemento del arreglo no ordenado se busca la posición en el ordenado
	//usando una BS y esa posicion se almacena en el no ordenado
	int linf, lsup, mid;
	for(int ii = 0; ii < n; ii++) {
		linf = 0, lsup = n - 1;
		while(linf <= lsup) {
			int mid = (linf + lsup) / 2;
			if(arr[mid] == comp[ii]) {
				comp[ii] = mid;
				break;
			}
			else if(arr[mid] < comp[ii]) {
				linf = mid + 1;				
			}
			else {
				lsup = mid - 1;
			}
		}
	}

	//Se construye el árbol
	build_tree(1, 0, n - 1);

	while(q--) {
		scanf("%d %d %d", &i, &j, &k);

		//Con BS buscar el mínimo elemento tal que "query(i, j)" de exactamente k valores
		linf = 0, lsup = n - 1, res = 0;
		while(linf <= lsup) {
			int mid = (linf + lsup) / 2;
			int q_r = query(1, 0, n - 1, i - 1, j - 1, mid);

			if(q_r >= k) {
				res = mid;
				lsup = mid - 1;
			}
			else {
				linf = mid + 1;
			}
		}
		printf("%d\n", arr[res]);
	}

	return 0;
}
