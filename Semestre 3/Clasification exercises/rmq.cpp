#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 100005

using namespace std;

int tree[4 * MAXN];

void build_tree(int *arr, int node, int lo, int hi) {
	if(lo == hi) {
		tree[node] = lo;
	}
	else {
		int lc = node * 2, rc = node * 2 + 1;
		int mid = (lo + hi) / 2;
		build_tree(arr, lc, lo, mid);
		build_tree(arr, rc, mid + 1, hi);

		//Merge op
		if(arr[tree[lc]] < arr[tree[rc]]) {
			tree[node] = tree[lc];
		}
		else {
			tree[node] = tree[rc];
		}
	}
}

int query(int *arr, int node, int lo, int hi, int i, int j) {
	int id1, id2;
	if(i > hi || j < lo) {
		return -1;
	}

	if(lo >= i && hi <= j) {
		return tree[node];
	}

	int lc = node * 2, rc = node * 2 + 1;
	int mid = (lo + hi) / 2;
	id1 = query(arr, lc, lo, mid, i, j);
	id2 = query(arr, rc, mid + 1, hi, i, j);

	if(id1 == -1) {
		return id2;
	}
	if(id2 == -1) {
		return id1;
	}

	if(arr[id1] <= arr[id2]) {
		return id1;
	}
	else {
		return id2;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q, i, j, id;

	cin >> n;
	memset(tree, -1, sizeof(tree));

	int arr[n];
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	build_tree(arr, 1, 0, n - 1);

	cin >> m;
	while(m--) {
		cin >> i >> j;
		id = query(arr, 1, 0, n - 1, i, j);
		cout << arr[id] << "\n";
	}

	return 0;
}