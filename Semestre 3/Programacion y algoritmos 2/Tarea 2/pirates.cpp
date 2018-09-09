#include <bits/stdc++.h>

#define MAXN 1024005

using namespace std;

// Reservamos espacio para el segment tree y el lazy tree
int tree[4 * MAXN], lazy[4 * MAXN];

// Regresa la cadena s repetida n veces
string repeat(string s, int n) {
    ostringstream os;
    for(int i = 0; i < n; i++)
        os << s;
    return os.str();
}

// Método para construir el árbol de forma habitual
void build_tree(string &s, int node, int lo, int hi) {
	if(lo == hi) {
		// Guardamos si el nodo es un bucanero o no
		tree[node] = s[lo] - '0';
	}
	else {
		int mid = (lo + hi) / 2;
		int lc = 2 * node, rc = 2 * node + 1;

		build_tree(s, lc, lo, mid);
		build_tree(s, rc, mid + 1, hi);

		tree[node] = tree[lc] + tree[rc];
	}
}

// Actualiza el nodo del lazy tree con una nueva update
void compound_update(int node, int u_type) {
	/*
		Si la nueva update corresponde a cambiar todos los
		piratas a un bando en específico entonces sobreescribe
		a las updates anteriores en el nodo
	*/
	if(u_type == 1 || u_type == 2) {
		lazy[node] = u_type;
	}
	/*
		Si la nueva update corresponde a invertir los bandos de
		los piratas entonces se procesa por casos.
		Caso 1: No hay updates anteriores, este caso se procesa normal
		Caso 2: Update anterior tipo 'F', esta update se cambiaría por una tipo 'E'
		Caso 3: Update anterior tipo 'E', esta update se cambiaría por una tipo 'F'
		Caso 4: Update anterior tipo 'I', la nueva update cancela a la anterior
	*/
	else if(u_type == 3) {
		if(lazy[node] == 0) lazy[node] = u_type;
		else if(lazy[node] == 1) lazy[node] = 2;
		else if(lazy[node] == 2) lazy[node] = 1;
		else lazy[node] = 0;
	}
}

// Regresa el número de bucaneros en un rango
int query(int node, int lo, int hi, int i, int j) {
	int mid = (lo + hi) / 2;
	int lc = 2 * node, rc = 2 * node + 1;

	// Si hay actualizaciones pendientes se realizan
	if(lazy[node] != 0) {
		if(lazy[node] == 1) {
			tree[node] = hi - lo + 1;
		}
		else if(lazy[node] == 2) {
			tree[node] = 0;
		}
		else {
			tree[node] = hi - lo + 1 - tree[node];
		}

		if(lo != hi) {
			compound_update(lc, lazy[node]);
			compound_update(rc, lazy[node]);
		}
		lazy[node] = 0;
	}

	// Fuera de rango
	if(lo > hi || j < lo || i > hi) return 0;

	// Completamente en rango
	if(i <= lo && j >= hi) return tree[node];

	int q1 = query(lc, lo, mid, i, j);
	int q2 = query(rc, mid + 1, hi, i, j);

	return q1 + q2;
}

/*
	0: Sin actualizaciones
	1: F (Todos a bucaneros)
	2: E (Todos a bárcaros)
	3: I (Invertir)
*/
void update(int node, int lo, int hi, int i, int j, int u_type) {
	int mid = (lo + hi) / 2;
	int lc = 2 * node, rc = 2 * node + 1;

	// Si hay actualizaciones pendientes se realizan
	if(lazy[node] != 0) {
		if(lazy[node] == 1) {
			tree[node] = hi - lo + 1;
		}
		else if(lazy[node] == 2) {
			tree[node] = 0;
		}
		else {
			tree[node] = hi - lo + 1 - tree[node];
		}

		if(lo != hi) {
			compound_update(lc, lazy[node]);
			compound_update(rc, lazy[node]);
		}
		lazy[node] = 0;
	}

	// Fuera de rango
	if(lo > hi || j < lo || i > hi) return;

	// Completamente en rango
	if(i <= lo && j >= hi) {
		//Se hace la actualización en el nodo correspondiente
		if(u_type == 1) {
			tree[node] = hi - lo + 1;
		}
		else if(u_type == 2) {
			tree[node] = 0;
		}
		else {
			tree[node] = hi - lo + 1 - tree[node];
		}

		if(lo != hi) {
			// Se deja la actualización pendiente en los hijos del nodo
			compound_update(lc, u_type);
			compound_update(rc, u_type);
		}
	}
	// Parcialmente dentro, se actualiza de forma recursiva
	else {
		update(lc, lo, mid, i, j, u_type);
		update(rc, mid + 1, hi, i, j, u_type);

		tree[node] = tree[lc] + tree[rc];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, m, np, q, a, b, sz, cnt;
	string pirates, p_aux, q_type;

	cin >> t;
	for(int c = 1; c <= t; c++) {
		cout << "Case " << c << ":\n";
		pirates = "";
		memset(lazy, 0, sizeof(lazy));
		cnt = 1;

		cin >> m;
		for(int i = 0; i < m; i++) {
			cin >> np;
			cin >> p_aux;
			pirates += repeat(p_aux, np);
		}
		sz = pirates.size();
		build_tree(pirates, 1, 0, sz - 1);

		cin >> q;
		while(q--) {
			cin >> q_type >> a >> b;
			char q_t_aux = q_type[0];

			if(q_t_aux == 'F') update(1, 0, sz - 1, a, b, 1);
			else if(q_t_aux == 'E') update(1, 0, sz - 1, a, b, 2);
			else if(q_t_aux == 'I') update(1, 0, sz - 1, a, b, 3);
			else {
				int res = query(1, 0, sz - 1, a, b);
				cout << "Q" << cnt << ": " << res << "\n";
				cnt++;
			}
		}
	}


	return 0;
}