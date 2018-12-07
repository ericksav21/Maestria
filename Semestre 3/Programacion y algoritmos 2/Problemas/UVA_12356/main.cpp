#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 100010

using namespace std;

void print_arr(int *p, int n) {
	for(int i = 1; i <= n; i++) {
		cout << p[i] << " ";
	}
	cout << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int s, b, l, r;
	int left[MAXN], right[MAXN];

	while(true) {
		cin >> s >> b;
		if(s == 0 && b == 0) break;
		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));

		for(int i = 1; i <= s; i++) {
			left[i] = i - 1;
			right[i] = i + 1;
		}
		right[s] = 0;

		while(b--) {
			cin >> l >> r;
			left[right[r]] = left[l];
			right[left[l]] = right[r];

			if(left[right[r]] == 0) cout << "* ";
			else cout << left[right[r]] << " ";
			if(right[left[l]] == 0) cout << "*\n";
			else cout << right[left[l]] << "\n";
		}
		cout << "-\n";
	}

	return 0;
}