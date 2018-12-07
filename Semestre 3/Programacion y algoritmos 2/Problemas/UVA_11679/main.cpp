#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int b, n, d, c, v;
	while(cin >> b >> n) {
		if(b == 0 && n == 0) break;

		int reserve[b];
		for(int i = 0; i < b; i++) {
			cin >> reserve[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> d >> c >> v;
			reserve[d - 1] -= v;
			reserve[c - 1] += v;
			
		}
		bool possible = true;
		for(int i = 0; i < b; i++) {
			if(reserve[i] < 0) {
				possible = false;
				break;
			}
		}

		cout << (possible ? "S" : "N") << "\n";
	}
}