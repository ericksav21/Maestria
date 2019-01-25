#include <bits/stdc++.h>

#define MAXN 100005

using namespace std;

int arr[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t, n;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		int mmin = arr[n - 1];
		int res = INT_MIN;
		for(int i = n - 2; i >= 0; i--) {
			if(arr[i] - mmin > res) {
				res = arr[i] - mmin;
			}
			if(arr[i] < mmin) {
				mmin = arr[i];
			}
		}

		cout << res << "\n";
	}

	return 0;
}