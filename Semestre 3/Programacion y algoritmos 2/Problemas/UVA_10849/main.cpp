#include <iostream>
#include <cmath>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, q, n;
	int r1, c1, r2, c2;
	cin >> t;
	while(t--) {
		cin >> q >> n;
		for(int i = 0; i < q; i++) {
			cin >> r1 >> c1 >> r2 >> c2;
			int r_abs = abs(r1 - r2);
			int c_abs = abs(c1 - c2);

			if((r_abs + c_abs) % 2 != 0) {
				cout << "no move\n";
				continue;
			}
			if(r_abs == 0 && c_abs == 0) {
				cout << "0\n";
			}
			else if(r_abs == c_abs) {
				cout << "1\n";
			}
			else {
				cout << "2\n";
			}
		}
	}

	return 0;
}