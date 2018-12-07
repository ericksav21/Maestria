#include <iostream>
#include <cmath>

#define MAXN 1000000

using namespace std;

typedef long long ll;

ll cnt[1000000];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cnt[0] = 0;
	for(int i = 1; i < MAXN; i++) {
		cnt[i] = cnt[i - 1] + i;
	}

	int t, n;
	cin >> t;
	for(int i = 1; i <= t; i++) {
		cin >> n;
		cout << "Case " << i << ": ";
		if(cnt[n - 1] % 2 == 0) {
			cout << cnt[n - 1] / 2 << "\n";
		}
		else {
			cout << cnt[n - 1] << "/2\n";
		}
	}

	return 0;
}