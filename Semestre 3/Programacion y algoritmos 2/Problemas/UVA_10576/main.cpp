#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

int p[12], vals[2];
bool type[12];
int c, s, d;

void bt(int n) {
	if(n >= 5) {
		int aux = 0;
		for(int i = n - 1; i >= n - 5; i--) {
			aux += (type[i] ? p[i] : -p[i]);
		}
		if(aux > 0) return;

		if(aux < 0 && n == 12) {
			int sum = 0;
			for(int i = 0; i < 12; i++) {
				sum += (type[i] ? p[i] : -p[i]);
			}
			c = max(c, sum);
			return;
		}
	}
	for(int i = 0; i < 2; i++) {
		p[n] = vals[i];
		type[n] = (i == 1);
		bt(n + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	while(cin >> s >> d) {
		vals[0] = d; vals[1] = s;
		c = INT_MIN;
		bt(0);
		if(c < 0) {
			cout << "Deficit\n";
		}
		else {
			cout << c << "\n";
		}
	}

	return 0;
}
