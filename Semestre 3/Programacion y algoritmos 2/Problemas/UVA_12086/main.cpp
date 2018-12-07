#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN 200005

using namespace std;

typedef long long ll;

ll arr[MAXN], tree[4 * MAXN];
int n;

void build(int node, int lo, int hi) {
	if(lo == hi) {
		tree[node] = arr[lo];
		return;
	}
	int lc = 2 * node, rc = 2 * node + 1;
	int mid = (lo + hi) / 2;

	build(lc, lo, mid);
	build(rc, mid + 1, hi);
	tree[node] = tree[lc] + tree[rc];
}

void update(int node, int lo, int hi, int i, ll k) {
	if(lo > hi || lo > i || hi < i) {
		return;
	}
	if(lo == hi) {
		tree[node] = k;
		return;
	}

	int lc = 2 * node, rc = 2 * node + 1;
	int mid = (lo + hi) / 2;

	update(lc, lo, mid, i, k);
	update(rc, mid + 1, hi, i, k);

	tree[node] = tree[lc] + tree[rc];
}

ll query(int node, int lo, int hi, int i, int j) {
	if(lo > hi || lo > j || hi < i) {
		return 0;
	}
	if(lo >= i && hi <= j) {
		return tree[node];
	}

	int lc = 2 * node, rc = 2 * node + 1;
	int mid = (lo + hi) / 2;

	ll q1 = query(lc, lo, mid, i, j);
	ll q2 = query(rc, mid + 1, hi, i, j);

	return q1 + q2;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s;
	ll a, b;

	int c = 1;
	while(true) {
		memset(tree, 0, sizeof(tree));

		cin >> n;
		if(n == 0) break;

		if(c > 1) {
			cout << "\n";
		}
		cout << "Case " << c << ":\n";

		for(int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		build(1, 0, n - 1);

		while(true) {
			cin >> s;
			if(s == "END") break;
			cin >> a >> b;

			if(s == "S") {
				a--;
				update(1, 0, n - 1, (int)a, b);
			}
			else {
				a--; b--;
				cout << query(1, 0, n - 1, (int)a, (int)b) << "\n";
			}
		}

		c++;
	}

	return 0;
}