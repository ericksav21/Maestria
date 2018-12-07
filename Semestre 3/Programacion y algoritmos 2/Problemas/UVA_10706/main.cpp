#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	int t;
	cin >> t;
	while(t--) {
		ll n;
		cin >> n;

		ll m = 0, now = 0, d = 0;
		ll t;
		while(m < n) {
			now++;
			t = now;
			while(t) {
				d++;
				t /= 10;
			}
			m += d;
		}

		ll tmp = now;
		while(m != n) {
			tmp /= 10;
			m--;

			if(!tmp) {
				now--;
				tmp = now;
			}
		}

		cout << (tmp % 10) << "\n";
	}

	return 0;
}