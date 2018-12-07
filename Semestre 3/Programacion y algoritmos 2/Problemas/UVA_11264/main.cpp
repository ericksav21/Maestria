#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, n, coins[1001];
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> coins[i];
		}

		int w = coins[0], cnt = 2;
		for(int i = 1; i < n - 1; i++) {
			if(coins[i] + w < coins[i + 1]) {
				w += coins[i];
				cnt++;
			}
		}

		cout << cnt << "\n";
	}

	return 0;
}